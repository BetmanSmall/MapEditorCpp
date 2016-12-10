#include "mydockwidget.h"

MyDockWidget::MyDockWidget(QString title) : QDockWidget(title){
    tabWidget = new QTabWidget();
    setWidget(tabWidget);
}

void MyDockWidget::addTileSet(TileSet *tileSet) {
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Light);
    TileSetWidget *tilesSetWidget = new TileSetWidget(this, tileSet);
    scrollArea->setWidget(tilesSetWidget);
    tabWidget->addTab(scrollArea, tilesSetWidget->getTileSetName());
}

void MyDockWidget::wheelEvent(QWheelEvent *event) {
    qDebug() << "MyDockWidget::wheelEvent(" << event << ");";
}

void MyDockWidget::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    qDebug() << "MyDockWidget::keyPressEvent(" << event << "); - key:" << key;
    ((TileSetWidget*)(((QScrollArea*)(tabWidget->currentWidget()))->widget()))->setCtrl(true);
}

void MyDockWidget::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();
    qDebug() << "MyDockWidget::keyReleaseEvent(" << event << "); - key:" << key;
    ((TileSetWidget*)(((QScrollArea*)(tabWidget->currentWidget()))->widget()))->setCtrl(false);
}

void MyDockWidget::mousePressEvent(QMouseEvent *event) {
    int x = event->x();
    int y = event->y();
    qDebug() << "MyDockWidget::mousePressEvent(" << event << "); -- x:" << x << " y:" << y;
}
