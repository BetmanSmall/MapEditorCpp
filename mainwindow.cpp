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
    for(int ts = 0; ts < tileSets->tileSets.size(); ts++) {
        TileSet *tileSet = tileSets->getTileSet(ts);
        TileSetWidget *tilesSetWidget = new TileSetWidget(tileSet);
//        QScrollArea *scrollArea = new QScrollArea(tilesSetWidget);
//        QScrollArea *scrollArea = new QScrollArea();
//        scrollArea->setWidget(tilesSetWidget);
        ui->tabWidget->addTab(tilesSetWidget, tilesSetWidget->getTileSetName());
    }

////    TileSet *tileSet = map->getTileSets()->getTileSet(0);
//    ui->tabWidget->clear();
//    QList<Tile*> tiles = map->getTileSets()->getTileSet()
    for(int ts = 0; ts < map->getTileSets()->getTileSets().length(); ts++) {
        TileSet *tileSet = map->getTileSets()->getTileSet(ts);
        int columns = tileSet->getProperties()->value("columns").toInt();
        int rows = tileSet->getTiles().length()/columns;

        qDebug() << "columns" << columns << "rows" << rows;
        QTableWidget *tableWidget = new QTableWidget(rows, columns, ui->tabWidget);
        for(int x = 0; x < columns; x++) {
            for(int y = 0; y < rows; y++) {
                int index = columns*y + x;
                Tile* tile = tileSet->getTile(tileSet->getProperties()->value("firstgid").toInt() + index+1);
                if(tile != NULL) {
                    QPixmap pixmap = tile->getPixmap();
//                    QTableWidgetItem *item = new QTableWidgetItem(pixmap, x+"."+y);
                    QTableWidgetItem *item = new QTableWidgetItem(pixmap, QString::number(x) + "-" + QString::number(y));
                    tableWidget->setItem(x, y, item);
                    qDebug() << "MainWindow::MainWindow(); -- x:" << x << " y:" << y << " tileSet:" << tileSet->getName() << " s:" << map->getTileSets()->getTileSets().length();
                }
            }
        }
        tableWidget->adjustSize();
        ui->tabWidget->addTab(tableWidget, tileSet->getName());
    }
//    QTableWidgetItem *item = new QTableWidgetItem();
//    item->setText("[peq]");
//    ui->tableWidget->setItem(0, 0, item);
//    QTableWidgetItem *item1 = new QTableWidgetItem("qwe");
//    ui->tableWidget->setItem(1, 0, item1)
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
