#ifndef MYDOCKWIDGET_H
#define MYDOCKWIDGET_H

#include <QDockWidget>
#include <QTabWidget>
#include <QScrollArea>
#include <QVBoxLayout>

#include "tileset.h"
#include "tilesetwidget.h"

class MyDockWidget : public QDockWidget {
    QVBoxLayout *layout;
    QTabWidget *tabWidget;
public:
    MyDockWidget(QString title, QWidget* parent);
    void addTileSet(TileSet *tileSet);

    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void tileSelected1(Tile* tile);

public slots:
    void tileSelectedSlot(Tile* tile);
};

#endif // MYDOCKWIDGET_H
