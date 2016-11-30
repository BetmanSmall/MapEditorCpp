#ifndef TILESETS_H
#define TILESETS_H

#include <QVector>

#include "tileset.h"

class TileSets {
public:
    QVector<TileSet> tileSets;
public:
    TileSets();
    void addTileSet(TileSet tileSet);
    TileSet getTileSet(int index);
};

#endif // TILESETS_H
