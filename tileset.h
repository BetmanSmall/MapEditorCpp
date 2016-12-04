#ifndef TILESET_H
#define TILESET_H

#include <QMap>

#include "tile.h"

class TileSet {
    QString name;
    QMap<int, Tile*> tiles;
    QMap<QString, QString> properties;
public:
    TileSet();
    TileSet(QString name);
    void setName(QString name);
    QString getName();
    QMap<QString, QString> *getProperties();
    void putTile(int id, Tile *tile);
    Tile *getTile(int id);
    QList<Tile*> getTiles();
};

#endif // TILESET_H
