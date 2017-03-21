#include "dockwidgetlayers.h"

DockWidgetLayers::DockWidgetLayers(Map *map, QWidget* parent) : QDockWidget("Layers", parent) {
//    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    addDockWidget(Qt::LeftDockWidgetArea, dock);
//    setFeatures(QDockWidget::NoDockWidgetFeatures); // thus blocking dock widget area
    this->map = map;
    this->mapLayers = map->getMapLayers();
    this->listWidget = new QListWidget();
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

    QPushButton* addButton = new QPushButton("+");
    connect(addButton, SIGNAL(pressed()), this, SLOT(addEmptyLayer()));
    QPushButton* delButton = new QPushButton("-");
    connect(delButton, SIGNAL(pressed()), this, SLOT(delSelectedLayer()));
    QPushButton* upButton = new QPushButton("Up");
    connect(upButton, SIGNAL(pressed()), this, SLOT(upLayer()));
    QPushButton* downButton = new QPushButton("Down");
    connect(downButton, SIGNAL(pressed()), this, SLOT(downLayer()));

    QBoxLayout* mainLayout = new QVBoxLayout;
    QBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(delButton);
    buttonsLayout->addWidget(upButton);
    buttonsLayout->addWidget(downButton);
    mainLayout->addWidget(listWidget);
    mainLayout->addLayout(buttonsLayout);

    QGroupBox* groupBox = new QGroupBox;
    groupBox->setLayout(mainLayout);
    setWidget(groupBox);
}

void DockWidgetLayers::currentRowChanged(int currentRow) {
    qDebug() << "DockWidgetLayers::currentRowChanged(" << currentRow << ");";
    emit layerSelected(currentRow);
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

void DockWidgetLayers::addEmptyLayer() {
    qDebug() << "DockWidgetLayers::addEmptyLayer();";
    Layer* layer = map->addNewLayer();
    QListWidgetItem* item = new QListWidgetItem("New Layer " + QString::number(mapLayers->size()-1), listWidget);
    item->setData(Qt::UserRole, QString("%1").arg(mapLayers->size()-1));
    item->setCheckState(Qt::Unchecked);
    if(layer->isVisible() && layer->getOpacity() != 0) {
        item->setCheckState(Qt::Checked);
    }
}

void DockWidgetLayers::delSelectedLayer() {
    qDebug() << "DockWidgetLayers::delSelectedLayer();";
}

void DockWidgetLayers::upLayer() {
    qDebug() << "DockWidgetLayers::upLayer();";
}

void DockWidgetLayers::downLayer() {
    qDebug() << "DockWidgetLayers::downLayer();";
}
