#ifndef TILE_H
#define TILE_H

#include <QPixmap>
#include <QMap>

class Tile {
protected:
    int id;
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

    virtual int getId() = 0;

    virtual void setId(int id) = 0;

    /** @return the {@link BlendMode} to use for rendering the tile */
    virtual BlendMode getBlendMode() = 0;

    /** Sets the {@link BlendMode} to use for rendering the tile
     *
     * @param blendMode the blend mode to use for rendering the tile */
    virtual void setBlendMode(BlendMode blendMode) = 0;

    /** @return texture region used to render the tile */
    virtual QPixmap getPixmap() = 0;

    /** Sets the texture region used to render the tile */
    virtual void setPixmap(QPixmap pixmap) = 0;

    /** @return the amount to offset the x position when rendering the tile */
    virtual float getOffsetX() = 0;

    /** Set the amount to offset the x position when rendering the tile */
    virtual void setOffsetX(float offsetX) = 0;

    /** @return the amount to offset the y position when rendering the tile */
    virtual float getOffsetY() = 0;

    /** Set the amount to offset the y position when rendering the tile */
    virtual void setOffsetY(float offsetY) = 0;

    /** @return tile's properties set */
    virtual QMap<QString, QString> *getProperties() = 0;
};

#endif // TILE_H
