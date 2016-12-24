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
    Layer(int width, int height, int tileWidth, int tileHeight);

    /** @return layer's name */
    QString getName();

    /** @param name new name for the layer */
    void setName(QString name);

    /** @return layer's opacity */
    float getOpacity();

    /** @param opacity new opacity for the layer */
    void setOpacity(float opacity);

//    /** @return collection of objects contained in the layer */
//    MapObjects getObjects();

    /** @return whether the layer is visible or not */
    bool isVisible();

    /** @param visible toggles layer's visibility */
    void setVisible(bool visible);

    /** @return layer's set of properties */
    QMap<QString, QString> *getProperties();

    /** @return layer's width in tiles */
    int getWidth();

    /** @return layer's height in tiles */
    int getHeight();

    /** @return tiles' width in pixels */
    float getTileWidth();

    /** @return tiles' height in pixels */
    float getTileHeight();

    /** @param x X coordinate
     * @param y Y coordinate
     * @return {@link Cell} at (x, y) */
    Cell *getCell(int x, int y);

    /** Sets the {@link Cell} at the given coordinates.
     *
     * @param x X coordinate
     * @param y Y coordinate
     * @param cell the {@link Cell} to set at the given coordinates. */
    void setCell(int x, int y, Cell cell);

    bool turnRight();
    bool turnLeft();
    bool flipX();
    bool flipY();
};

#endif // LAYER_H
