#ifndef LAYER_H
#define LAYER_H

#include "cell.h"

class Layer {
    QString name;
    float opacity;
    bool visible;
//    MapObjects objects = new MapObjects();
    QMap<QString, QString> properties;
    int width;
    int height;
    QVector<Cell> cells;

    float tileWidth;
    float tileHeight;
public:
    /** Creates TiledMap layer
     *
     * @param width layer width in tiles
     * @param height layer height in tiles
     * @param tileWidth tile width in pixels
     * @param tileHeight tile height in pixels */
    Layer(int width, int height, int tileWidth, int tileHeight) {
        opacity = 1.0f;
        visible = true;
        this->width = width;
        this->height = height;
        this->tileWidth = tileWidth;
        this->tileHeight = tileHeight;
        this->cells = QVector<Cell>(width*height);
    }
    /** @return layer's name */
    QString getName() {
        return name;
    }

    /** @param name new name for the layer */
    void setName(QString name) {
        this->name = name;
    }

    /** @return layer's opacity */
    float getOpacity() {
        return opacity;
    }

    /** @param opacity new opacity for the layer */
    void setOpacity(float opacity) {
        this->opacity = opacity;
    }

//    /** @return collection of objects contained in the layer */
//    MapObjects getObjects () {
//        return objects;
//    }

    /** @return whether the layer is visible or not */
    bool isVisible() {
        return visible;
    }

    /** @param visible toggles layer's visibility */
    void setVisible(bool visible) {
        this->visible = visible;
    }

    /** @return layer's set of properties */
    QMap<QString, QString> *getProperties () {
        return &properties;
    }

    /** @return layer's width in tiles */
    int getWidth() {
        return width;
    }

    /** @return layer's height in tiles */
    int getHeight() {
        return height;
    }

    /** @return tiles' width in pixels */
    float getTileWidth() {
        return tileWidth;
    }

    /** @return tiles' height in pixels */
    float getTileHeight() {
        return tileHeight;
    }

    /** @param x X coordinate
     * @param y Y coordinate
     * @return {@link Cell} at (x, y) */
    Cell *getCell (int x, int y) {
        if (x < 0 || x >= width) return NULL;
        if (y < 0 || y >= height) return NULL;
        return &(cells[y*width+x]);
    }

    /** Sets the {@link Cell} at the given coordinates.
     *
     * @param x X coordinate
     * @param y Y coordinate
     * @param cell the {@link Cell} to set at the given coordinates. */
    void setCell (int x, int y, Cell cell) {
        if (x < 0 || x >= width) return;
        if (y < 0 || y >= height) return;
        cells[y*width+x] = cell;
    }
};

#endif // LAYER_H
