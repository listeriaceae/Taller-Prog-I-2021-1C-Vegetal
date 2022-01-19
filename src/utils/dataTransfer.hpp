#ifndef DATA_TRANSFER_H
#define DATA_TRANSFER_H

#include <cstddef>

namespace dataTransfer {
bool sendData(int clientSocket, const void *data, size_t size);
bool receiveData(int clientSocket, void *data, size_t size);
}// namespace dataTransfer

#endif// DATA_TRANSFER_H
