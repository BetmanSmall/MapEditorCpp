#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QFileDialog>
#include <QPaintEvent>
#include <QPainter>
#include <QScrollArea>

//#include "map.h"
#include "maploader.h"
#include "tile.h"
#include "statictile.h"
#include "animatedtile.h"
#include "tilesets.h"
#include "tileset.h"
#include "tilesetwidget.h"
#include "mydockwidget.h"
#include "mapwidgetgl.h"
//#include "layer.h"
#include "dockwidgetlayers.h"

namespace Ui {
class MainWindow;
}

//class Camera {
//public:
//    QPainter p;
//    int x, y;
//    int cellSizeX, cellSizeY;
//    Camera(): x(0), y(0), cellSizeX(64), cellSizeY(32) {}
//};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool ctrlPressed;

    void paintEvent(QPaintEvent *event);
//    void drawGrid();
//    void drawFullField();
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;
    Camera camera;
    Map *map;
    MapLayers *mapLayers;
    MapWidgetGL *mapWidget;

private slots:
    void loadMap();
};

#endif // MAINWINDOW_H
