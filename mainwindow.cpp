#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionLoadMap, SIGNAL(triggered(bool)), this, SLOT(loadMap()));

    MapLoader *mapLoader = new MapLoader();
    this->map = mapLoader->load("C:/QtProjects/MapEditor/maps/arena4.tmx");
    if(map != NULL) {
        TileSets *tileSets = map->getTileSets();
        DockWidgetTileSets *dockWidgetTileSets = new DockWidgetTileSets(tileSets, this);
        addDockWidget(Qt::RightDockWidgetArea, dockWidgetTileSets);

        mapLayers = map->getMapLayers();
        DockWidgetLayers* dockWidgetLayers = new DockWidgetLayers(mapLayers, this);
        addDockWidget(Qt::RightDockWidgetArea, dockWidgetLayers);

        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setBackgroundRole(QPalette::Light);
        mapWidget = new MapWidgetGL(map);
        scrollArea->setWidget(mapWidget);
        QDockWidget *mapDockWidget = new QDockWidget("MAP");
        mapDockWidget->setWidget(scrollArea);

        addDockWidget(Qt::LeftDockWidgetArea, mapDockWidget);

        connect(dockWidgetLayers, SIGNAL(repaintMap()), mapWidget, SLOT(repaint()));
        connect(dockWidgetLayers, SIGNAL(layerSelected(int)), mapWidget, SLOT(setSelectedLayer(int)));
        connect(dockWidgetTileSets, SIGNAL(tileSelected(Tile*)), mapWidget, SLOT(setSelectedTile(Tile*)));
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
//    qDebug() << "MainWindow::paintEvent(" << event << ");";
//    camera.p.begin(this);
//    drawFullField();
//    drawGrid();
//    camera.p.drawLine(0, 0, width(), height());
//    camera.p.drawLine(width(), 0, 0, height());
//    camera.p.drawEllipse(0, 0, 200, 200);
//    camera.p.end();
//    qDebug() << "MainWindow::paintEvent(); -- !!END!!";
}

void MainWindow::wheelEvent(QWheelEvent *event) {
//    qDebug() << "MainWindow::wheelEvent(" << event << "); -- ctrlPressed:" << ctrlPressed;
//    qDebug() << "MainWindow::wheelEvent(" << event << "); -- &ctrlPressed:" << &ctrlPressed << " ctrlPressed:" << ctrlPressed;
//    if(ctrlPressed) {
//        ((TileSetWidget*)(ui->tabWidget->currentWidget()))->wheelEvent(event);
//    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    qDebug() << "MainWindow::keyPressEvent(); -- key:" << key;
    if(mapWidget != NULL) {
        if(key == 43) { // Qt::Key_Plus
            mapWidget->camera.zoom += 0.01;
            mapWidget->repaint();
        } else if(key == 45) { // Qt::Key_Minus
            mapWidget->camera.zoom -= 0.01;
            mapWidget->repaint();
        } else if(key == 93) {
            mapWidget->map->turnRight();
            mapWidget->repaint();
        } else if(key == 91) {
            mapWidget->map->turnLeft();
            mapWidget->repaint();
        } else if(key == 39) {
            mapWidget->map->flipX();
            mapWidget->repaint();
        } else if(key == 59) {
            mapWidget->map->flipY();
            mapWidget->repaint();
        } else if(key == 49) {
            mapWidget->isDrawableGrid = !mapWidget->isDrawableGrid;
            mapWidget->repaint();
        } else if(key == 50) {
            mapWidget->isDrawableTerrain = !mapWidget->isDrawableTerrain;
            mapWidget->repaint();
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();
    qDebug() << "MainWindow::keyReleaseEvent(); -- key:" << key;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    int x = event->x();
    int y = event->y();
    qDebug() << "MainWindow::mousePressEvent(" << event << "); -- x:" << x << " y:" << y;
}

void MainWindow::loadMap() {
    qDebug() << "MainWindow::loadMap()";
    QString mapName = QFileDialog::getOpenFileName(this, tr("Open File"), "../../MapEditor/maps", tr("Maps (*.tmx)"));

    if(this->map != NULL) {
        delete map;
    }
    MapLoader *mapLoader = new MapLoader();
    this->map = mapLoader->load(mapName);
}
