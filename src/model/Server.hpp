#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include "../utils/player.hpp"

class Server
{
public:
  Server();
  int startServer();

  static int serverListen(std::uint16_t port);

  std::unordered_map<std::string, std::string> users{};
  size_t maxPlayers{};
  struct
  {
    std::vector<player_t> players;
    std::mutex mtx;
  } connectedPlayers{};
  struct
  {
    std::condition_variable cv;
    std::mutex mtx;
  } start_game_cv{};

private:
  void startGame();
};

#endif// SERVER_H
