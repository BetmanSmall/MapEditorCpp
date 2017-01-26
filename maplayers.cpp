#include "maplayers.h"

MapLayers::MapLayers() {

}

Layer *MapLayers::get(int index) {
    return layers[index];
}

/** @param name
 * @return the first layer having the specified name, if one exists, otherwise null */
Layer *MapLayers::get(QString name) {
    for (int i = 0, n = layers.length(); i < n; i++) {
        Layer *layer = layers[i];
        if (name == layer->getName()) {
            return layer;
        }
    }
    return NULL;
}

/** Get the index of the layer having the specified name, or -1 if no such layer exists. */
int MapLayers::getIndex(QString name) {
    return getIndex(get(name));
}

/** Get the index of the layer in the collection, or -1 if no such layer exists. */
int MapLayers::getIndex(Layer *layer) {
    return layers.indexOf(layer, true);
}

/** @return number of layers in the collection */
int MapLayers::size() {
    return layers.length();
}

/** @param layer layer to be added to the set */
void MapLayers::add(Layer *layer) {
    this->layers.append(layer);
}

/** @param index removes layer at index */
void MapLayers::remove(int index) {
    layers.remove(index);
}

/** @param layer layer to be removed */
void MapLayers::remove(Layer *layer) {
    layers.removeOne(layer);
}

//<T extends Layer> Array<T> MapLayers::getByType (Class<T> type) {
//    return getByType(type, new Array<T>());
//}

//<T extends Layer> Array<T> MapLayers::getByType (Class<T> type, Array<T> fill) {
//    fill.clear();
//    for (int i = 0, n = layers.size; i < n; i++) {
//        Layer layer = layers.get(i);
//        if (ClassReflection.isInstance(type, layer)) {
//            fill.add((T)layer);
//        }
//    }
//    return fill;
//}

void MapLayers::turnRight() {
    foreach (Layer* layer, layers) {
        layer->turnRight();
    }
}

void MapLayers::turnLeft() {
    foreach (Layer* layer, layers) {
        layer->turnLeft();
    }
}

void MapLayers::flipX() {
    foreach (Layer* layer, layers) {
        layer->flipX();
    }
}

void MapLayers::flipY() {
    foreach (Layer* layer, layers) {
        layer->flipY();
    }
}
