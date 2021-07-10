#pragma once
#include <string>

class AudioObserver {
public:
    AudioObserver();
    void update(std::string event);
    void reset();
    char getState();
private:
    char sounds; 
};