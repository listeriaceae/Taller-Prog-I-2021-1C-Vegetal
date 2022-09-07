#include <unistd.h>
#include <iostream>
#include <string>
#include <mutex>
#include <atomic>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <condition_variable>
#include <SDL2/SDL_image.h>
#include <arpa/inet.h>
#include <fmt/format.h>

#include "Client.hpp"
#include "Nivel1Vista.hpp"
#include "Nivel2Vista.hpp"
#include "InterludeVista.hpp"
#include "StartPageView.hpp"
#include "showMessage.hpp"
#include "../logger.hpp"
#include "../controller/MarioController.hpp"
#include "../controller/AudioController.hpp"
#include "../utils/Constants.hpp"
#include "../utils/estadoJuego.hpp"
#include "../utils/dataTransfer.hpp"
#include "../utils/textureHandler.hpp"
#include "../utils/network.hpp"

#define SERVER_CONNECTION_SUCCESS 0
#define START_PAGE_SUCCESS 0

bool quitRequested{ false };
SDL_Renderer *renderer{ nullptr };
SDL_Texture *texture{ nullptr };

static std::atomic<bool> serverOpen{ true };
static int clientSocket{ -1 };

static Login auth(int socket, user_t user);
static void receiveState(int socket, std::atomic<GameState> *lsh);
static void sendControls(int socket);

Client::Client()
{
  SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  window = SDL_CreateWindow("Donkey Kong 2: Jumpman Returns",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            448,
                            512,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  textureHandler::load();
  AudioController::loadAudioFiles();
}

Client::~Client()
{
  AudioController::closeAudioFiles();
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}

void
Client::startClient(int socket)
{
  showMessage::waitingLobby();
  const auto status = startGame(socket);
  processExit(status);
}

void
Client::processExit(ExitStatus exitStatus)
{
  switch (exitStatus) {
  case ExitStatus::CONNECTION_CLOSED:
    logger::logInfo(fmt::format("[{}] connection closed", this->name));
    showMessage::disconnection();
    break;
  case ExitStatus::GAME_OVER:
    logger::logInfo(fmt::format("[{}] game over", this->name));
    showMessage::gameOver();
    break;
  case ExitStatus::GAME_COMPLETE:
    logger::logInfo(fmt::format("[{}] game complete", this->name));
    showMessage::gameComplete();
    break;
  case ExitStatus::QUIT_REQUESTED:
    logger::logInfo(fmt::format("[{}] quit requested", this->name));
    return;
  default:
    break;
  }
  while (!SDL_QuitRequested()) {
    std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
    AudioController::checkToggleMusicEvent(
      SDL_GetKeyboardState(NULL)[SDL_SCANCODE_M]);
  };
}

ExitStatus
Client::startGame(int socket)
{
  AudioController::startMusic();

  std::size_t currentScene{ std::numeric_limits<std::size_t>::max() };
  std::unique_ptr<SceneVista> vista{};
  std::atomic<GameState> level_state{};

  std::thread receiver{ receiveState, socket, &level_state };

  level_state.wait({}, std::memory_order_relaxed);
  const std::size_t playerIndex = [&]() {
    std::size_t match{ std::numeric_limits<std::size_t>::max() };
    const auto game_state = level_state.load(std::memory_order_relaxed);
    for (std::size_t i = 0; i < MAX_PLAYERS; ++i)
      if (strncmp(game_state.players[i].name, name, 3) == 0)
        match = i;
    return match;
  }();

  std::thread sender{ sendControls, socket };

  ExitStatus exitStatus = ExitStatus::CONNECTION_CLOSED;
  while (!quitRequested && serverOpen.load(std::memory_order_relaxed)) {
    level_state.wait({}, std::memory_order_relaxed);
    const auto game_state = level_state.exchange({}, std::memory_order_relaxed);
    AudioController::playSounds(game_state.level.players[playerIndex].sounds);

    if (currentScene == game_state.level.v.index()) {
      SDL_RenderClear(renderer);

      vista->update(game_state);

      SDL_RenderPresent(renderer);
    } else {
      currentScene = game_state.level.v.index();
      vista = getSceneView(currentScene, playerIndex);
      exitStatus = std::holds_alternative<bool>(game_state.level.v)
                       && *std::get_if<bool>(&game_state.level.v)
                     ? game_state.players[playerIndex].lives == 0
                         ? ExitStatus::GAME_OVER
                         : ExitStatus::GAME_COMPLETE
                     : ExitStatus::CONNECTION_CLOSED;
    }

    quitRequested = SDL_QuitRequested();
  }

  Network::close_connection(socket);
  sender.join();
  receiver.join();

  return quitRequested ? ExitStatus::QUIT_REQUESTED : exitStatus;
}

void
sendControls(int socket)
{
  unsigned char controls{};

  while (!quitRequested && serverOpen.load(std::memory_order_relaxed)) {
    std::this_thread::sleep_for(std::chrono::milliseconds{ 10 });
    if (const auto aux = controls;
        aux != (controls = MarioController::getControls())
        && !dataTransfer::sendData(socket, &controls, sizeof controls))
      serverOpen.store(false, std::memory_order_relaxed);
  }
}

void
receiveState(int socket, std::atomic<GameState> *lsh)
{
  GameState new_state{ { { "---", 0, 0 } }, {} };
  while (!quitRequested && serverOpen.load(std::memory_order_relaxed)) {
    if (!dataTransfer::receiveData(socket, &new_state, sizeof new_state))
      serverOpen.store(false, std::memory_order_relaxed);
    lsh->store(new_state, std::memory_order_relaxed);
    lsh->notify_all();
  }
}

std::unique_ptr<SceneVista>
Client::getSceneView(std::size_t sceneNumber, std::size_t playerIndex)
{
  switch (sceneNumber) {
  case 1:
    return std::make_unique<Nivel1Vista>(playerIndex);
  case 2:
    return std::make_unique<Nivel2Vista>(playerIndex);
  case 3:
    return std::make_unique<InterludeVista>();
  default:
    return {};
  }
}

Login
Client::login(int socket)
{
  StartPage startPage{};
  Login response;
  do {
    const auto user = startPage.getLoginUser();
    if (quitRequested)
      return Login::ABORTED;

    response = auth(socket, user);
    if (response == Login::OK)
      std::memcpy(name, user.username, 3);
    else
      startPage.setResponse(response);
  } while (response != Login::OK && response != Login::ABORTED);

  return response;
}

Login
auth(int socket, user_t user)
{
  auto response = Login::ABORTED;

  dataTransfer::sendData(socket, &user, sizeof user);
  dataTransfer::receiveData(socket, &response, sizeof response);

  return response;
}
