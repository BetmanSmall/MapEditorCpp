#include "dockwidgetlayers.h"

DockWidgetLayers::DockWidgetLayers(MapLayers* mapLayers, QWidget* parent) : QDockWidget("Layers", parent) {
//    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    addDockWidget(Qt::LeftDockWidgetArea, dock);
//    setFeatures(QDockWidget::NoDockWidgetFeatures); // thus blocking dock widget area
    this->mapLayers = mapLayers;
    this->listWidget = new QListWidget(this);
    setWidget(listWidget);
//    listWidget->setSizeAdjustPolicy(QListWidget::AdjustToContents);
//    listWidget->resize(300, 300);
    for(int l = mapLayers->size()-1; l >= 0; l--) {
        Layer* layer = mapLayers->get(l);
        QString name = layer->getName();
        QListWidgetItem* item = new QListWidgetItem(name, listWidget);
        item->setData(Qt::UserRole, QString("%1").arg(l));
//        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        if(layer->isVisible() && layer->getOpacity() != 0) {
            item->setCheckState(Qt::Checked);
        }
    }
    connect(listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(currentRowChanged(int)));
    connect(listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(itemChanged(QListWidgetItem*)));
    connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClicked(QListWidgetItem*)));
    connect(listWidget, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(itemPressed(QListWidgetItem*)));
}

void DockWidgetLayers::currentRowChanged(int currentRow) {
    qDebug() << "DockWidgetLayers::currentRowChanged();";
}

void DockWidgetLayers::itemChanged(QListWidgetItem *item) {
    int index = item->data(Qt::UserRole).toInt();
//    int index = listWidget->currentRow();
    qDebug() << "DockWidgetLayers::itemChanged(); -- item:" << item->text() << ":" << item->checkState() << " index:" << index;
    Layer* l = mapLayers->get(index);
    l->setVisible(item->checkState() == Qt::Checked ? true : false);
    emit repaintMap();
}

void DockWidgetLayers::itemDoubleClicked(QListWidgetItem* item) {
    qDebug() << "DockWidgetLayers::itemDoubleClicked();";
}

void DockWidgetLayers::itemPressed(QListWidgetItem *item) {
    qDebug() << "DockWidgetLayers::itemPressed();";
}
