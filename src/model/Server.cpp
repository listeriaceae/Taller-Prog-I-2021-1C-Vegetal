#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <chrono>
#include <algorithm>
#include <thread>
#include <arpa/inet.h>
#include <fmt/format.h>

#include "Server.hpp"
#include "../configuration.hpp"
#include "../logger.hpp"
#include "Nivel1.hpp"
#include "Nivel2.hpp"
#include "Interlude.hpp"
#include "Mario.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"
#include "../utils/estadoJuego.hpp"
#include "../utils/player.hpp"
#include "../utils/dataTransfer.hpp"

static int serverSocket{ -1 };

static Scene *getNextScene(std::vector<Mario> *marios);
static void getEstadoJugadores(GameState &estado, const std::vector<player_t> &connectedPlayers);

static void acceptNewConnections(Server *server);
static void receiveControls(int clientSocket, Mario *mario);
static Login validateUserLogin(int client, Server *server);

static void handleLogin(int client, Server *server);

int Server::serverListen(std::uint16_t port)
{
  // socket
  if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("ERROR opening socket");
    return EXIT_FAILURE;
  }

  struct sockaddr_in serverAddress
  {
  };
  std::memset(&serverAddress, 0, sizeof serverAddress);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port);

  // bind
  if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof serverAddress) == -1) {
    perror("ERROR on binding");
    close(serverSocket);
    return EXIT_FAILURE;
  }

  // listen
  if (constexpr int max_queued_connections = 3;
      listen(serverSocket, max_queued_connections) == -1) {
    perror("ERROR on listen");
    close(serverSocket);
    return EXIT_FAILURE;
  }

  puts("Aplicación iniciada en modo servidor");
  return EXIT_SUCCESS;
}

Server::Server()
{
  const auto &config = configuration::GameConfiguration::getInstance(CONFIG_FILE);
  for (auto &u : config.getUsers()) {
    this->users.emplace(std::string(u.username), std::string(u.password));
  }
  connectedPlayers.players.reserve(config.getMaxPlayers());
}

int Server::startServer()
{
  {
    const auto &config = configuration::GameConfiguration::getInstance(CONFIG_FILE);
    logger::Logger::getInstance().setLogLevel(config.getLogLevel());
    maxPlayers = config.getMaxPlayers();
  }

  logger::Logger::getInstance().logNewGame();
  std::thread acceptConnections;

  {
    std::unique_lock lk{ this->start_game_cv.mtx };

    acceptConnections = std::thread{ acceptNewConnections, this };

    start_game_cv.cv.wait(lk, [&]() {
      return connectedPlayers.players.size() == maxPlayers;
    });
  }
  startGame();

  for (auto &player : connectedPlayers.players)
    close(player.clientSocket);

  shutdown(serverSocket, SHUT_RDWR);
  close(serverSocket);
  acceptConnections.join();

  return EXIT_SUCCESS;
}

void Server::startGame()
{
  std::vector<Mario> marios{ maxPlayers };

  Scene *scene = getNextScene(&marios);
  GameState game{};

  {
    size_t i = 0;
    for (auto &player : connectedPlayers.players) {
      player.mario = &marios[i];
      std::memcpy(game.players[i++].name, player.user, 4);
      std::thread receiver{ receiveControls, player.clientSocket, player.mario };
      receiver.detach();
    }
  }

  auto previous = std::chrono::steady_clock::now();
  std::chrono::nanoseconds lag{ 0 };
  while (scene != nullptr) {
    {
      const auto current = std::chrono::steady_clock::now();
      const auto elapsed = current - previous;
      previous = current;
      lag += elapsed;
    }
    {
      static constexpr long frames_per_s = 60L;
      using frame_duration_t =
        std::chrono::duration<int64_t, std::ratio<1, frames_per_s>>;
      static constexpr auto ns_per_frame =
        std::chrono::ceil<std::chrono::nanoseconds>(frame_duration_t{ 1 });

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
        player.isConnected && dataTransfer::sendData(player.clientSocket, &game, sizeof game);
      player.mario->audioObserver.reset();
    }
    if (scene->isComplete()) {
      delete scene;
      scene = getNextScene(&marios);
    }
  }
  for (auto &player : connectedPlayers.players)
    if (player.isConnected)
      shutdown(player.clientSocket, SHUT_RDWR);
}

// START LOGIN
static void
  acceptNewConnections(Server *server)
{
  server->start_game_cv.mtx.lock();
  while (true) {
    int clientSocket{ -1 };
    {
      struct sockaddr_in clientAddress;
      socklen_t clilen = sizeof clientAddress;
      clientSocket = accept(serverSocket,
        reinterpret_cast<struct sockaddr *>(&clientAddress),
        &clilen);
      if (clientSocket < 0) {
        if (errno == EBADF || errno == EINVAL)
          break;
        perror("ERROR on accept");
        exit(1);
      }
    }
    std::thread clientConnection{ handleLogin, clientSocket, server };
    clientConnection.detach();
  }
}

static void
  handleLogin(int client, Server *server)
{
  Login response;

  do {
    response = validateUserLogin(client, server);
    dataTransfer::sendData(client, &response, sizeof response);
  } while (response != Login::ABORTED && response != Login::OK);
}

static Login
  validateUserLogin(int client, Server *server)
{
  user_t user;
  if (!dataTransfer::receiveData(client, &user, sizeof user)) {
    logger::Logger::getInstance().logInformation("[server] Lost connection to client");
    close(client);
    return Login::ABORTED;
  }

  if (server->users.find(user.username) == std::end(server->users)) {
    logger::Logger::getInstance().logInformation(fmt::format("[server] invalid user: '{}'", user.username));
    return Login::INVALID_USER;
  }

  if (strcmp(server->users.at(user.username).c_str(), user.password) != 0) {
    logger::Logger::getInstance().logInformation(fmt::format("[server] incorrect password for user: '{}'", user.username));
    return Login::INVALID_USER_PASS;
  }

  bool reconnected = false;
  std::lock_guard lock{ server->connectedPlayers.mtx };
  for (auto &player : server->connectedPlayers.players) {
    if (strncmp(player.user, user.username, 3) == 0) {
      if (player.isConnected) {
        logger::Logger::getInstance().logInformation(
          fmt::format("[server] user '{}' already connected", user.username));
        return Login::USER_ALREADY_CONNECTED;
      } else {
        close(player.clientSocket);
        player.clientSocket = client;
        reconnected = true;
        player.isConnected = true;
        player.mario->enable();
        std::thread receiver{ receiveControls, client, player.mario };
        receiver.detach();
        logger::Logger::getInstance().logInformation(
          fmt::format("[server] successfully "
                      "reconnected user '{}'", user.username));
      }
    }
  }

  if (!reconnected) {
    if (server->connectedPlayers.players.size() == server->maxPlayers)
      return Login::MAX_USERS_CONNECTED;
    else {
      server->connectedPlayers.players.emplace_back(player_t{
        nullptr,
        client,
        true,
        { user.username[0], user.username[1], user.username[2] } });
      logger::Logger::getInstance().logInformation(
        fmt::format("[server] accepted new user: '{}'", user.username));
      if (server->connectedPlayers.players.size() == server->maxPlayers) {
        server->start_game_cv.mtx.unlock();
        server->start_game_cv.cv.notify_one();
      }
    }
  }

  return Login::OK;
}
// END LOGIN

static void
  receiveControls(int clientSocket, Mario *mario)
{
  std::uint8_t controls, aux = 255;
  while (dataTransfer::receiveData(clientSocket, &controls, sizeof controls)) {
    std::uint8_t old = mario->controls;
    std::uint8_t new_controls = (old & SPACE) | (controls & aux);
    while (!mario->controls.compare_exchange_weak(old, new_controls))
      new_controls = (old & SPACE) | (controls & aux);
    aux = ~(controls & SPACE);
  }
  mario->disable();
  shutdown(clientSocket, SHUT_RD);
}

static Scene *
  getNextScene(std::vector<Mario> *marios)
{
  switch (static int currentScene = 0; ++currentScene) {
  case 1:
    logger::Logger::getInstance().logDebug("Level 1 starts");
    return new Nivel1{ marios };
  case 2:
    logger::Logger::getInstance().logDebug("End of Level 1");
    {
      const bool gameOver =
        std::none_of(std::cbegin(*marios), std::cend(*marios), &isAlive);
      currentScene = gameOver ? -1 : currentScene;
      return new Interlude{ gameOver };
    }
  case 3:
    logger::Logger::getInstance().logDebug("Level 2 starts");
    return new Nivel2{ marios };
  case 4:
    logger::Logger::getInstance().logDebug("End of Level 2");
    return new Interlude{ true };
  default:
    logger::Logger::getInstance().logGameOver();
    return nullptr;
  }
}

static void
  getEstadoJugadores(GameState &estado, const std::vector<player_t> &connectedPlayers)
{
  size_t i = 0;
  for (const auto &player : connectedPlayers) {
    estado.players[i].lives = player.mario->lives;
    estado.players[i++].score = player.mario->score;
  }
}
