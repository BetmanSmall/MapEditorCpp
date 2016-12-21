#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QDebug>
#include <QFile>
#include <QDomDocument>
#include <QPixmap>

#include "map.h"
#include "tile.h"
#include "layer.h"

class MapLoader {
    int mapTileWidth;
    int mapTileHeight;
    int mapWidthInPixels;
    int mapHeightInPixels;
    bool flipX = false;
    bool flipY = true;
    int FLAG_FLIP_HORIZONTALLY = 0x80000000;
    int FLAG_FLIP_VERTICALLY = 0x40000000;
    int FLAG_FLIP_DIAGONALLY = 0x20000000;
    int MASK_CLEAR = 0xE0000000;

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
    void loadTileLayer(Map *map, QDomElement element);
    void loadBasicLayerInfo(Layer *layer, QDomElement element);
    int *getTileIds(QDomElement element, int width, int height);
    Cell createTileLayerCell(bool flipHorizontally, bool flipVertically, bool flipDiagonally);
};

#endif // MAPLOADER_H
