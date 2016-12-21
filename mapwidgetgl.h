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
#include <QWheelEvent>

#include "map.h"

class Camera {
public:
    QPainter p;
    int x, y;
    int cellSizeX, cellSizeY;
    float scale;
    Camera(): x(0), y(0), cellSizeX(64), cellSizeY(32), scale(1) {}
};

//class MapWidgetGL : public QOpenGLWidget, public QDockWidget {
class MapWidgetGL : public QWidget {
public:
    MapWidgetGL(Map *map, QWidget *parent = 0);
    ~MapWidgetGL();
    Map *map;
    Camera camera;

protected:
    void paintEvent(QPaintEvent *event);
    void drawGrid();
    void drawFullField();
    void wheelEvent(QWheelEvent *event);
//    void initializeGL();
//    void resizeGL(int w, int h);
//    void paintGL();
};
