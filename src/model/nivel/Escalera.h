#pragma once

#include <string>

class Escalera
{
    public:
        Escalera(std::string name, int center, int x_0, int x_1, int y_0, int y_1);
        int getX0();
        int getX1();
        int getY0();
        int getY1();
        std::string getName();
        int getCenter();

    private:
        std::string name;
        int x_0;
        int x_1;
        int y_0;
        int y_1;
        int center;
};