#pragma once

#include <string>

class MarioState {
    public:
        virtual void handleInput(char controls) = 0;
        virtual void update() = 0;
        virtual ~MarioState() = default;

        std::string getName();

    protected:
        std::string name;
};