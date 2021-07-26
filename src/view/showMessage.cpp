#include "showMessage.h"
#include "../TextRenderer.h"
#include "../utils/window.hpp"
#include "../utils/Constants.hpp"

const char *const MSG_DISCONNECT_1 = "SE PERDIO LA CONEXION";
const char *const MSG_DISCONNECT_2 = "CON EL SERVIDOR";
const char *const MSG_GAME_OVER = "GAME OVER";
const char *const MSG_FELICITACIONES = "FELICITACIONES";
const char *const MSG_JUEGO_COMPLETADO = "JUEGO COMPLETADO";
const char *const MSG_WAITING_FOR_PLAYERS = "Esperando a jugadores...";

namespace showMessage {
    void waitingLobby(SDL_Renderer *renderer) {
        SDL_RenderClear(renderer);
        {
            const punto_t pos{12 * ANCHO_PANTALLA / (float)ANCHO_NIVEL,
                              112 * ALTO_PANTALLA / (float)ALTO_NIVEL};
            TextRenderer::getInstance(renderer)->renderText(pos, MSG_WAITING_FOR_PLAYERS, 1);
        }
        SDL_RenderPresent(renderer);
    }

    void disconnection(SDL_Renderer* renderer) {
        SDL_RenderClear(renderer);
        {
            const punto_t pos{18.5f * ANCHO_PANTALLA / (float)ANCHO_NIVEL,
                              112 * ALTO_PANTALLA / (float)ALTO_NIVEL};
            TextRenderer::getInstance(renderer)->renderText(pos, MSG_DISCONNECT_1, 1);
        }
        {
            const punto_t pos{45.5f * ANCHO_PANTALLA / (float)ANCHO_NIVEL,
                              122 * ALTO_PANTALLA / (float)ALTO_NIVEL};
            TextRenderer::getInstance(renderer)->renderText(pos, MSG_DISCONNECT_2, 1);
        }
        SDL_RenderPresent(renderer);
    }

    void gameOver(SDL_Renderer *renderer) {
        SDL_RenderClear(renderer);
        {
            const punto_t pos{32 * ANCHO_PANTALLA / (float)ANCHO_NIVEL,
                              112 * ALTO_PANTALLA / (float)ALTO_NIVEL};
            TextRenderer::getInstance(renderer)->renderText(pos, MSG_GAME_OVER, 2);
        }
        SDL_RenderPresent(renderer);
    }

    void gameComplete(SDL_Renderer *renderer) {
        SDL_RenderClear(renderer);
        {
            const punto_t pos{36 * ANCHO_PANTALLA / (float)ANCHO_NIVEL,
                              104 * ALTO_PANTALLA / (float)ALTO_NIVEL};
            TextRenderer::getInstance(renderer)->renderText(pos, MSG_FELICITACIONES, 1.25);
        }
        {
            const punto_t pos{24 * ANCHO_PANTALLA / (float)ANCHO_NIVEL,
                              122 * ALTO_PANTALLA / (float)ALTO_NIVEL};
            TextRenderer::getInstance(renderer)->renderText(pos, MSG_JUEGO_COMPLETADO, 1.25);
        }
        SDL_RenderPresent(renderer);
    }
}