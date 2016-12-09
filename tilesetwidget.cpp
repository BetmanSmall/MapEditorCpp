#include "tilesetwidget.h"

//TileSetWidget::TileSetWidget(QWidget *parent) : QWidget(parent) {
//    this
//}

TileSetWidget::TileSetWidget(TileSet *tileSet) {
    this->tileSet = tileSet;
    int tileWidht = tileSet->getProperties()->value("tilewidth").toInt();
    int tileHeight = tileSet->getProperties()->value("tileheight").toInt();
    int columns = tileSet->getProperties()->value("columns").toInt();
    setGeometry(QRect(0, 0, columns*tileWidht, (tileSet->getTiles().length()/columns)*tileHeight));
//    scale = 1000;
}

QString TileSetWidget::getTileSetName() {
    return tileSet->getName();
}

void TileSetWidget::paintEvent(QPaintEvent *event) {
    qDebug() << "TilesSetWidget::paintEvent(); -- scale:";
    QPainter p;
    p.begin(this);
//    p.scale(scale, scale);
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

void TileSetWidget::wheelEvent(QWheelEvent *event) {
    qDebug() << "TileSetWidget::wheelEvent(); -- event.delta():" << event->delta();
//    scale+=(event->delta()/120);
}
