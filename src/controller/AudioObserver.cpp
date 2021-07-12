#include "AudioObserver.h"

void AudioObserver::update(SoundCode soundCode) {
    switch (soundCode) {
        case JUMP:
            sounds.jump = 1;
            break;
        case DEATH:
            sounds.death = 1;
            break;
    }
}

void AudioObserver::reset() {
    sounds = {0, 0};
}

sounds_t AudioObserver::getState() const {
    return sounds;
}