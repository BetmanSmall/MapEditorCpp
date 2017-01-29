//#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QGlWidget>
#include <QOpenGLWidget>
#include <QDockWidget>
#include <gl/GLU.h>
#include <gl/GL.h>

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
//#include <QWheelEvent>
//#include <QKeyEvent>

#include "map.h"

class Camera {
public:
    QPainter p;
    int x, y;
    int cellSizeX, cellSizeY;
    float zoom;
    Camera(): x(0), y(0), cellSizeX(64), cellSizeY(32), zoom(0.5f) {}
    QString toString() {
        QString str = "Camera:[";
        str.append("x:" + QString::number(x));
        str.append(",y:" + QString::number(y));
        str.append(",cellSizeX:" + QString::number(cellSizeX));
        str.append(",cellSizeY:" + QString::number(cellSizeY));
        str.append(",zoom:" + QString::number(zoom));
        str.append("]");
        return str;
    }
};

//class MapWidgetGL : public QOpenGLWidget, public QDockWidget {
class MapWidgetGL : public QWidget {
    Q_OBJECT
public:
    MapWidgetGL(Map *map, QWidget *parent = 0);
    ~MapWidgetGL();
    Map *map;
    Camera camera;
    Tile* selectedTile;
    int selectedLayer;

    bool isDrawableTerrain = true;
    bool isDrawableGrid = true;
    bool isDrawableCreeps = true;
    bool isDrawableTowers = true;
    bool isDrawableRoutes = true;
    bool isDrawableGridNav = true;
protected:
    void paintEvent(QPaintEvent *event);
    void drawGrid();
    void drawTerrain();
    void mousePressEvent(QMouseEvent *event);
    bool whichCell(int &mouseX, int &mouseY);
//    void wheelEvent(QWheelEvent *event);
//    void keyPress(QKeyEvent *event);
//    void initializeGL();
//    void resizeGL(int w, int h);
//    void paintGL();

public slots:
    void setSelectedTile(Tile* tile);
    void setSelectedLayer(int layerIndex);
};
