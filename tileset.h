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
    Tile *getGlobalTile(int id);
    Tile *getLocalTile(int id);
    QList<Tile*> getTiles();

    int firshgid;
};

#endif // TILESET_H
