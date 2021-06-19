#include "Tile.h"

void Tile::addPlatform(Platform *platform) {
    platforms.push_back(platform);
}

void Tile::getPlatforms(std::unordered_set<Platform *> *platforms) {
    platforms->insert(this->platforms.begin(), this->platforms.end());
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
    delete ladderBottom;
}