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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent*);

private:
    Ui::MainWindow *ui;
    Map *map;

private slots:
    void loadMap();
};

#endif // MAINWINDOW_H
