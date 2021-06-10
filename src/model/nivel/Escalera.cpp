#include "Escalera.h"
#include <string>

Escalera::Escalera(std::string name, int center, int x_0, int x_1, int y_0, int y_1){
    this->name = name;
    this->center = center;
    this->x_0 = x_0; 
    this->x_1 = x_1;
    this->y_0 = y_0;
    this->y_1 = y_1;
}

std::string Escalera::getName() {
    return this->name;
}

int Escalera::getCenter() {
    return this->center;
}

int Escalera::getX0(){
    return this->x_0;
}

int Escalera::getX1(){
    return this->x_1;
}

int Escalera::getY0(){
    return this->y_0;
}

int Escalera::getY1(){
    return this->y_1;
}