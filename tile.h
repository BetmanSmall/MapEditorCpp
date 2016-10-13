#ifndef TILE_H
#define TILE_H

#include <QPixmap>
#include <QMap>

class Tile {
    int id;
    QPixmap pixmap;
    QMap<QString, QString> properties;
    float offsetX;
    float offsetY;
public:
    Tile(QPixmap pixmap);
    void setId(int id);
    int getId();
    void setOffsetX(float offsetX);
    void setOffsetY(float offsetY);
};

#endif // TILE_H
