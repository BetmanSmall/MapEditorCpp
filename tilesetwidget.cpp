#include "tilesetwidget.h"

//TileSetWidget::TileSetWidget(QWidget *parent) : QWidget(parent) {
//    this
//}

TileSetWidget::TileSetWidget(TileSet *tileSet) {
    this->tileSet = tileSet;
//    int x = 0, y = 0;
//    int tileWidht = tileSet->getProperties()->value("tilewidth").toInt();
//    int tileHeight = tileSet->getProperties()->value("tileheight").toInt();
//    int columns = tileSet->getProperties()->value("columns").toInt();
//    QList<Tile*> tiles = tileSet->getTiles();
//    this->setColumnCount(columns);
//    this->setRowCount(tiles.length()/columns);
////    this->ro
//    for(int y = 0; y < tiles.length()/columns; y++) {
//        for(int x = 0; x < columns; x++) {
//            int index = columns*y + x;
//            Tile *tile = tiles[index];
//            StaticTile *staticTile = static_cast<StaticTile*>(tile);
//            if(staticTile != NULL) {
//                QPixmap pixmap = staticTile->getPixmap();
//                QTableWidgetItem *itemPixmap = new QTableWidgetItem(QIcon(pixmap), "x + + y");
//                QTableWidgetItem *item = new QTableWidgetItem();
//                item->setText("[eq]");
//                this->setItem(x, y, item);
////                qDebug() << "MainWindow::paintEvent(); -- p.drawPixmap(" << x*tileWidht << "," << y*tileHeight << "," << tileWidht << "," << tileHeight << "," << pixmap << ");";
////                qDebug() << "TileSetWidget::TileSetWidget(); -- setItem(" << x << "," << y << "," << itemPixmap << "," << pixmap << ");";
////                p.drawPixmap(x*tileWidht, y*tileHeight, tileWidht, tileHeight, pixmap);
//            } else {
//                AnimatedTile *animatedTile = static_cast<AnimatedTile*>(tile);
//                if(animatedTile != NULL) {
//                    qDebug() << "MainWindow::paintEvent(); -- AnimatedTile:" << animatedTile->getId();
//                }
//            }
//        }
//    }
}

void TileSetWidget::paintEvent(QPaintEvent *event) {
    qDebug() << "TilesSetWidget::paintEvent();";
    QPainter p;
    p.begin(this);
    int x = 0, y = 0;
    int tileWidht = tileSet->getProperties()->value("tilewidth").toInt();
    int tileHeight = tileSet->getProperties()->value("tileheight").toInt();
    int columns = tileSet->getProperties()->value("columns").toInt();
    QList<Tile*> tiles = tileSet->getTiles();
    for(int y = 0; y < tiles.length()/columns; y++) {
        for(int x = 0; x < columns; x++) {
            int index = columns*y + x;
            Tile *tile = tiles[index];
            StaticTile *staticTile = static_cast<StaticTile*>(tile);
            if(staticTile != NULL) {
                QPixmap pixmap = staticTile->getPixmap();
                p.drawPixmap(x*tileWidht, y*tileHeight, tileWidht, tileHeight, pixmap);
//                qDebug() << "MainWindow::paintEvent(); -- p.drawPixmap(" << x*tileWidht << "," << y*tileHeight << "," << tileWidht << "," << tileHeight << "," << pixmap << ");";
            } else {
                AnimatedTile *animatedTile = static_cast<AnimatedTile*>(tile);
                if(animatedTile != NULL) {
                    qDebug() << "MainWindow::paintEvent(); -- AnimatedTile:" << animatedTile->getId();
                }
            }
        }
    }
    p.end();
}

QString TileSetWidget::getTileSetName() {
    return tileSet->getName();
}
