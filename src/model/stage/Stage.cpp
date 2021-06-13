#include "Stage.h"

#define STAGE_WIDTH (ANCHO_NIVEL / ANCHO_TILE)
#define STAGE_HEIGHT (ALTO_NIVEL / ALTO_TILE)
#define GRID_COLS (STAGE_WIDTH + 1)

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

}

bool Stage::collide(float *x, float *y, float *dx, float *dy) {
    unsigned int i = ((int)(*y) / STAGE_HEIGHT) * GRID_COLS + (int)(*x) / STAGE_WIDTH;
    std::list<Platform *> platforms;
    for (Platform *platform : platforms) {
        
    }
}