#ifndef TILESETS_H
#define TILESETS_H

#include <QVector>

#include "tileset.h"

class TileSets {
public:
    QList<TileSet> tileSets;
public:
    TileSets();
    void addTileSet(TileSet tileSet);
    TileSet *getTileSet(int index);
    QList<TileSet> getTileSets();
    Tile *getTile(int id);
};

#endif // TILESETS_H
