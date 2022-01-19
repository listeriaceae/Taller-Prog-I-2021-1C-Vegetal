#ifndef AUDIO_CONTROLLER_H
#define AUDIO_CONTROLLER_H

namespace AudioController {
void loadAudioFiles();
void closeAudioFiles();

void toggleMusic();
void checkToggleMusicEvent();
void playSounds(unsigned char sounds);
}// namespace AudioController

#endif// AUDIO_CONTROLLER_H
