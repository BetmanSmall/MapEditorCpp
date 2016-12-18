#include "mapwidgetgl.h"

MapWidgetGL::MapWidgetGL(Map *map, QWidget *parent)
    : QWidget(parent) {
    qDebug() << "MapWidget::MapWidget();";
    this->map = map;
    this->setGeometry(QRect(0, 0, map->getProperties()->value("width").toInt()*camera.cellSizeX, map->getProperties()->value("height").toInt()*camera.cellSizeY));
}

MapWidgetGL::~MapWidgetGL() {
    qDebug() << "MapWidget::~MapWidget();";
}

void MapWidgetGL::paintEvent(QPaintEvent *event) {
//    qDebug() << "MapWidgetGL::paintEvent(); -- map:" << map;
    camera.p.begin(this);
//    drawFullField();
    drawGrid();
//    camera.p.drawLine(0, 0, width(), height());
//    camera.p.drawLine(width(), 0, 0, height());
//    camera.p.drawEllipse(0, 0, 200, 200);
    camera.p.end();
//    qDebug() << "MapWidgetGL::paintEvent(); -- !!END!!";
}

void MapWidgetGL::drawGrid() {
//    qDebug() << "MapWidgetGL::drawGrid(); -- camera.x:" << camera.x << " camera.y:" << camera.y << " camera.cellSizeX:" << camera.cellSizeX << " camera.cellSizeY:" << camera.cellSizeY;
    int mainCoorMapX = camera.x;
    int mainCoorMapY = camera.y + height()/2;
    int sizeCell = camera.cellSizeX;
    camera.p.setPen(QColor(100, 60, 21));
    camera.p.drawEllipse(QPoint(mainCoorMapX, mainCoorMapY), 180, 180);

    int fieldX = map->getProperties()->value("width").toInt();
    int fieldY = map->getProperties()->value("height").toInt();

//    if(field.getIsometric()) {
        int halfSizeCellX = camera.cellSizeX/2;
        int halfSizeCellY = camera.cellSizeY/2;
//        int sizeCellX = field.getTileMapWidth()/2;
//        int sizeCellY = field.getTileMapHeight()/2;
        int isometricSpaceX = halfSizeCellX*fieldY;
        int isometricSpaceY = halfSizeCellY*fieldY;

//        qDebug() << "GameWidget::drawGrid(); -- isometricSpaceX: " << isometricSpaceX;
//        qDebug() << "GameWidget::drawGrid(); -- isometricSpaceY: " << isometricSpaceY;
//        qDebug() << "GameWidget::drawGrid(); -- fieldX: " << fieldX;
//        qDebug() << "GameWidget::drawGrid(); -- fieldY: " << fieldY;
//        qDebug() << "GameWidget::drawGrid(); -- halfSizeCellX: " << halfSizeCellX;
//        qDebug() << "GameWidget::drawGrid(); -- halfSizeCellY: " << halfSizeCellY;

        for(int x = 0; x < fieldX+1; x++) {
            int x1 = mainCoorMapX + x*halfSizeCellX;
            int y1 = mainCoorMapY + x*halfSizeCellY;
            int x2 = mainCoorMapX + isometricSpaceX + x*halfSizeCellX;
            int y2 = mainCoorMapY - isometricSpaceY + x*halfSizeCellY;
//            int x1 = mainCoorMapX + isometricSpaceX + x*halfSizeCellX;
//            int y1 = mainCoorMapY + x*halfSizeCellY;
//            int x2 = mainCoorMapX + x*halfSizeCellX;
//            int y2 = mainCoorMapY + isometricSpaceY + x*halfSizeCellY;
            camera.p.drawLine(x1, y1, x2, y2);
//            qDebug() << "GameWidget::drawGrid(); -- x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2;
        }
        for(int y = 0; y < fieldY+1; y++) {
            int x1 = mainCoorMapX + y*halfSizeCellX;
            int y1 = mainCoorMapY - y*halfSizeCellY;
            int x2 = mainCoorMapX + isometricSpaceX + y*halfSizeCellX;
            int y2 = mainCoorMapY + isometricSpaceY - y*halfSizeCellY;
//            int x1 = mainCoorMapX + isometricSpaceX - y*halfSizeCellX;
//            int y1 = mainCoorMapY + y*halfSizeCellY;
//            int x2 = mainCoorMapX + isometricSpaceX*2 - (halfSizeCellX*(fieldY-fieldX)) - y*halfSizeCellX;
//            int y2 = mainCoorMapY + isometricSpaceY - (halfSizeCellY*(fieldY-fieldX)) + y*halfSizeCellY;
            camera.p.drawLine(x1, y1, x2, y2);
//            qDebug() << "GameWidget::drawGrid(); -- x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2;
        }
//    } else {
//        for(int x = 0; x < fieldX+1; x++) {
//            p.drawLine(mainCoorMapX + spaceWidget + x*sizeCell, mainCoorMapY + spaceWidget, mainCoorMapX + spaceWidget + x*sizeCell, mainCoorMapY + spaceWidget + sizeCell*fieldY);
//        }
//        for(int y = 0; y < fieldY+1; y++) {
//            p.drawLine(mainCoorMapX + spaceWidget, mainCoorMapY + spaceWidget + y*sizeCell, mainCoorMapX + spaceWidget + sizeCell*fieldX, mainCoorMapY + spaceWidget + y*sizeCell);
//        }
//    }
}

void MapWidgetGL::drawFullField() {
//    if(field.getIsometric()) {
    int mainCoorMapX = camera.x;
    int mainCoorMapY = camera.y + height()/2;
    int sizeCellX = camera.cellSizeX;
    int sizeCellY = camera.cellSizeY;
    int halfSizeCellX = camera.cellSizeX/2;
    int halfSizeCellY = camera.cellSizeY/2;
//    int sizeX = (width()/sizeCellX)+1;
//    int sizeY = (height()/sizeCellY)*2+2;
    int fieldX = map->getProperties()->value("width").toInt();
    int fieldY = map->getProperties()->value("height").toInt();

    MapLayers *mapLayer = map->getMapLayers();
//    for (int l = 0; l < halfSizeCellX; l++) {
        Layer *layer = mapLayer->get(8);
//        qDebug() << "MapWidgetGL::drawFullField(); -- pix:" << pix.isNull();
//        camera.p.drawPixmap(mainCoorMapX, mainCoorMapY, sizeCellX, sizeCellY*2, pix);

        int isometricSpaceX = 0;
        int isometricSpaceY = halfSizeCellY;
//        int isometricSpaceX = halfSizeCellX*fieldY;
//        int isometricSpaceY = halfSizeCellY*fieldY;
        for(int y = 0; y < fieldY; y++) {
            for(int x = 0; x < fieldX; x++) {
//                QPixmap pix = layer->getCell(x, y)->getTile()->getPixmap();
                Cell *cell = layer->getCell(x, y);
                if(cell != NULL) {
                    Tile *tile = cell->getTile();
                    if(tile != NULL) {
                        QPixmap pix = QPixmap(tile->getPixmap());
                        if(!pix.isNull()) {
                            int pixWidth = pix.width();
                            int pixHeight = pix.height();
                            int drawX = mainCoorMapX + isometricSpaceX + x*halfSizeCellX;
                            int drawY = mainCoorMapY + isometricSpaceY - x*halfSizeCellY - pixHeight;
                            camera.p.drawPixmap(drawX, drawY, sizeCellX, sizeCellY, pix);
                        }
                    } else {
                        qDebug() << "1";
                    }
                } else {
                    qDebug() << "2";
                }
            }
            isometricSpaceX += halfSizeCellX;
            isometricSpaceY += halfSizeCellY;
        }
//    }
}

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
