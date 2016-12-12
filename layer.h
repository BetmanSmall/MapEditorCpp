#ifndef LAYER_H
#define LAYER_H

#include "cell.h"

class Layer {
    int width;
    int height;
    Cell *cells;

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
        this->width = width;
        this->height = height;
        this->tileWidth = tileWidth;
        this->tileHeight = tileHeight;
        this->cells = new Cell[width*height];
    }

    /** @return layer's width in tiles */
    int getWidth () {
        return width;
    }

    /** @return layer's height in tiles */
    int getHeight () {
        return height;
    }

    /** @return tiles' width in pixels */
    float getTileWidth () {
        return tileWidth;
    }

    /** @return tiles' height in pixels */
    float getTileHeight () {
        return tileHeight;
    }

    /** @param x X coordinate
     * @param y Y coordinate
     * @return {@link Cell} at (x, y) */
    Cell *getCell (int x, int y) {
        if (x < 0 || x >= width) return NULL;
        if (y < 0 || y >= height) return NULL;
        return &cells[y*width+x];
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
