#include "mapwidgetgl.h"

MapWidgetGL::MapWidgetGL(Map *map, QWidget *parent)
    : QWidget(parent) {
    qDebug() << "MapWidget::MapWidget();";
    this->map = map;
    this->setGeometry(QRect(0, 0, map->width*camera.cellSizeX, map->height*camera.cellSizeY));
}

MapWidgetGL::~MapWidgetGL() {
    qDebug() << "MapWidget::~MapWidget();";
}

void MapWidgetGL::paintEvent(QPaintEvent *event) {
//    qDebug() << "MapWidgetGL::paintEvent(); -- map:" << map;
//    this->setGeometry(QRect(0, 0, map->width*camera.cellSizeX*camera.zoom, map->height*camera.cellSizeY*camera.zoom));
    camera.p.begin(this);
    if(isDrawableTerrain)
        drawTerrain();
    if(isDrawableGrid)
        drawGrid();
//    camera.p.drawLine(0, 0, width(), height());
//    camera.p.drawLine(width(), 0, 0, height());
//    camera.p.drawEllipse(40, 0, 200, 200);
    camera.p.end();
//    qDebug() << "MapWidgetGL::paintEvent(); -- !!END!!";
}

void MapWidgetGL::drawTerrain() {
    int mainCoorMapX = camera.x;
    int mainCoorMapY = camera.y;
    int sizeCellX = camera.cellSizeX*camera.zoom;
    int sizeCellY = camera.cellSizeY*camera.zoom;
    int halfSizeCellX = sizeCellX/2;
    int halfSizeCellY = sizeCellY/2;
    int fieldX = map->width;
    int fieldY = map->height;

    MapLayers *mapLayer = map->getMapLayers();
    for (int l = 0; l < mapLayer->getCount(); l++) {
        Layer *layer = mapLayer->get(l);

        int isometricSpaceX = (sizeCellX/2) * fieldY;
        int isometricSpaceY = 0;
        for(int y = 0; y < fieldY; y++) {
            for(int x = 0; x < fieldX; x++) {
                Cell *cell = layer->getCell(x, y);
                if(cell != NULL) {
                    Tile *tile = cell->getTile();
                    if(tile != NULL) {
                        QPixmap pix = QPixmap(tile->getPixmap());
                        if(!pix.isNull()) {
                            int pixWidth = pix.width();
                            int pixHeight = pix.height();
                            int drawX = mainCoorMapX + isometricSpaceX - (sizeCellX/2) + x*halfSizeCellX;
                            int drawY = mainCoorMapY + isometricSpaceY - (sizeCellY) + x*halfSizeCellY;
                            camera.p.drawPixmap(drawX, drawY, sizeCellX, sizeCellY*2, pix);
                        }
                    } else {
//                        qDebug() << "MapWidgetGL::drawTerrain(); -- Not Tile in Cell(" << x << "," << y << ")";
                    }
                } else {
//                    qDebug() << "MapWidgetGL::drawTerrain(); -- Bad Cell(" << x << "," << y << ")";
                }
            }
            isometricSpaceX -= halfSizeCellX;
            isometricSpaceY += halfSizeCellY;
        }
    }
}

void MapWidgetGL::drawGrid() {
    qDebug() << "MapWidgetGL::drawGrid(); -- " << camera.toString();
    int mainCoorMapX = camera.x;
    int mainCoorMapY = camera.y;
//    int mainCoorMapY = camera.y + height()/2;
    int sizeCellX = camera.cellSizeX*camera.zoom;
    int sizeCellY = camera.cellSizeY*camera.zoom;
    int halfSizeCellX = sizeCellX/2;
    int halfSizeCellY = sizeCellY/2;
    camera.p.setPen(QColor(100, 60, 21));
    camera.p.drawEllipse(QPoint(mainCoorMapX, mainCoorMapY), 180, 180);

    int fieldX = map->width;
    int fieldY = map->height;
    int isometricSpaceX = halfSizeCellX*fieldY;
    int isometricSpaceY = halfSizeCellY*fieldY;

    for(int x = 0; x < fieldX+1; x++) {
        int x1 = mainCoorMapX + isometricSpaceX + x*halfSizeCellX;
        int y1 = mainCoorMapY + x*halfSizeCellY;
        int x2 = mainCoorMapX + x*halfSizeCellX;
        int y2 = mainCoorMapY + isometricSpaceY + x*halfSizeCellY;
//        int x1 = mainCoorMapX + x*halfSizeCellX;
//        int y1 = mainCoorMapY + x*halfSizeCellY;
//        int x2 = mainCoorMapX + isometricSpaceX + x*halfSizeCellX;
//        int y2 = mainCoorMapY - isometricSpaceY + x*halfSizeCellY;
        camera.p.drawLine(x1, y1, x2, y2);
//        qDebug() << "GameWidget::drawGrid(); -- x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2;
    }
    for(int y = 0; y < fieldY+1; y++) {
        int x1 = mainCoorMapX + isometricSpaceX - y*halfSizeCellX;
        int y1 = mainCoorMapY + y*halfSizeCellY;
        int x2 = mainCoorMapX + isometricSpaceX*2 - (halfSizeCellX*(fieldY-fieldX)) - y*halfSizeCellX;
        int y2 = mainCoorMapY + isometricSpaceY - (halfSizeCellY*(fieldY-fieldX)) + y*halfSizeCellY;
//        int x1 = mainCoorMapX + y*halfSizeCellX;
//        int y1 = mainCoorMapY - y*halfSizeCellY;
//        int x2 = mainCoorMapX + isometricSpaceX + y*halfSizeCellX;
//        int y2 = mainCoorMapY + isometricSpaceY - y*halfSizeCellY;
        camera.p.drawLine(x1, y1, x2, y2);
//        qDebug() << "GameWidget::drawGrid(); -- x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2;
    }
}

void MapWidgetGL::mousePressEvent(QMouseEvent *event) {
    int x = event->x();
    int y = event->y();
    qDebug() << "MapWidgetGL::mousePressEvent(" << event << "); -- x:" << x << " y:" << y;
    int mouseX = x;
    int mouseY = y;
    whichCell(mouseX, mouseY);
}

bool MapWidgetGL::whichCell(int &mouseX, int &mouseY) {
    qDebug() << "MapWidgetGL::whichCell(" << mouseX << ", " << mouseY << "); -- " << camera.toString();
    int mainCoorMapX = camera.x;
    int mainCoorMapY = camera.y;
    int sizeCellX = camera.cellSizeX*camera.zoom;
    int sizeCellY = camera.cellSizeY*camera.zoom;
    int fieldX = map->width;
    int fieldY = map->height;
    qDebug() << "MapWidgetGL::whichCell(2); - fieldX:" << fieldX << ", fieldY:" << fieldY;

    int gameX, gameY;

    int isometricCoorX = (sizeCellX/2) * fieldY;
    int isometricCoorY = 0;

    int localMouseX = -mainCoorMapX + mouseX - isometricCoorX;
    int localMouseY = -mainCoorMapY + mouseY + sizeCellY;
    qDebug() << "MapWidgetGL::whichCell(3); - localMouseX:" << localMouseX << ", localMouseY:" << localMouseY;

    gameX = (localMouseX/2 + localMouseY) / (sizeCellX/2);
    gameY = -(localMouseX/2 - localMouseY) / (sizeCellX/2);
    qDebug() << "MapWidgetGL::whichCell(4); - gameX:" << gameX << ", gameY:" << gameY;

//    QString text = QString("%1/%2").arg(gameX).arg(gameY);
//    global_text2 = text.toStdString().c_str();

    if(gameX > 0 && gameX < fieldX+1) {
        if(gameY > 0 && gameY < fieldY+1) {
            mouseX = gameX-1;
            mouseY = gameY-1;
            qDebug() << "MapWidgetGL::whichCell(5); - mouseX:" << mouseX << ", mouseY:" << mouseY;
            return true;
        }
    }

    return false;
}

//void MapWidgetGL::wheelEvent(QWheelEvent *event) {
////    scale+=(event->delta()/120);
////    qDebug() << "MapWidgetGL::wheelEvent(1); -- event.delta():" << event->delta() << " scale:" << scale;
////    qDebug() << "MapWidgetGL::wheelEvent(2); -- &ctrlPressed:" << &this->ctrlPressed << " ctrlPressed:" << this->ctrlPressed;
//    qDebug() << "MapWidgetGL:" << this << ":wheelEvent(); -- this->ctrlPressed:"/* << this->ctrlPressed*/;

////    if(this->ctrlPressed) {
//        qDebug() << "MapWidgetGL::wheelEvent(2); -- event.delta():" << event->delta() << " scale:" << camera.zoom;
//        if(event->delta() > 0) {
//            if(camera.zoom < 5) {
//                camera.zoom += 0.1;
//            }
//        } else {
////            if(parentWidget()->height() < (rows*tileHeight)*scale) {
//                qDebug() << "qweqwe";
//                camera.zoom -= 0.1;
////            } else {
////                qDebug() << "NOT do";
////            }
//        }
////        setGeometry(QRect(0, 0, columns*(tileWidht*scale), rows*(tileHeight*scale)));
//        repaint();
////    } else {
////        ((MyDockWidget*)parentWidget())->wheelEvent(event);
////    }
//}

//void MapWidgetGL::keyPress(QKeyEvent *event) {
//    qDebug() << "MapWidgetGL::keyPress(" << event << "); -- key:" << event->key();
//}

//void MapWidgetGL::initializeGL() {
//    qDebug() << "MapWidget::initializeGL();";
////    glClearColor(0,0,0,1);
////    glEnable(GL_DEPTH_TEST);
////    glEnable(GL_LIGHT0);
////    glEnable(GL_LIGHTING);
////    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
////    glEnable(GL_COLOR_MATERIAL);
//}

//void MapWidgetGL::paintGL() {
//    qDebug() << "MapWidget::pascal();";
////    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

////    glBegin(GL_TRIANGLES);
////        glColor3f(1.0, 0.0, 0.0);
////        glVertex3f(-0.5, -0.5, 0);
////        glColor3f(0.0, 1.0, 0.0);
////        glVertex3f( 0.5, -0.5, 0);
////        glColor3f(0.0, 0.0, 1.0);
////        glVertex3f( 0.0,  0.5, 0);
////    glEnd();
//}

//void MapWidgetGL::resizeGL(int w, int h) {
//    qDebug() << "MapWidget::resizeGL(" << w << ", " << h << ");";
////    glViewport(0,0,w,h);
////    glMatrixMode(GL_PROJECTION);
////    glLoadIdentity();
////    gluPerspective(45, (float)w/h, 0.01, 100.0);
////    glMatrixMode(GL_MODELVIEW);
////    glLoadIdentity();
////    gluLookAt(0,0,5,0,0,0,0,1,0);
//}
