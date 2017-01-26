#ifndef MAPLAYERS_H
#define MAPLAYERS_H

#include <QVector>

#include "layer.h"

class MapLayers {
    QVector<Layer*> layers;
public:
    MapLayers();

    /** @param index
     * @return the Layer at the specified index */
    Layer *get(int index);

    /** @param name
     * @return the first layer having the specified name, if one exists, otherwise null */
    Layer *get(QString name);

    /** Get the index of the layer having the specified name, or -1 if no such layer exists. */
    int getIndex(QString name);

    /** Get the index of the layer in the collection, or -1 if no such layer exists. */
    int getIndex(Layer *layer);

    /** @return number of layers in the collection */
    int size();

    /** @param layer layer to be added to the set */
    void add(Layer *layer);

    /** @param index removes layer at index */
    void remove(int index);

    /** @param layer layer to be removed */
    void remove(Layer *layer);

//    /** @param type
//     * @return array with all the layers matching type */
//    <T extends Layer> Array<T> getByType (Class<T> type);

//    /** @param type
//     * @param fill array to be filled with the matching layers
//     * @return array with all the layers matching type */
//    <T extends Layer> Array<T> getByType (Class<T> type, Array<T> fill);

    void turnRight();
    void turnLeft();
    void flipX();
    void flipY();
};

#endif // MAPLAYERS_H
