#pragma once

#include "../Mario.hpp"
#include <string>

class Mario;

class MarioState {
    public:
        MarioState();
        virtual MarioState* handleInput(char controls, Mario* mario) = 0;
        virtual void update() = 0;
        virtual void perform() = 0;
        virtual ~MarioState() = default;

        std::string getName();

    protected:
        std::string name;
        float velX;
        float velY;
};