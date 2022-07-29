#ifndef AUDIO_OBSERVER_H
#define AUDIO_OBSERVER_H

#include "../../utils/marioStructs.hpp"

class AudioObserver
{
public:
  constexpr void
  update(SoundCode soundCode)
  {
    sounds |= soundCode;
  }
  constexpr void
  reset()
  {
    sounds = {};
  }
  constexpr std::uint8_t
  getState() const
  {
    return sounds;
  }

private:
  std::uint8_t sounds{};
};

#endif// AUDIO_OBSERVER_H
