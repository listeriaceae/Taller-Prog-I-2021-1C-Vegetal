#pragma once
#include "../utils/marioStructs.h"

class AudioObserver {
public:
    void update(sound_codes_t soundCode);
    void reset();
    sounds_t getState() const;
private:
    sounds_t sounds{0, 0}; 
};