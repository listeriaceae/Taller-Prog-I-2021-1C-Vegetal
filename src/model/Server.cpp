#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <chrono>
#include <algorithm>
#include <memory>
#include <thread>
#include <arpa/inet.h>
#include <fmt/format.h>

#include "Server.hpp"
#include "../configuration.hpp"
#include "../logger.hpp"
#include "Interlude.hpp"
#include "Nivel1.hpp"
#include "Nivel2.hpp"
#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "../utils/dataTransfer.hpp"
#include "../utils/estadoJuego.hpp"
#include "../utils/player.hpp"
#include "../utils/tcp_server.hpp"

static std::unique_ptr<Scene> getNextScene(std::vector<Mario> *marios);
static void getEstadoJugadores(GameState &estado,
                               const std::vector<player_t> &connectedPlayers);

static void receiveControls(Mario *mario, int clientSocket);


static std::unordered_map<std::string, std::string>
init_users(std::vector<std::pair<std::string, std::string>> u)
{
  return std::unordered_map<std::string, std::string>(std::begin(u), std::end(u));
}

Server::Server()
: users{ init_users(configuration::getUsers()) },
  maxPlayers{ configuration::getMaxPlayers() }
{
}

Server::~Server()
{
  for (const auto &player : connectedPlayers.players)
    if (player.isConnected)
      Network::close_connection(player.clientSocket);
}

void
Server::startGame()
{
  std::vector<Mario> marios{ maxPlayers };

  auto scene = getNextScene(&marios);
  GameState game{};

  for (std::size_t i = 0; auto &player : connectedPlayers.players) {
    player.mario = &marios[i];
    std::strncpy(game.players[i++].name, player.user, 4);
    std::thread(receiveControls, player.mario, player.clientSocket).detach();
  }

  auto previous = std::chrono::steady_clock::now();
  decltype(previous - previous) lag{ 0 };
  while (scene != nullptr) {
    {
      const auto current = std::chrono::steady_clock::now();
      const auto elapsed = current - previous;
      previous = current;
      lag += elapsed;
    }
    {
      constexpr long fps = 60L;
      using frame_duration_t =
        std::chrono::duration<std::int64_t, std::ratio<1, fps>>;
      static constexpr auto ns_per_frame =
        std::chrono::ceil<decltype(lag)>(frame_duration_t{ 1 });

      std::this_thread::sleep_for(ns_per_frame - lag);
      do {
        scene->update();
        lag -= ns_per_frame;
      } while (lag >= ns_per_frame);
    }

    game.level = scene->getEstado();
    getEstadoJugadores(game, connectedPlayers.players);

    for (auto &player : connectedPlayers.players) {
      player.isConnected =
        player.isConnected
        && dataTransfer::sendData(player.clientSocket, &game, sizeof game);
      player.mario->audioObserver.reset();
    }
    if (scene->isComplete())
      scene = getNextScene(&marios);
  }
}

// START LOGIN
void
Server::handleLogin(int client)
{
  Login response;

  do {
    response = validateUserLogin(client);
    dataTransfer::sendData(client, &response, sizeof response);
  } while (response != Login::ABORTED && response != Login::OK);
}

Login
Server::validateUserLogin(int client)
{
  user_t user;
  if (!dataTransfer::receiveData(client, &user, sizeof user)) {
    logger::logInfo(
      "[server] Lost connection to client");
    close(client);
    return Login::ABORTED;
  }

  if (this->users.find(user.username) == std::end(this->users)) {
    logger::logInfo(
      fmt::format("[server] invalid user: '{}'", user.username));
    return Login::INVALID_USER;
  }

  if (strcmp(this->users.at(user.username).c_str(), user.password) != 0) {
    logger::logInfo(
      fmt::format("[server] incorrect password for user: '{}'", user.username));
    return Login::INVALID_USER_PASS;
  }

  bool reconnected = false;
  std::lock_guard lock{ this->connectedPlayers.mtx };
  for (auto &player : this->connectedPlayers.players) {
    if (strncmp(player.user, user.username, 3) == 0) {
      if (player.isConnected) {
        logger::logInfo(
          fmt::format("[server] user '{}' already connected", user.username));
        return Login::USER_ALREADY_CONNECTED;
      } else {
        close(player.clientSocket);
        player.clientSocket = client;
        reconnected = true;
        player.isConnected = true;
        player.mario->enable();
        std::thread(receiveControls, player.mario, client).detach();
        logger::logInfo(
          fmt::format("[server] successfully "
                      "reconnected user '{}'",
                      user.username));
      }
    }
  }

  if (!reconnected) {
    if (this->connectedPlayers.players.size() == this->maxPlayers)
      return Login::MAX_USERS_CONNECTED;
    else {
      this->connectedPlayers.players.emplace_back(
        player_t{ nullptr,
                  client,
                  true,
                  { user.username[0], user.username[1], user.username[2] } });
      logger::logInfo(
        fmt::format("[server] accepted new user: '{}'", user.username));
      if (this->connectedPlayers.players.size() == this->maxPlayers) {
        this->start_game_cv.mtx.unlock();
        this->start_game_cv.cv.notify_one();
      }
    }
  }

  return Login::OK;
}
// END LOGIN

static void
receiveControls(Mario *mario, int clientSocket)
{
  std::uint8_t controls, new_controls, aux = 0xff;
  while (dataTransfer::receiveData(clientSocket, &controls, sizeof controls)) {
    auto old = mario->controls.load(std::memory_order_relaxed);
    do
      new_controls = (old & SPACE) | (controls & aux);
    while (!mario->controls.compare_exchange_weak(
      old, new_controls, std::memory_order_relaxed, std::memory_order_relaxed));
    aux = ~(controls & SPACE);
  }
  mario->disable();
  shutdown(clientSocket, SHUT_RD);
}

static std::unique_ptr<Scene>
getNextScene(std::vector<Mario> *marios)
{
  switch (static int currentScene = 0; ++currentScene) {
  case 1:
    logger::logDebug("Level 1 starts");
    return std::make_unique<Nivel1>(marios);
  case 2:
    logger::logDebug("End of Level 1");
    {
      const bool gameOver =
        std::none_of(std::cbegin(*marios), std::cend(*marios), &isAlive);
      currentScene = gameOver ? -1 : currentScene;
      return std::make_unique<Interlude>(gameOver);
    }
  case 3:
    logger::logDebug("Level 2 starts");
    return std::make_unique<Nivel2>(marios);
  case 4:
    logger::logDebug("End of Level 2");
    return std::make_unique<Interlude>(true);
  default:
    logger::logGameOver();
    return nullptr;
  }
}

static void
getEstadoJugadores(GameState &estado,
                   const std::vector<player_t> &connectedPlayers)
{
  std::size_t i = 0;
  for (const auto &player : connectedPlayers) {
    estado.players[i].lives = player.mario->lives;
    estado.players[i++].score = player.mario->score;
  }
}
