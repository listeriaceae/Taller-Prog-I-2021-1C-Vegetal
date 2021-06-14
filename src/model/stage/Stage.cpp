#include <unordered_set>
#include "Stage.h"

#define STAGE_WIDTH (ANCHO_NIVEL / ANCHO_TILE)
#define STAGE_HEIGHT (ALTO_NIVEL / ALTO_TILE)
#define GRID_COLS (STAGE_WIDTH + 1)

Stage::Stage() {
    for (unsigned int i = 0; i < GRID_COLS * (STAGE_HEIGHT + 1); ++i) grid[i] = new Tile();
}

void Stage::addLadder(Ladder *ladder) {
    int x = (int)ladder->getX() / STAGE_WIDTH;
    int y = (int)ladder->getBottom() / STAGE_HEIGHT;
    grid[y * GRID_COLS + x]->setLadderBottom(ladder);

    y = (int)ladder->getTop() / STAGE_HEIGHT;
    grid[y * GRID_COLS + x]->setLadderTop(ladder);
}

Ladder *Stage::getLadder(float x, float y, float ySpeed) {
    unsigned int i = ((int)y / STAGE_HEIGHT) * GRID_COLS + ((int)x + ANCHO_TILE / 2) / STAGE_WIDTH;
    if (0 < ySpeed) return grid[i]->getLadderBottom();
    if (ySpeed < 0) return grid[i]->getLadderTop();
    return NULL;
}

void Stage::addPlatform(Platform *platform) {
    float x, max;
    platform->getLimits(&x, &max);
    while (x < max) {
        unsigned int i = ((int)platform->getY(x) / STAGE_HEIGHT) * GRID_COLS + (int)x / STAGE_WIDTH;
        grid[i]->addPlatform(platform);
        x += ANCHO_TILE;
    }
}

bool Stage::collide(float *x, float *y, float *dx, float *dy) {
    unsigned int i = ((int)(*y) / STAGE_HEIGHT) * GRID_COLS + (int)(*x) / STAGE_WIDTH;
    std::unordered_set<Platform *> platforms;
    grid[i]->getPlatforms(&platforms);
    grid[i + 1]->getPlatforms(&platforms);
    grid[i + GRID_COLS]->getPlatforms(&platforms);
    grid[i + (GRID_COLS + 1)]->getPlatforms(&platforms);

    bool is_standing = false;
    float min, max;
    for (auto it = platforms.begin(); it != platforms.end();) {
        (*it)->getCurrentLimits(&min, &max);
        if (min - ANCHO_MARIO < *x && *x < max) {
            float distance = *y + ALTO_MARIO - (*it)->getY(*x);
            if (0 <= distance) {
                int hit_floor = distance < 2;
                is_standing |= hit_floor;
                *y -= distance * hit_floor;
                *dy -= *dy * hit_floor;
                *x += hit_floor * (*it)->getSpeed();
                int hit_wall = !hit_floor && (distance < ALTO_MARIO);
                *x += (max - *x) * (std::abs(*x - max) < 1);
                *x += (min - ANCHO_MARIO - *x) * (std::abs(*x - (min - ANCHO_MARIO)) < 1);
                *dx -= *dx * hit_wall;
            }
        }
        it = platforms.erase(it);
    }
    return is_standing;
}

Stage::~Stage() {
    for (Tile *tile : grid) delete tile;
}