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
    MyDockWidget(QString title);
    void addTileSet(TileSet *tileSet);

    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // MYDOCKWIDGET_H
