#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include "../utils/user.hpp"
#include "../utils/exitStatus.hpp"
#include "SceneVista.hpp"

enum class Login;

class Client
{
public:
  Client();
  ~Client();
  int startClient();

  static int connectToServer(const char *serverIp, std::uint16_t port);

private:
  ExitStatus startGame();
  int showStartPage();
  Login login(user_t user);
  std::unique_ptr<SceneVista> getSceneView(std::size_t sceneNumber,
                                           std::size_t playerIndex);
  void processExit(ExitStatus clientExitStatus);

  char name[4] = "---";
};

#endif// CLIENT_H
