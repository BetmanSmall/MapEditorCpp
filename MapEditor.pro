#-------------------------------------------------
#
# Project created by QtCreator 2016-09-23T19:21:06
#
#-------------------------------------------------

QT       += core gui xml opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapEditor
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    map.cpp \
    tile.cpp \
    maploader.cpp \
    tileset_back.cpp \
    tilesets.cpp \
    tileset.cpp \
    animatedtile.cpp \
    statictile.cpp \
    tilesetwidget.cpp \
    mydockwidget.cpp \
    layer.cpp \
    cell.cpp \
    maplayers.cpp \
    mapwidgetgl.cpp \
    dockwidgetlayers.cpp \
    dockwidgettilesets.cpp

HEADERS  += mainwindow.h \
    map.h \
    tile.h \
    maploader.h \
    tileset_back.h \
    tilesets.h \
    tileset.h \
    animatedtile.h \
    statictile.h \
    tilesetwidget.h \
    mydockwidget.h \
    layer.h \
    cell.h \
    maplayers.h \
    mapwidgetgl.h \
    dockwidgetlayers.h \
    dockwidgettilesets.h

FORMS    += mainwindow.ui
