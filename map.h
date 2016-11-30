#ifndef MAP_H
#define MAP_H

#include <QDebug>

#include "tilesets.h"

class Map {
public:
    QString mapPath;
    TileSets tileSets;
    QMap<QString, QString> properties;

public:
    Map();
    QMap<QString, QString> *getProperties();
    TileSets getTileSets();
//    void loadMap(QString fileName);
//    QString findFile(QString filePath);
private:
};

#endif // MAP_H
