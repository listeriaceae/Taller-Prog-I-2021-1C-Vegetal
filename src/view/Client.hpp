#ifndef CLIENT_H
#define CLIENT_H

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
  void processExit(ExitStatus status);

  char name[4] = "---";
  SDL_Window *window{ nullptr };
};

#endif// CLIENT_H
