#pragma once

#include "../model/Mario.hpp"
#include "user.h"

typedef struct player
{
    char user[4];
    Mario *mario;
    int clientSocket;
    bool isConnected;
} player_t;