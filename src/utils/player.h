#pragma once

class Mario;

typedef struct player
{
    char user[4];
    Mario *mario;
    int clientSocket;
    bool isConnected;
} player_t;