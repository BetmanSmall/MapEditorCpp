#ifndef TILESSETWIDGET_H
#define TILESSETWIDGET_H

#include <QWidget>
//#include <QTableWidget>
//#include <QScrollArea>
#include <QPaintEvent>
#include <QPainter>

#include "tileset.h"
#include "statictile.h"
#include "animatedtile.h"

class TileSetWidget : public QWidget
{
    Q_OBJECT
    TileSet *tileSet;
public:
//    explicit TileSetWidget(QWidget *parent = 0);
    TileSetWidget(TileSet *tileSet);
    void paintEvent(QPaintEvent *event);

    QString getTileSetName();
signals:

public slots:
};

#endif // TILESSETWIDGET_H
