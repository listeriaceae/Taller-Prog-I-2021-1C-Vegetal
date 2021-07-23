#include "Barril.h"

const int VELOCIDAD_INICIAL_X = 1;
const int VELOCIDAD_INICIAL_Y = 0;

const std::array<std::pair<punto_t,punto_t>, 12> Barril::direcciones{
        std::make_pair(punto_t{128, 84 - ALTO_BARRIL}, punto_t{1, 0.0625}),
        std::make_pair(punto_t{208, 89 - ALTO_BARRIL}, punto_t{0, 1}),
        std::make_pair(punto_t{208, 110 - ALTO_BARRIL}, punto_t{-1, 0.0625}),
        std::make_pair(punto_t{16 - ANCHO_BARRIL, 122.75 - ALTO_BARRIL}, punto_t{0, 1}),
        std::make_pair(punto_t{16 - ANCHO_BARRIL, 142.75 - ALTO_BARRIL}, punto_t{1, 0.0625}),
        std::make_pair(punto_t{208, 155.5 - ALTO_BARRIL}, punto_t{0, 1}),
        std::make_pair(punto_t{208, 175.5 - ALTO_BARRIL}, punto_t{-1, 0.0625}),
        std::make_pair(punto_t{16 - ANCHO_BARRIL, 188.25 - ALTO_BARRIL}, punto_t{0, 1}),
        std::make_pair(punto_t{16 - ANCHO_BARRIL, 208.25 - ALTO_BARRIL}, punto_t{1, 0.0625}),
        std::make_pair(punto_t{208, 221 - ALTO_BARRIL}, punto_t{0, 1}),
        std::make_pair(punto_t{208, 241 - ALTO_BARRIL}, punto_t{1, 0}),
        {}
    };

Barril::Barril()
: Entidad(N2_POS_X_BARRIL, N2_POS_Y_BARRIL, ANCHO_BARRIL, ALTO_BARRIL), vel{VELOCIDAD_INICIAL_X, VELOCIDAD_INICIAL_Y} {}

void Barril::mover() {
    pos.x += vel.x;
    pos.y += vel.y;
    if (pos == direcciones[direcciones_index].first) {
        vel = direcciones[direcciones_index++].second;
    }
}

bool Barril::estaEnNivel() {
    return pos.x < ANCHO_NIVEL;
}

dimensiones_t Barril::dimensions() const {
    return {pos.x, pos.y, pos.x + ANCHO_BARRIL, pos.y + ALTO_BARRIL};
 }