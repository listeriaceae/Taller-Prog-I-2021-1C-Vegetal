#pragma once
#include "../utils/marioStructs.h"
#include <string>

class AudioObserver {
public:
    AudioObserver();
    void update(std::string event);
    void reset();
    sounds_t getState();
private:
    sounds_t sounds; 
};