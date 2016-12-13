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
    Layer *get (int index) {
        return layers[index];
    }

    /** @param name
     * @return the first layer having the specified name, if one exists, otherwise null */
    Layer *get(QString name) {
        for (int i = 0, n = layers.length(); i < n; i++) {
            Layer *layer = layers[i];
            if (name == layer->getName()) {
                return layer;
            }
        }
        return NULL;
    }

    /** Get the index of the layer having the specified name, or -1 if no such layer exists. */
    int getIndex (QString name) {
        return getIndex(get(name));
    }

    /** Get the index of the layer in the collection, or -1 if no such layer exists. */
    int getIndex (Layer *layer) {
        return layers.indexOf(layer, true);
    }

    /** @return number of layers in the collection */
    int getCount () {
        return layers.length();
    }

    /** @param layer layer to be added to the set */
    void add (Layer *layer) {
        this->layers.append(layer);
    }

    /** @param index removes layer at index */
    void remove (int index) {
        layers.remove(index);
    }

    /** @param layer layer to be removed */
    void remove(Layer *layer) {
        layers.removeOne(layer);
    }

//    /** @param type
//     * @return array with all the layers matching type */
//    <T extends Layer> Array<T> getByType (Class<T> type) {
//        return getByType(type, new Array<T>());
//    }

//    /** @param type
//     * @param fill array to be filled with the matching layers
//     * @return array with all the layers matching type */
//    <T extends Layer> Array<T> getByType (Class<T> type, Array<T> fill) {
//        fill.clear();
//        for (int i = 0, n = layers.size; i < n; i++) {
//            Layer layer = layers.get(i);
//            if (ClassReflection.isInstance(type, layer)) {
//                fill.add((T)layer);
//            }
//        }
//        return fill;
//    }
};

#endif // MAPLAYERS_H
