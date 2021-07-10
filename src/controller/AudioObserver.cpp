#include "AudioObserver.h"

const int JUMP_SOUND_CODE = 1;
const int DEATH_SOUND_CODE = 2;
AudioObserver::AudioObserver() { }

void AudioObserver::update(std::string event) {
    if(event == "salto") {
        this->sounds += JUMP_SOUND_CODE;
    }
    else if(event == "death") {
        this->sounds += DEATH_SOUND_CODE;
    }
}

void AudioObserver::reset() {
    this->sounds = 0;
}

char AudioObserver::getState() {
    return sounds;
}