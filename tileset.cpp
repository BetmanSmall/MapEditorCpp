#include "tileset.h"

TileSet::TileSet() {

}

TileSet::TileSet(QString name) {
    this->name = name;
}

void TileSet::setName(QString name) {
    this->name = name;
}

QString TileSet::getName() {
    return name;
}

QMap<QString, QString> *TileSet::getProperties() {
    return &properties;
}

void TileSet::putTile(int id, Tile tile) {
    tiles.insert(id, tile);
}

Tile *TileSet::getTile(int id) {
    return &(tiles[id]);
}
