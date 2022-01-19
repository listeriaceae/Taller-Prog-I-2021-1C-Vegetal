#include <array>
#include "MarioVista.hpp"
#include "HammerVista.hpp"
#include "../utils/Constants.hpp"
#include "../utils/window.hpp"

#define MARIO_TREPANDO_INDEX 3
#define MARIO_DE_ESPALDAS_INDEX 6
#define MARIO_SALTANDO_INDEX 13
#define MARIO_MURIENDO_INDEX 15
#define MARIO_MUERTO_INDEX 17
#define MARIO_POSE_MARTILLO_INDEX 7

#define TIEMPO_FRAME_MUERTO 16
#define TIEMPO_POR_FRAME_MARTILLO 4
#define TIEMPO_POR_FRAME_CORRIENDO 3
#define CANT_FRAMES 24
#define CANT_FRAMES_MARTILLO 2
#define MARIO_SPRITE_SIZE 16

extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

MarioVista::MarioVista()
  : srcRect{ 0, 256, ANCHO_MARIO, ALTO_MARIO }, dstRect{
      0,
      0,
      static_cast<int>(round(ANCHO_MARIO * ANCHO_PANTALLA / (float)ANCHO_NIVEL)),
      static_cast<int>(round(ALTO_MARIO * ALTO_PANTALLA / (float)ALTO_NIVEL))
    }
{
}

void MarioVista::setColor(int color)
{
  srcRect.y = 256 + (color << 4);
}

void MarioVista::mostrar(const PlayerState &estadoMario)
{
  const int nextX = static_cast<int>(round(from_fixed16<float>(estadoMario.pos.x) * (ANCHO_PANTALLA / (float)ANCHO_NIVEL)));
  const int nextY = static_cast<int>(round(from_fixed16<float>(estadoMario.pos.y) * (ANCHO_PANTALLA / (float)ANCHO_NIVEL)));
  switch (estadoMario.estado) {
  case Estado::REPOSO:
  case Estado::DE_ESPALDAS:
    updateReposo(estadoMario.estado, estadoMario.collider);
    break;
  case Estado::CORRIENDO:
    updateCorriendo(nextX, estadoMario.collider);
    break;
  case Estado::SALTANDO:
    updateSaltando(nextX);
    break;
  case Estado::TREPANDO:
    updateTrepando(nextY);
    break;
  case Estado::MURIENDO:
  case Estado::MUERTO:
    updateMuriendo(estadoMario.estado);
    break;
  case Estado::NIVEL_COMPLETO:
    updateNivelCompleto();
    break;
  case Estado::GAME_OVER:
    return;
  }
  dstRect.x = nextX;
  dstRect.y = nextY;
  SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0., NULL, flip);
}

void MarioVista::updateReposo(Estado estado, ColliderType collider)
{
  switch (collider) {
  case ColliderType::NORMAL:
    srcRect.x = estado == Estado::DE_ESPALDAS
                  ? MARIO_DE_ESPALDAS_INDEX * MARIO_SPRITE_SIZE
                  : 0;
    break;

  case ColliderType::HAMMER:
    drawHammer();
    srcRect.x = MARIO_POSE_MARTILLO_INDEX * MARIO_SPRITE_SIZE + (hammerTime & 16);
    break;
  }
}

void MarioVista::updateCorriendo(int nextX, ColliderType collider)
{
  static constexpr std::array<int, 4> sprite_index{ 0, 1, 0, 2 };

  flip = static_cast<SDL_RendererFlip>((dstRect.x < nextX) | (static_cast<int>(flip) & (dstRect.x == nextX)));
  tiempo = (tiempo + (dstRect.x != nextX)) % (TIEMPO_POR_FRAME_CORRIENDO * CANT_FRAMES);
  switch (collider) {
  case ColliderType::NORMAL:
    srcRect.x = sprite_index[(tiempo / TIEMPO_POR_FRAME_CORRIENDO) & 3] << 4;
    break;

  case ColliderType::HAMMER:
    drawHammer();
    srcRect.x = (sprite_index[(tiempo / TIEMPO_POR_FRAME_CORRIENDO) & 3] << 5) + (hammerTime & 16) + MARIO_POSE_MARTILLO_INDEX * MARIO_SPRITE_SIZE;
    break;
  }
}

void MarioVista::updateSaltando(int nextX)
{
  flip = static_cast<SDL_RendererFlip>((dstRect.x < nextX) | (static_cast<int>(flip) & (dstRect.x == nextX)));
  srcRect.x = MARIO_SALTANDO_INDEX * MARIO_SPRITE_SIZE;
}

void MarioVista::updateTrepando(int nextY)
{
  tiempo += dstRect.y != nextY;
  flip = static_cast<SDL_RendererFlip>((tiempo & 8) >> 3);
  srcRect.x = MARIO_TREPANDO_INDEX * MARIO_SPRITE_SIZE;
}

void MarioVista::updateMuriendo(Estado estado)
{
  tiempo = srcRect.x >= MARIO_MURIENDO_INDEX * MARIO_SPRITE_SIZE ? tiempo + 1 : 0;
  if (estado == Estado::MURIENDO) {
    const int sprite = (tiempo >> 4) & 3;
    srcRect.x = (MARIO_MURIENDO_INDEX + 1 - (sprite & 1)) << 4;
    flip = static_cast<SDL_RendererFlip>((sprite > 1) * (sprite - 1));
  } else {
    flip = SDL_FLIP_NONE;
    srcRect.x = MARIO_MUERTO_INDEX * MARIO_SPRITE_SIZE;
  }
}

void MarioVista::updateNivelCompleto()
{
  flip = SDL_FLIP_NONE;
  srcRect.x = 0;
}

void MarioVista::drawHammer()
{
  hammerTime += 2;
  HammerVista::mostrar(
    dstRect.x, dstRect.y, static_cast<EstadoHammer>((hammerTime & 16) >> 4), flip);
}
