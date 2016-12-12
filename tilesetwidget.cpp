#include "tilesetwidget.h"

//TileSetWidget::TileSetWidget(QWidget *parent) : QWidget(parent) {
//    this
//}

TileSetWidget::TileSetWidget(QWidget *parent, TileSet *tileSet) : QWidget(parent) {
//    this->parentWidget()->height();
    this->tileSet = tileSet;
    this->tileWidht = tileSet->getProperties()->value("tilewidth").toInt();
    this->tileHeight = tileSet->getProperties()->value("tileheight").toInt();
    this->columns = tileSet->getProperties()->value("columns").toInt();
    this->rows = tileSet->getTiles().length()/columns;
    this->scale = 1;
    this->setGeometry(QRect(0, 0, columns*tileWidht, rows*tileHeight));
    this->ctrlPressed = false;
    this->selectedTile = new QRect();
}

QString TileSetWidget::getTileSetName() {
    return tileSet->getName();
}

void TileSetWidget::setCtrl(bool pressed) {
//    qDebug() << "TileSetWidget::setCtrl(" << pressed << "); -- &pressed:" << &pressed << " pressed:" << pressed;
//    qDebug() << "TileSetWidget::setCtrl(" << pressed << "); -- &ctrlPressed:" << &ctrlPressed << " ctrlPressed:" << ctrlPressed;
    qDebug() << "TileSetWidget:" << this << ":setCtrl(); -- this->ctrlPressed:" << this->ctrlPressed;
    this->ctrlPressed = pressed;
}

void TileSetWidget::paintEvent(QPaintEvent *event) {
//    qDebug() << "TilesSetWidget::paintEvent(); -- scale:" << scale << " width():" << width() << " height():" << height();
//    qDebug() << "TilesSetWidget::paintEvent(" << event << "); -- &ctrlPressed:" << &ctrlPressed << " ctrlPressed:" << ctrlPressed;
    qDebug() << "TileSetWidget:" << this << ":paintEvent(); -- this->ctrlPressed:" << this->ctrlPressed;
    QPainter p;
    p.begin(this);
//    p.scale(scale, scale);
    QList<Tile*> tiles = tileSet->getTiles();
    for(int y = 0; y < tiles.length()/columns; y++) {
        for(int x = 0; x < columns; x++) {
            int index = columns*y + x;
            Tile *tile = tiles[index];
            StaticTile *staticTile = static_cast<StaticTile*>(tile);
            if(staticTile != NULL) {
                QPixmap pixmap = staticTile->getPixmap();
                p.drawPixmap((int)(x*(tileWidht*scale)), (int)(y*(tileHeight*scale)), (int)(tileWidht*scale), (int)(tileHeight*scale), pixmap);
//                qDebug() << "MainWindow::paintEvent(); -- p.drawPixmap(" << x*tileWidht << "," << y*tileHeight << "," << tileWidht << "," << tileHeight << "," << pixmap << ");";
            } else {
                AnimatedTile *animatedTile = static_cast<AnimatedTile*>(tile);
                if(animatedTile != NULL) {
                    qDebug() << "MainWindow::paintEvent(); -- AnimatedTile:" << animatedTile->getId();
                }
            }
        }
    }
    qDebug() << "TileSetWidget:" << this << ":paintEvent(); -- this->selectedTile:" << this->selectedTile;
    if(!selectedTile->isNull()) {
        p.fillRect(*selectedTile, QBrush(QColor(128, 128, 255, 128)));
    }
    p.end();
}

void TileSetWidget::wheelEvent(QWheelEvent *event) {
//    scale+=(event->delta()/120);
//    qDebug() << "TileSetWidget::wheelEvent(1); -- event.delta():" << event->delta() << " scale:" << scale;
//    qDebug() << "TileSetWidget::wheelEvent(2); -- &ctrlPressed:" << &this->ctrlPressed << " ctrlPressed:" << this->ctrlPressed;
    qDebug() << "TileSetWidget:" << this << ":wheelEvent(); -- this->ctrlPressed:" << this->ctrlPressed;

    if(this->ctrlPressed) {
        qDebug() << "TileSetWidget::wheelEvent(2); -- event.delta():" << event->delta() << " scale:" << scale;
        if(event->delta() > 0) {
            if(scale < 5) {
                scale += 0.1;
            }
        } else {
            if(parentWidget()->height() < (rows*tileHeight)*scale) {
                qDebug() << "qweqwe";
                scale -= 0.1;
            } else {
                qDebug() << "NOT do";
            }
        }
        setGeometry(QRect(0, 0, columns*(tileWidht*scale), rows*(tileHeight*scale)));
        repaint();
    } else {
        ((MyDockWidget*)parentWidget())->wheelEvent(event);
    }
}

//void TileSetWidget::keyPress(QKeyEvent *event) {
//    int key = event->key();
//    qDebug() << "TileSetWidget::keyPress(" << event << "); - key:" << key;
//    if(key == Qt::Key_Control) {
//        this->ctrlPressed = true;
//        qDebug() << "TileSetWidget:" << this << ":keyPress(); -- this->ctrlPressed:" << this->ctrlPressed;
////        qDebug() << "TileSetWidget::keyPress(); -- &ctrlPressed:" << &this->ctrlPressed << " ctrlPressed:" << this->ctrlPressed;
//    }
//}

//void TileSetWidget::keyRelease(QKeyEvent *event) {
//    int key = event->key();
//    qDebug() << "TileSetWidget::keyRelease(" << event << "); - key:" << key;
//    if(key == Qt::Key_Control) {
//        this->ctrlPressed = false;
//        qDebug() << "TileSetWidget:" << this << ":keyRelease(); -- this->ctrlPressed:" << this->ctrlPressed;
////        qDebug() << "TileSetWidget::keyRelease(); -- &ctrlPressed:" << &this->ctrlPressed << " ctrlPressed:" << this->ctrlPressed;
//    }
//}

void TileSetWidget::mousePressEvent(QMouseEvent *event) {
    int mouseX = event->x();
    int mouseY = event->y();
    int tileX = mouseX/(tileWidht*scale);
    int tileY = mouseY/(tileHeight*scale);
    this->selectedTile->setRect(tileX*(tileWidht*scale), tileY*(tileHeight*scale), tileWidht*scale, tileHeight*scale);
    qDebug() << "TileSetWidget::mousePressEvent(" << event << "); -- mouseX:" << mouseX << " mouseY:" << mouseY << " tileX:" << tileX << " tileY:" << tileY;
    repaint();
}
