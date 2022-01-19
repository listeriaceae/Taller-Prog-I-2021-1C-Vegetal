#include <iostream>
#include <charconv>
#include "../model/Server.hpp"

int main(int argc, char *argv[])
{
  if (argc < 2) {
    std::cerr << "ERROR, no port provided\n";
    return 1;
  } else {
    std::uint16_t port;
    auto res = std::from_chars(argv[1], nullptr, port);
    if (res.ec == std::errc::invalid_argument || res.ec == std::errc::result_out_of_range || *res.ptr != '\0') {
      std::cerr << "ERROR, invalid port\n";
      return EXIT_FAILURE;
    }
    if (Server::serverListen(port) == EXIT_FAILURE)
      return EXIT_FAILURE;

    Server server{};
    server.startServer();
  }

  return 0;
}
