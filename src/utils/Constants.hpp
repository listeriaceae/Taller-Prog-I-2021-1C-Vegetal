#pragma once

#include <string>

// Dimensiones
#define ANCHO_NIVEL 224
#define ALTO_NIVEL 256

#define ANCHO_BARRIL 12
#define ALTO_BARRIL 10

#define ANCHO_ENEMIGO_FUEGO 15
#define ALTO_ENEMIGO_FUEGO 16

#define ANCHO_FUEGO 16
#define ALTO_FUEGO 16

#define ANCHO_PLATAFORMA 16
#define ALTO_PLATAFORMA 8

#define ANCHO_POLEA 11
#define ALTO_POLEA 10

#define ANCHO_MARIO 16
#define ALTO_MARIO 16

#define DONKEYKONG_ANCHO 40
#define DONKEYKONG_ALTO 34
#define DONKEYKONG_POSX 24
#define DONKEYKONG_POSY 50

#define PEACH_POSX 88
#define PEACH_POSY 34
#define PEACH_ANCHO 16
#define PEACH_ALTO 22

#define POSX_BARRIL 16
#define POSY_BARRIL 232
#define ANCHO_FIRE_BARREL 16
#define ALTO_FIRE_BARREL 16

#define DEFAULT_CONFIG_X 56
#define DEFAULT_CONFIG_Y 20
#define ANCHO_DEFAULT_CONFIG 108
#define ALTO_DEFAULT_CONFIG 7

// Nivel 1
#define N1_MARIO_POS_X 2
#define N1_MARIO_POS_Y 232

#define N1_POSX_FUEGO1 48
#define N1_POSX_FUEGO2 88
#define N1_POSX_FUEGO3 128
#define N1_POSX_FUEGO4 168

#define N1_POSY_FUEGO 240

#define N1_POSX1_POLEA 10
#define N1_POSX2_POLEA 203

#define N1_POSY1_POLEA 128
#define N1_POSY2_POLEA 168

// Nive 2
#define N2_MARIO_POS_X 34
#define N2_MARIO_POS_Y 232

#define N2_POSX_FUEGO 16
#define N2_POSY_FUEGO 216

#define N2_POSY_BARRIL 30

// Name
const std::string NOMBRE_JUEGO = "Donkey Kong 2 Jumpman Returns";
// Config
const std::string CONFIG_FILE = "archivo.json";
// Default
const std::string IMG_DEFAULT = "res/default.png";

enum {
    REPOSO,
    CORRIENDO,
    SALTANDO,
    TREPANDO
};