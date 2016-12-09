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
    this->map = mapLoader->load("C:/QtProjects/MapEditor/maps/arena2.tmx");

    ui->tabWidget->clear();
    TileSets *tileSets = map->getTileSets();
    for(int ts = 0; ts < tileSets->tileSets.size(); ts++) {
        TileSet *tileSet = tileSets->getTileSet(ts);
        TileSetWidget *tilesSetWidget = new TileSetWidget(tileSet);
        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setBackgroundRole(QPalette::Light);
        scrollArea->setWidget(tilesSetWidget);
        ui->tabWidget->addTab(scrollArea, tilesSetWidget->getTileSetName());
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
//    qDebug() << "MainWindow::paintEvent(" << event << ");";
//    QPainter p;
//    p.begin(this);
//    qDebug() << "MainWindow::pa intEvent(); -- Test8";

//    p.drawLine(0, 0, width(), height());
//    p.end();
//    qDebug() << "MainWindow::paintEvent(); -- !!END!!";
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
