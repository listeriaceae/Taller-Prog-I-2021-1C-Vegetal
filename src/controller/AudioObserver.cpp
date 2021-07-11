#include "AudioObserver.h"

const int JUMP_SOUND_CODE = 1;
const int DEATH_SOUND_CODE = 2;
AudioObserver::AudioObserver() { }

void AudioObserver::update(std::string event) {
    if(event == "salto") {
        sounds.jump = 1;
    }
    else if(event == "death") {
        sounds.death = 1;
    }
}

void AudioObserver::reset() {
    sounds.jump = 0;
    sounds.death = 0;
}

sounds_t AudioObserver::getState() {
    return sounds;
}