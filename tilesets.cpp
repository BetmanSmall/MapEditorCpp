#include "tilesets.h"

TileSets::TileSets() {

}

void TileSets::addTileSet(TileSet tileSet) {
    this->tileSets.append(tileSet);
}

TileSet *TileSets::getTileSet(int index) {
    return &(tileSets[index]);
}

QList<TileSet> TileSets::getTileSets() {
    return this->tileSets;
}

