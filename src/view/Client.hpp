#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include "../utils/user.hpp"
#include "../utils/exitStatus.hpp"
#include "SceneVista.hpp"

enum class Login;
typedef struct SDL_Window SDL_Window;

class Client
{
public:
  Client();
  ~Client();
  Login login(int socket);
  void startClient(int socket);

private:
  ExitStatus startGame(int socket);
  std::unique_ptr<SceneVista> getSceneView(std::size_t sceneNumber,
                                           std::size_t playerIndex);
  void processExit(ExitStatus clientExitStatus);

  char name[4] = "---";
  SDL_Window *window{ nullptr };
};

#endif// CLIENT_H
