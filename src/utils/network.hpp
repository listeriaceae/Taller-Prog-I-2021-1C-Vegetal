#ifndef NETWORK_H
#define NETWORK_H

#include <cstdint>

namespace Network {
int listen_on(std::uint16_t port);
int accept_from(int fd);
int close_connection(int fd);

int connect_to(const char *ip, std::uint16_t port);
}// namespace Network

#endif// NETWORK_H
