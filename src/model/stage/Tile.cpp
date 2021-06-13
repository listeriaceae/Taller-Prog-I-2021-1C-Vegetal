#include "Tile.h"

void Tile::addPlatform(Platform *platform) {
    platforms.push_back(platform);
}

void Tile::getPlatforms(std::list<Platform *> *platforms) {
    for (Platform *platform : this->platforms) {
        platforms->push_back(platform);
    }
}

void Tile::setLadderBottom(Ladder *ladder) {
    ladderBottom = ladder;
}

void Tile::setLadderTop(Ladder *ladder) {
    ladderTop = ladder;
}

Ladder *Tile::getLadderBottom() {
    return ladderBottom;
}

Ladder *Tile::getLadderTop() {
    return ladderTop;
}

Tile::~Tile() {
    platforms.clear();
}