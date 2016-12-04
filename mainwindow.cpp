#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionLoadMap, SIGNAL(triggered(bool)), this, SLOT(loadMap()));

    MapLoader *mapLoader = new MapLoader();
    this->map = mapLoader->load("C:/QtProjects/MapEditor/maps/arena2.tmx");

    TileSets *tileSets = map->getTileSets();
    ui->tabWidget->clear();
    for(int ts = 0; ts < tileSets->tileSets.size(); ts++) {
        TileSet *tileSet = tileSets->getTileSet(ts);
        TileSetWidget *tilesSetWidget = new TileSetWidget(tileSet);
//        QScrollArea *scrollArea = new QScrollArea(tilesSetWidget);
        ui->tabWidget->addTab(tilesSetWidget, tilesSetWidget->getTileSetName());
    }

//    int columns = 4, rows = 4;
//    ui->tableWidget->setColumnCount(columns);
//    ui->tableWidget->setRowCount(rows);
//    for(int y = 0; y < rows; y++) {
//        for(int x = 0; x < columns; x++) {
//            QTableWidgetItem *item = new QTableWidgetItem(QString::number(x) + "-" + QString::number(y));
//            ui->tableWidget->setItem(x, y, item);
//        }
//    }
//    QTableWidgetItem *item = new QTableWidgetItem();
//    item->setText("[peq]");
//    ui->tableWidget->setItem(0, 0, item);
//    QTableWidgetItem *item1 = new QTableWidgetItem("qwe");
//    ui->tableWidget->setItem(1, 0, item1);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
//    qDebug() << "MainWindow::paintEvent(" << event << ");";
//    QPainter p;
//    p.begin(this);
//    qDebug() << "MainWindow::paintEvent(); -- Test8";

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
