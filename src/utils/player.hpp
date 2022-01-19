#ifndef PLAYER_H
#define PLAYER_H

class Mario;

typedef struct player
{
  Mario *mario;
  int clientSocket;
  bool isConnected;
  char user[4];
} player_t;

#endif// PLAYER_H
