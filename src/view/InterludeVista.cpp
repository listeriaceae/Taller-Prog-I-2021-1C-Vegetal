#include "InterludeVista.h"
#include "../TextRenderer.h"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

#define OFFSET_SCORE 36 * ANCHO_PANTALLA / (float)ANCHO_NIVEL

InterludeVista::InterludeVista(SDL_Renderer *renderer) : SceneVista(), renderer{renderer} {}

void InterludeVista::update(const estadoJuego_t &estadoJuego) {
    punto_t statsJugadorPos{};
    auto textRenderer = TextRenderer::getInstance(renderer);
    for (auto &statsJugador : estadoJuego.players) {
        textRenderer->renderText(statsJugadorPos, statsJugador.name, 2, LIME);
        const char score_str[7]{'0',
                                static_cast<char>('0' + (statsJugador.score / 100) % 10),
                                static_cast<char>('0' + (statsJugador.score / 10) % 10),
                                static_cast<char>('0' + statsJugador.score % 10),
                                '0',
                                '0'};
        
        textRenderer->renderText({statsJugadorPos.x + OFFSET_SCORE, statsJugadorPos.y}, score_str, 2, CYAN);
    }
}