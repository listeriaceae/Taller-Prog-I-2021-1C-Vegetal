#include <iostream>
#include <charconv>
#include "../configuration.hpp"
#include "../logger.hpp"
#include "../view/Client.hpp"
#include "../utils/network.hpp"

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    std::cerr << "Use: " << argv[0] << " ip port\n";
    return EXIT_FAILURE;
  }

  configuration::init("config.json");
  logger::setLogLevel(configuration::getLogLevel());

  std::uint16_t port;
  auto res = std::from_chars(argv[2], nullptr, port);
  if (res.ec == std::errc::invalid_argument
      || res.ec == std::errc::result_out_of_range || *res.ptr != '\0') {
    std::cerr << "ERROR, invalid port\n";
    return EXIT_FAILURE;
  }

  int socket = Network::connect_to(argv[1], port);

  if (socket == -1)
    return EXIT_FAILURE;

  Client client{};

  if (client.login(socket) == Login::OK)
    client.startClient(socket);
  else
    Network::close_connection(socket);

  return 0;
}
