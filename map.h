#ifndef MAP_H
#define MAP_H

#include <QDebug>

#include "tilesets.h"
#include "maplayers.h"

class Map {
public:
    QString mapPath;
    TileSets tileSets;
    MapLayers mapLayers;
    QMap<QString, QString> properties;
    int width, height;

public:
    Map();
    QMap<QString, QString> *getProperties();
    TileSets *getTileSets();
    MapLayers *getMapLayers();
//    void loadMap(QString fileName);
//    QString findFile(QString filePath);
    void turnRight();
    void turnLeft();
    void flipX();
    void flipY();
private:
};

#endif // MAP_H
