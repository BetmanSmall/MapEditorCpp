#ifndef DOCKWIDGETLAYERS_H
#define DOCKWIDGETLAYERS_H

#include <QDebug>
#include <QDockWidget>
#include <QLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QPushButton>

#include "maplayers.h"
#include "layer.h"

class DockWidgetLayers : public QDockWidget {
    Q_OBJECT
    QListWidget* listWidget;
    MapLayers* mapLayers;
public:
    explicit DockWidgetLayers(MapLayers* mapLayers, QWidget *parent);

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
