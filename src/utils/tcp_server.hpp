#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <cstdint>

namespace Network {
int listen_on(std::uint16_t port);
int accept_from(int fd);
int close_connection(int fd);
}// namespace Network

#endif// TCP_SERVER_H
