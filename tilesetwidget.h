#ifndef TILESSETWIDGET_H
#define TILESSETWIDGET_H

#include <QWidget>
#include <QTableWidget>
//#include <QScrollArea>
#include <QPaintEvent>
#include <QPainter>

#include "tileset.h"
#include "statictile.h"
#include "animatedtile.h"

class TileSetWidget : public QWidget {
    Q_OBJECT
    TileSet *tileSet;
    int tileWidht;
    int tileHeight;
    int columns;
    float scale;
public:
//    explicit TileSetWidget(QWidget *parent = 0);
    TileSetWidget(TileSet *tileSet);
    QString getTileSetName();

    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
signals:

public slots:
};

#endif // TILESSETWIDGET_H
