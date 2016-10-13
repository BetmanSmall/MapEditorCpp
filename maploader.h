#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QDebug>
#include <QFile>
#include <QDomDocument>
#include <QPixmap>

#include "map.h"

class MapLoader {
    int mapTileWidth;
    int mapTileHeight;
    int mapWidthInPixels;
    int mapHeightInPixels;
    bool flipY = true;

public:
    MapLoader();

    Map *load(QString mapPath);
private:
    QDomDocument *loadDomDocument(QString xmlFile);
    QVector<QString> loadTilesets(QDomElement mapElement, QString mapPath);
    QVector<QString> loadImages(QDomElement mapElement, QString mapPath);
    Map *loadMap(QDomElement mapElement, QString mapPath, QMap<QString, QPixmap> textures);
    void loadProperties(QMap<QString, QString> *properties, QDomElement propertiesElement);
    void loadTileSet(Map *map, QDomElement tileSetElement, QString mapPath, QMap<QString, QPixmap> textures);
    QString findFile(QString mapPath, QString filePath);
};

#endif // MAPLOADER_H
