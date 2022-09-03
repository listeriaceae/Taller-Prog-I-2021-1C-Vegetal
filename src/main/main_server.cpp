#include <iostream>
#include <charconv>
#include "../configuration.hpp"
#include "../logger.hpp"
#include "../model/Server.hpp"
#include "../utils/tcp_server.hpp"

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    std::cerr << "ERROR, no port provided\n";
    return EXIT_FAILURE;
  }

  configuration::init("archivo.json");
  logger::setLogLevel(configuration::getLogLevel());

  std::uint16_t port;
  if (const auto res = std::from_chars(argv[1], nullptr, port);
      res.ec == std::errc::invalid_argument
      || res.ec == std::errc::result_out_of_range || *res.ptr != '\0') {
    std::cerr << "ERROR, invalid port: " << argv[1] << '\n';
    return EXIT_FAILURE;
  }

  int socket = Network::listen_on(port);
  if (socket == -1)
    return EXIT_FAILURE;

  Server server{};
  logger::logNewGame();

  auto accept_loop = [&](int socket) {
    server.start_game_cv.mtx.lock();

    int client;
    while ((client = Network::accept_from(socket)) != -1)
      std::thread(&Server::handleLogin, &server, client).detach();

    if (errno != EBADF && errno != EINVAL) {
      perror("ERROR on accept");
      exit(EXIT_FAILURE);
    }
  };

  std::thread accept_connections;
  {
    std::unique_lock lk{ server.start_game_cv.mtx };
    accept_connections = std::thread(accept_loop, socket);

    server.start_game_cv.cv.wait(lk, [&]() {
      return server.connectedPlayers.players.size() == server.maxPlayers;
    });
  }

  server.startGame();

  Network::close_connection(socket);
  accept_connections.join();

  return 0;
}
