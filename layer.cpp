#include "layer.h"

Layer::Layer(int width, int height, int tileWidth, int tileHeight) {
    opacity = 1.0f;
    visible = true;
    this->width = width;
    this->height = height;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->cells = QVector<Cell>(width*height);
}

QString Layer::getName() {
    return name;
}

void Layer::setName(QString name) {
    this->name = name;
}

float Layer::getOpacity() {
    return opacity;
}

void Layer::setOpacity(float opacity) {
    this->opacity = opacity;
}

//MapObjects Layer::getObjects () {
//    return objects;
//}

bool Layer::isVisible() {
    return visible;
}

void Layer::setVisible(bool visible) {
    this->visible = visible;
}

QMap<QString, QString> *Layer::getProperties () {
    return &properties;
}

int Layer::getWidth() {
    return width;
}

int Layer::getHeight() {
    return height;
}

float Layer::getTileWidth() {
    return tileWidth;
}

float Layer::getTileHeight() {
    return tileHeight;
}

Cell *Layer::getCell(int x, int y) {
    if (x < 0 || x >= width) return NULL;
    if (y < 0 || y >= height) return NULL;
    return &(cells[y*width+x]);
}

void Layer::setCell (int x, int y, Cell cell) {
    if (x < 0 || x >= width) return;
    if (y < 0 || y >= height) return;
    cells[y*width+x] = cell;
}

bool Layer::turnRight() {
    if(!cells.isEmpty() && width == height) {
        QVector<Cell> newCells(width*height);
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                newCells[width*(x)+(width-y-1)] = cells[width*y+x];
            }
        }
        cells = newCells;
        return true;
    } else {
        return false;
    }
}

bool Layer::turnLeft() {
    if(!cells.isEmpty() && width == height) {
        QVector<Cell> newCells(width*height);
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                newCells[width*(height-x-1)+(y)] = cells[width*y+x];
            }
        }
        cells = newCells;
        return true;
    } else {
        return false;
    }
}

bool Layer::flipX() {
    if(!cells.isEmpty() && width == height) {
        QVector<Cell> newCells(width*height);
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                newCells[width*(width-y-1)+(x)] = cells[width*y+x];
            }
        }
        cells = newCells;
        return true;
    } else {
        return false;
    }
}

bool Layer::flipY() {
    if(!cells.isEmpty() && width == height) {
        QVector<Cell> newCells(width*height);
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                newCells[width*(y)+(height-x-1)] = cells[width*y+x];
            }
        }
        cells = newCells;
        return true;
    } else {
        return false;
    }
}
