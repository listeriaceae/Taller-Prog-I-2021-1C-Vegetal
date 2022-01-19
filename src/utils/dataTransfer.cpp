#include <sys/socket.h>
#include "dataTransfer.hpp"

bool dataTransfer::sendData(int clientSocket, const void *data, size_t size)
{
  size_t totalBytesSent = 0;
  ssize_t bytesSent = 0;

  while (totalBytesSent < size) {
    bytesSent = send(clientSocket,
      reinterpret_cast<const std::byte *>(data) + totalBytesSent,
      size - totalBytesSent,
      MSG_NOSIGNAL);
    if (bytesSent > 0) {
      totalBytesSent += bytesSent;
    } else {
      break;
    }
  }
  return totalBytesSent == size;
}

bool dataTransfer::receiveData(int clientSocket, void *data, size_t size)
{
  size_t totalBytesReceived = 0;
  ssize_t bytesReceived = 0;

  while (totalBytesReceived < size) {
    bytesReceived = recv(clientSocket,
      reinterpret_cast<std::byte *>(data) + totalBytesReceived,
      size - totalBytesReceived,
      MSG_NOSIGNAL);
    if (bytesReceived > 0) {
      totalBytesReceived += bytesReceived;
    } else {
      break;
    }
  }

  return totalBytesReceived == size;
}
