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

void TileSet::putTile(int id, Tile *tile) {
    tiles.insert(id, tile);
}

Tile *TileSet::getTile(int id) {
    int firshgid = properties.value("firstgid").toInt();
    int delta = id - firshgid;
    return tiles[delta];
}

QList<Tile*> TileSet::getTiles() {
    return tiles.values();
}
