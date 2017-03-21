#include "map.h"

Map::Map() {
    properties.insert("key1", "value1");
}

Layer *Map::addNewLayer() {
    int tileWidth = properties.value("tilewidth").toInt();
    int tileHeight = properties.value("tileheight").toInt();
    Layer* layer = new Layer(width, height, tileWidth, tileHeight);
    mapLayers.add(layer);
    return layer;
}

QMap<QString, QString> *Map::getProperties() {
    return &properties;
}

TileSets *Map::getTileSets() {
    return &tileSets;
}

MapLayers *Map::getMapLayers() {
    return &mapLayers;
}

void Map::turnRight() {
    mapLayers.turnRight();
    this->width = mapLayers.get(0)->getWidth();
    this->height = mapLayers.get(0)->getHeight();
}

void Map::turnLeft() {
    mapLayers.turnLeft();
    this->width = mapLayers.get(0)->getWidth();
    this->height = mapLayers.get(0)->getHeight();
}

void Map::flipX() {
    mapLayers.flipX();
}

void Map::flipY() {
    mapLayers.flipY();
}
