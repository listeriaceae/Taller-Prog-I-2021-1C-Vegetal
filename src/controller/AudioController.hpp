#ifndef AUDIO_CONTROLLER_H
#define AUDIO_CONTROLLER_H

namespace AudioController {
void loadAudioFiles();
void closeAudioFiles();

void startMusic();
void checkToggleMusicEvent(int m_state);
void playSounds(int sounds);
}// namespace AudioController

#endif// AUDIO_CONTROLLER_H
