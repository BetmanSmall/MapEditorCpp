#ifndef DOCKWIDGETLAYERS_H
#define DOCKWIDGETLAYERS_H

#include <QDebug>
#include <QDockWidget>
#include <QLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QPushButton>

#include "map.h"
#include "maplayers.h"
#include "layer.h"

class DockWidgetLayers : public QDockWidget {
    Q_OBJECT
    Map* map;
    MapLayers* mapLayers;
    QListWidget* listWidget;
public:
    explicit DockWidgetLayers(Map* map, QWidget *parent);

private slots:
    void currentRowChanged(int currentRow);
    void itemChanged(QListWidgetItem* item);
    void itemDoubleClicked(QListWidgetItem* item);
    void itemPressed(QListWidgetItem* item);
    void addEmptyLayer();
    void delSelectedLayer();
    void upLayer();
    void downLayer();

signals:
    void repaintMap();
    void layerSelected(int layerIndex);
};

#endif // DOCKWIDGETLAYERS_H
