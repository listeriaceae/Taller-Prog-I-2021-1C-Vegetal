#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include "../utils/player.hpp"
#include "../utils/user.hpp"

enum class Login;

class Server
{
public:
  Server();
  ~Server();
  void handleLogin(int client);
  void startGame();

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
  Login validateUserLogin(int client);
};

#endif// SERVER_H
