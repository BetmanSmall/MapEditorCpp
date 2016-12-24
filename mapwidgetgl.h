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
    Camera(): x(0), y(0), cellSizeX(64), cellSizeY(32), zoom(0.49f) {}
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
public:
    MapWidgetGL(Map *map, QWidget *parent = 0);
    ~MapWidgetGL();
    Map *map;
    Camera camera;

    bool isDrawableTerrain = true;
    bool isDrawableGrid = true;
    bool isDrawableCreeps = true;
    bool isDrawableTowers = true;
    bool isDrawableRoutes = true;
    bool isDrawableGridNav = true;
protected:
    void paintEvent(QPaintEvent *event);
    void drawGrid();
    void drawFullField();
    void mousePressEvent(QMouseEvent *event);
//    void wheelEvent(QWheelEvent *event);
//    void keyPress(QKeyEvent *event);
//    void initializeGL();
//    void resizeGL(int w, int h);
//    void paintGL();
};
