#ifndef TILESET_H
#define TILESET_H

#include <QMap>

#include "tile.h"

class TileSet {
    QString name;
    QMap<int, Tile> tiles;
    QMap<QString, QString> properties;
public:
    TileSet(QString name);
    void setName(QString name);
    QString getName();
    QMap<QString, QString> *getProperties();
    void putTile(int id, Tile tile);
    Tile *
};

#endif // TILESET_H
