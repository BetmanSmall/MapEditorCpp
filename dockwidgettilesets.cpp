#include "dockwidgettilesets.h"

DockWidgetTileSets::DockWidgetTileSets(TileSets* tileSets, QWidget* parent) : QDockWidget("TileSets", parent) {
    this->tileSets = tileSets;
    this->tabWidget = new QTabWidget();

    for(int t = 0; t < tileSets->size(); t++) {
        TileSet* tileSet = tileSets->getTileSet(t);
        TileSetWidget *tilesSetWidget = new TileSetWidget(this, tileSet);
        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setBackgroundRole(QPalette::Light);
        scrollArea->setWidget(tilesSetWidget);
        tabWidget->addTab(scrollArea, tilesSetWidget->getTileSetName());
        qDebug() << "addTab:" << tilesSetWidget->getTileSetName() << ";" << this;
        connect(tilesSetWidget, SIGNAL(tileSelected(Tile*)), this, SLOT(tileSelectedSlot(Tile*)));
    }
    setWidget(tabWidget);
}

void DockWidgetTileSets::wheelEvent(QWheelEvent *event) {
    qDebug() << "DockWidgetTileSets::wheelEvent(" << event << ");";
}

void DockWidgetTileSets::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    qDebug() << "DockWidgetTileSets::keyPressEvent(" << event << "); - key:" << key;
    ((TileSetWidget*)(((QScrollArea*)(tabWidget->currentWidget()))->widget()))->setCtrl(true);
}

void DockWidgetTileSets::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();
    qDebug() << "DockWidgetTileSets::keyReleaseEvent(" << event << "); - key:" << key;
    ((TileSetWidget*)(((QScrollArea*)(tabWidget->currentWidget()))->widget()))->setCtrl(false);
}

void DockWidgetTileSets::mousePressEvent(QMouseEvent *event) {
    int x = event->x();
    int y = event->y();
    qDebug() << "DockWidgetTileSets::mousePressEvent(" << event << "); -- x:" << x << " y:" << y;
}

void DockWidgetTileSets::tileSelectedSlot(Tile *tile) {
    qDebug() << "DockWidgetTileSets::tileSelectedSlot();";
    emit tileSelected(tile);
}
