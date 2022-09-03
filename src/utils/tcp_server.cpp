#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include "tcp_server.hpp"

namespace {
int
bind_port(std::uint16_t port, int fd)
{
  struct sockaddr_in address;
  std::memset(&address, 0, sizeof address);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  return bind(fd, (struct sockaddr *) &address, sizeof address);
}

int
listen_error(const char *err, int fd)
{
  perror(err);
  if (fd != -1)
    close(fd);
  return -1;
}
}

int
Network::listen_on(std::uint16_t port)
{
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1)
    return listen_error("ERROR creating socket", fd);

  if (bind_port(port, fd) == -1)
    return listen_error("ERROR on bind", fd);
      
  if (listen(fd, 4) == -1)
    return listen_error("ERROR on listen", fd);

  return fd;
}

int
Network::accept_from(int fd)
{
  return accept(fd, NULL, NULL);
}

int
Network::close_connection(int fd)
{
  shutdown(fd, SHUT_RDWR);
  return close(fd);
}
