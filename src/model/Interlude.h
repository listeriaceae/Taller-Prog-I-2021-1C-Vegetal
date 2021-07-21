#pragma once
#include "Scene.h"

#define INTERLUDE_DURATION 600

class Interlude : public Scene
{
public:
    Interlude(unsigned char sceneNumber) : Scene() { estadoNivel.scene = sceneNumber; };
    void update() override { ++ticks; };
    const estadoNivel_t &getEstado() override { return estadoNivel; };
    bool isComplete() const override { return ticks > INTERLUDE_DURATION; };
private:
    size_t ticks{};
};