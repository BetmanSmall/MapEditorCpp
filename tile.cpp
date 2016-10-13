#include "tile.h"

Tile::Tile(QPixmap pixmap) {
    this->pixmap = pixmap;
}

void Tile::setId(int id) {
    this->id = id;
}

int Tile::getId() {
    return id;
}

void Tile::setOffsetX(float offsetX) {
    this->offsetX = offsetX;
}

void Tile::setOffsetY(float offsetY) {
    this->offsetY = offsetY;
}
