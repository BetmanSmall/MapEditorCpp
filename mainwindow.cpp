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
    this->map = mapLoader->load("C:/QtProjects/MapEditor/maps/arena.tmx");
    if(map != NULL) {
    //    ui->tabWidget->clear();
        TileSets *tileSets = map->getTileSets();
    //    for(int ts = 0; ts < tileSets->tileSets.size(); ts++) {
    //        TileSet *tileSet = tileSets->getTileSet(ts);
    //        QScrollArea *scrollArea = new QScrollArea();
    //        scrollArea->setBackgroundRole(QPalette::Light);
    //        TileSetWidget *tilesSetWidget = new TileSetWidget(scrollArea, tileSet);
    //        scrollArea->setWidget(tilesSetWidget);
    //        ui->tabWidget->addTab(scrollArea, tilesSetWidget->getTileSetName());
    //    }
    //    ctrlPressed = true;
        MyDockWidget *tileSetsDockWidget = new MyDockWidget("Наборы тайлов - TTW Map Editor");
        for(int ts = 0; ts < tileSets->tileSets.size(); ts++) {
            TileSet *tileSet = tileSets->getTileSet(ts);
            tileSetsDockWidget->addTileSet(tileSet);
        }
        addDockWidget(Qt::RightDockWidgetArea, tileSetsDockWidget);

        mapLayers = map->getMapLayers();

        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setBackgroundRole(QPalette::Light);
        mapWidget = new MapWidgetGL(map);
        scrollArea->setWidget(mapWidget);
        QDockWidget *mapDockWidget = new QDockWidget("MAP");
        mapDockWidget->setWidget(scrollArea);

        addDockWidget(Qt::LeftDockWidgetArea, mapDockWidget);
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
    qDebug() << "MainWindow::paintEvent(); -- !!END!!";
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
//    ((TileSetWidget*)(ui->tabWidget->currentWidget()))->keyPress(event);
//    if(key == Qt::Key_Control) {
//        ((TileSetWidget*)(ui->tabWidget->currentWidget()))->setCtrl(true);
//        qDebug() << "MainWindow::keyPressEvent(); -- &ctrlPressed:" << &ctrlPressed << " ctrlPressed:" << ctrlPressed;
//    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();
    qDebug() << "MainWindow::keyReleaseEvent(); -- key:" << key;
//    ((TileSetWidget*)(ui->tabWidget->currentWidget()))->keyRelease(event);
//    if(key == Qt::Key_Control) {
//        ((TileSetWidget*)(ui->tabWidget->currentWidget()))->setCtrl(false);
//        ctrlPressed = false;
//    }
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
