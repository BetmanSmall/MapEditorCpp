#ifndef DOCKWIDGETTILESETS_H
#define DOCKWIDGETTILESETS_H

#include <QDockWidget>
#include <QTabWidget>
#include <QScrollArea>
#include <QVBoxLayout>

#include "tilesets.h"
#include "tileset.h"
#include "tilesetwidget.h"

class DockWidgetTileSets : public QDockWidget {
    Q_OBJECT
    TileSets* tileSets;
    QTabWidget *tabWidget;
//    QVBoxLayout *layout;
public:
    DockWidgetTileSets(TileSets* tileSets, QWidget* parent);
//    void addTileSet(TileSet *tileSet);

    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void tileSelected(Tile* tile);

public slots:
    void tileSelectedSlot(Tile* tile);
};

#endif // DOCKWIDGETTILESETS_H
