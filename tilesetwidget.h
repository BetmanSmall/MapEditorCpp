#ifndef TILESSETWIDGET_H
#define TILESSETWIDGET_H

#include <QWidget>
#include <QTableWidget>
//#include <QScrollArea>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>

#include "tileset.h"
#include "statictile.h"
#include "animatedtile.h"
#include "mydockwidget.h"

class TileSetWidget : public QWidget {
    Q_OBJECT
    QWidget *parent;
    TileSet *tileSet;
    int tileWidht;
    int tileHeight;
    int rows;
    int columns;
    float scale;
    bool ctrlPressed;
    QRect *selectedTile;
public:
//    explicit TileSetWidget(QWidget *parent = 0);
    TileSetWidget(QWidget *parent, TileSet *tileSet);
    QString getTileSetName();

    void setCtrl(bool pressed);

    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
//    void keyPress(QKeyEvent *event);
//    void keyRelease(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void tileSelected(Tile* tile);
};

#endif // TILESSETWIDGET_H
