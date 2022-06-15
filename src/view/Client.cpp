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
#include "../configuration.hpp"
#include "../logger.hpp"
#include "../controller/MarioController.hpp"
#include "../controller/AudioController.hpp"
#include "../utils/window.hpp"
#include "../utils/Constants.hpp"
#include "../utils/estadoJuego.hpp"
#include "../utils/dataTransfer.hpp"
#include "../utils/textureHandler.hpp"

#define SERVER_CONNECTION_SUCCESS 0
#define START_PAGE_SUCCESS 0

bool quitRequested{ false };
SDL_Renderer *renderer{ nullptr };
SDL_Texture *texture{ nullptr };
static SDL_Window *window{ nullptr };

static std::atomic<bool> serverOpen{ true };
static int clientSocket{ -1 };

static void receiveState(std::atomic<GameState> *lsh);
static void sendControls();

int Client::connectToServer(const char *serverIp, std::uint16_t port)
{
  std::cout << "Conectando al servidor: " << serverIp << " puerto: " << port << '\n';

  // socket
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket == -1) {
    perror("ERROR opening socket");
    return EXIT_FAILURE;
  }

  struct sockaddr_in serverAddress;

  memset(&serverAddress, 0, sizeof serverAddress);
  serverAddress.sin_addr.s_addr = inet_addr(serverIp);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(port);

  // connect
  if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof serverAddress) != 0) {
    perror("ERROR connecting");
    close(clientSocket);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

Client::Client()
{
  SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  window = SDL_CreateWindow("Donkey Kong 2: Jumpman Returns",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            ANCHO_PANTALLA,
                            ALTO_PANTALLA,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  textureHandler::load();
  AudioController::loadAudioFiles();

  puts("Aplicación iniciada en modo cliente");
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

int Client::startClient()
{
  if (this->showStartPage() == EXIT_FAILURE)
    return EXIT_FAILURE;

  if (serverOpen.load(std::memory_order_relaxed)) {
    showMessage::waitingLobby();
    processExit(startGame());
  } else {
    processExit(ExitStatus::CONNECTION_CLOSED);
  }
  close(clientSocket);
  return EXIT_SUCCESS;
}

void Client::processExit(ExitStatus exitStatus)
{
  switch (exitStatus) {
  case ExitStatus::CONNECTION_CLOSED:
    logger::Logger::getInstance()
        .logInformation(fmt::format("[{}] connection closed", this->name));
    showMessage::disconnection();
    break;
  case ExitStatus::GAME_OVER:
    logger::Logger::getInstance()
        .logInformation(fmt::format("[{}] game over", this->name));
    showMessage::gameOver();
    break;
  case ExitStatus::GAME_COMPLETE:
    logger::Logger::getInstance()
        .logInformation(fmt::format("[{}] game complete", this->name));
    showMessage::gameComplete();
    break;
  case ExitStatus::QUIT_REQUESTED:
    logger::Logger::getInstance()
        .logInformation(fmt::format("[{}] quit requested", this->name));
    return;
  default:
    break;
  }
  while (!SDL_QuitRequested()) {
    std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
    AudioController::checkToggleMusicEvent(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_M]);
  };
}

ExitStatus
  Client::startGame()
{
  AudioController::startMusic();

  logger::Logger::getInstance().setLogLevel(
    configuration::GameConfiguration::getInstance(CONFIG_FILE).getLogLevel());

  std::size_t currentScene{ std::numeric_limits<std::size_t>::max() };
  std::unique_ptr<SceneVista> vista{};
  std::atomic<GameState> level_state{};

  std::thread receiver{ receiveState, &level_state };
  std::thread sender{ sendControls };

  level_state.wait({}, std::memory_order_relaxed);
  const std::size_t playerIndex = [&](){
    std::size_t match{ std::numeric_limits<std::size_t>::max() };
    const auto game_state = level_state.load(std::memory_order_relaxed);
    for (std::size_t i = 0; i < MAX_PLAYERS; ++i)
      if (strncmp(game_state.players[i].name, name, 3) == 0)
        match = i;
    return match;
  }();

  ExitStatus exitStatus = ExitStatus::CONNECTION_CLOSED;
  while (!quitRequested && serverOpen.load(std::memory_order_relaxed)) {
    level_state.wait({}, std::memory_order_relaxed);
    const auto game_state = level_state.exchange({}, std::memory_order_relaxed);
    AudioController::playSounds(
      game_state.level.players[playerIndex].sounds);

    if (currentScene == game_state.level.v.index()) {
      SDL_RenderClear(renderer);

      vista->update(game_state);

      SDL_RenderPresent(renderer);
    } else {
      currentScene = game_state.level.v.index();
      vista = getSceneView(currentScene, playerIndex);
      exitStatus =
        std::holds_alternative<bool>(game_state.level.v) && *std::get_if<bool>(&game_state.level.v)
          ? game_state.players[playerIndex].lives == 0
              ? ExitStatus::GAME_OVER
              : ExitStatus::GAME_COMPLETE
          : ExitStatus::CONNECTION_CLOSED;
    }

    quitRequested = SDL_QuitRequested();
  }
  shutdown(clientSocket, SHUT_RDWR);
  sender.join();
  receiver.join();

  return quitRequested ? ExitStatus::QUIT_REQUESTED : exitStatus;
}

static void
  sendControls()
{
  unsigned char controls{};

  while (!quitRequested && serverOpen.load(std::memory_order_relaxed)) {
    std::this_thread::sleep_for(std::chrono::milliseconds{ 10 });
    if (const auto aux = controls;
        aux != (controls = MarioController::getControls()) &&
        !dataTransfer::sendData(clientSocket, &controls, sizeof controls))
      serverOpen.store(false, std::memory_order_relaxed);
  }
}

static void
  receiveState(std::atomic<GameState> *lsh)
{
  GameState new_state{ { { "---" } } };
  while (!quitRequested && serverOpen.load(std::memory_order_relaxed)) {
    if (!dataTransfer::receiveData(clientSocket, &new_state, sizeof new_state))
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

int Client::showStartPage()
{
  StartPage startPage{};
  Login response;
  do {
    const auto user = startPage.getLoginUser();
    if (quitRequested)
      return EXIT_FAILURE;

    response = login(user);
    if (response == Login::OK) {
      memcpy(name, user.username, 3);
      name[3] = '\0';
    } else {
      startPage.setResponse(response);
    }
  } while (response != Login::OK && serverOpen);

  return EXIT_SUCCESS;
}

Login Client::login(user_t user)
{
  dataTransfer::sendData(clientSocket, &user, sizeof user);
  auto response = Login::ABORTED;
  if (!dataTransfer::receiveData(clientSocket, &response, sizeof response))
    serverOpen.store(false, std::memory_order_relaxed);
  return response;
}
