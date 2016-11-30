#ifndef TILE_H
#define TILE_H

#include <QPixmap>
#include <QMap>

class Tile {
//    int id;
    QPixmap pixmap;
    QMap<QString, QString> properties;
    float offsetX;
    float offsetY;
public:
//    Tile(QPixmap pixmap);
//    void setId(int id);
//    int getId();
//    void setOffsetX(float offsetX);
//    void setOffsetY(float offsetY);

    enum BlendMode {
        NONE, ALPHA
    };

    int getId();

    void setId(int id);

    /** @return the {@link BlendMode} to use for rendering the tile */
    BlendMode getBlendMode();

    /** Sets the {@link BlendMode} to use for rendering the tile
     *
     * @param blendMode the blend mode to use for rendering the tile */
    void setBlendMode(BlendMode blendMode);

    /** @return texture region used to render the tile */
    QPixmap getPixmap();

    /** Sets the texture region used to render the tile */
    void setPixmap(QPixmap pixmap);

    /** @return the amount to offset the x position when rendering the tile */
    float getOffsetX();

    /** Set the amount to offset the x position when rendering the tile */
    void setOffsetX(float offsetX);

    /** @return the amount to offset the y position when rendering the tile */
    float getOffsetY();

    /** Set the amount to offset the y position when rendering the tile */
    void setOffsetY(float offsetY);

    /** @return tile's properties set */
    QMap<QString, QString> *getProperties();
};

#endif // TILE_H
