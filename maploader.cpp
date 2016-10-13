#include "maploader.h"
#include "animatedtile.h"

MapLoader::MapLoader() {

}

Map* MapLoader::load(QString mapPath) {
    QDomDocument *domDocument = loadDomDocument(mapPath);

    QDomElement mapElement = domDocument->documentElement();
    QMap<QString, QPixmap> textures;
    QVector<QString> textureFiles = loadTilesets(mapElement, mapPath);
    qDebug() << textureFiles;
    textureFiles += loadImages(mapElement, mapPath);
    qDebug() << textureFiles;

    foreach (QString pixFilePath, textureFiles) {
        QPixmap pix(pixFilePath);
        if(!pix.isNull()) {
            textures.insert(pixFilePath, pix);
        } else {
            qDebug() << "MapLoader::load() -- Can't load QPixmap: " << pixFilePath;
        }
    }

    Map *map = loadMap(mapElement, mapPath, textures);
}

QDomDocument *MapLoader::loadDomDocument(QString xmlFile) {
    QString xmlName = xmlFile.mid(xmlFile.lastIndexOf("/")+1);
    qDebug() << "Try load xmlFile: " << xmlFile;
    QDomDocument *domDocument = new QDomDocument(xmlName);

    QFile file(xmlFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Can't load map: " << xmlFile;
        return NULL;
    }
    if (!domDocument->setContent(&file)) {
        qDebug() << "Could not convert to xml format: " << xmlFile;
        file.close();
        return NULL;
    }
    file.close();
    qDebug() << "Load xml file: " << xmlFile;
    return domDocument;
}

QVector<QString> MapLoader::loadTilesets(QDomElement mapElement, QString mapPath) {
    QVector<QString> images;
    QDomNodeList tileSetsNodeList = mapElement.elementsByTagName("tileset");
    for(int k = 0; k < tileSetsNodeList.length(); k++) {
        QDomNode tileSetNode = tileSetsNodeList.item(k);
        QString source = tileSetNode.toElement().attribute("source");
        if(source != NULL) {
            QString tsxFile = findFile(mapPath, source);
            tileSetNode = loadDomDocument(tsxFile)->documentElement();
            QDomElement imageElement = tileSetNode.firstChildElement("image");
            if(!imageElement.isNull()) {
                QString imageSource = imageElement.attribute("source");
                QString imageFile = findFile(tsxFile, imageSource);
                images.append(imageFile);
            } else {
                QDomNodeList tilesNodeList = tileSetNode.toElement().elementsByTagName("tile");
                for(int l = 0; l < tilesNodeList.length(); l++) {
                    QDomNode tileNode = tilesNodeList.item(l);
                    QString imageSource = tileNode.firstChildElement("image").attribute("source");
                    QString imageFile = findFile(tsxFile, imageSource);
                    images.append(imageFile);
                }
            }
        } else {
            QDomElement imageElement = tileSetNode.firstChildElement("image");
            if(!imageElement.isNull()) {
                QString imageSource = imageElement.attribute("source");
                QString imageFile = findFile(mapPath, imageSource);
                images.append(imageFile);
            } else {
                QDomNodeList tilesNodeList = tileSetNode.toElement().elementsByTagName("tile");
                for(int l = 0; l < tilesNodeList.length(); l++) {
                    QDomNode tileNode = tilesNodeList.item(l);
                    QString imageSource = tileNode.firstChildElement("image").attribute("source");
                    QString imageFile = findFile(mapPath, imageSource);
                    images.append(imageFile);
                }
            }
        }
    }
    return images;
}

QVector<QString> MapLoader::loadImages(QDomElement mapElement, QString mapPath) {
    QVector<QString> images;
    QDomNodeList imageLaysersNodeList = mapElement.elementsByTagName("imagelayer");
    for(int k = 0; k < imageLaysersNodeList.length(); k++) {
        QDomNode imageLayerNode = imageLaysersNodeList.item(k);
        QDomElement imageElement = imageLayerNode.firstChildElement("image");
        QString source = imageElement.attribute("source", NULL);
        if(source != NULL) {
            QString imageFile = findFile(mapPath, source);
            if(!images.contains(imageFile)) {
                images.append(imageFile);
            }
        }
    }
    return images;
}

Map *MapLoader::loadMap(QDomElement mapElement, QString mapPath, QMap<QString, QPixmap> textures) {
    Map *map = new Map();

    QString mapOrientation = mapElement.attribute("orientation", NULL);
    int mapWidth = mapElement.attribute("width", "0").toInt();
    int mapHeight = mapElement.attribute("height", "0").toInt();
    int tileWidth = mapElement.attribute("tilewidth", "0").toInt();
    int tileHeight = mapElement.attribute("tileheight", "0").toInt();
    int hexSideLength = mapElement.attribute("hexsidelength", "0").toInt();
    QString staggerAxis = mapElement.attribute("staggeraxis", NULL);
    QString staggerIndex = mapElement.attribute("staggerindex", NULL);
    QString mapBackgroundColor = mapElement.attribute("backgroundcolor", NULL);

    QMap<QString, QString> *mapProperties = map->getProperties();
    if(mapOrientation != NULL) {
        mapProperties->insert("orientation", mapOrientation);
    }
    mapProperties->insert("width", QString::number(mapWidth));
    mapProperties->insert("height", QString::number(mapHeight));
    mapProperties->insert("tilewidth", QString::number(tileWidth));
    mapProperties->insert("tileheight", QString::number(tileHeight));
    mapProperties->insert("hexsidelength", QString::number(hexSideLength));
    if (staggerAxis != NULL) {
        mapProperties->insert("staggeraxis", staggerAxis);
    }
    if (staggerIndex != NULL) {
        mapProperties->insert("staggerindex", staggerIndex);
    }
    if (mapBackgroundColor != NULL) {
        mapProperties->insert("backgroundcolor", mapBackgroundColor);
    }

    mapTileWidth = tileWidth;
    mapTileHeight = tileHeight;
    mapWidthInPixels = mapWidth * tileWidth;
    mapHeightInPixels = mapHeight * tileHeight;

    if (mapOrientation != NULL) {
        if (mapOrientation == "staggered") {
            if (mapHeight > 1) {
                mapWidthInPixels += tileWidth / 2;
                mapHeightInPixels = mapHeightInPixels / 2 + tileHeight / 2;
            }
        }
    }

    QDomElement propertiesElement = mapElement.firstChildElement("properties");
    if (!propertiesElement.isNull()) {
        loadProperties(map->getProperties(), propertiesElement);
    }
    qDebug() << *(map->getProperties());

    QDomNodeList tileSetsNodeList = mapElement.elementsByTagName("tileset");
    for(int k = 0; k < tileSetsNodeList.length(); k++) {
        QDomNode tileSetNode = tileSetsNodeList.item(k);
        loadTileSet(map, tileSetNode.toElement(), mapPath, textures);
    }
}


void MapLoader::loadProperties(QMap<QString, QString> *properties, QDomElement propertiesElement) {
    if (propertiesElement.isNull()) {
        return;
    }
    if (propertiesElement.nodeName() == "properties") {
        QDomNodeList propertieNodeList = propertiesElement.elementsByTagName("property");
        for(int k = 0; k < propertieNodeList.length(); k++) {
            QDomNode propertyNode = propertieNodeList.item(k);
            QString name = propertyNode.toElement().attribute("name", NULL);
            QString value = propertyNode.toElement().attribute("value", NULL);
            if(value == NULL) {
                value = propertyNode.toElement().nodeValue();
            }
            properties->insert(name, value);
        }
    }
}

void MapLoader::loadTileSet(Map *map, QDomElement tileSetElement, QString mapPath, QMap<QString, QPixmap> textures) {
    if(tileSetElement.nodeName() == "tileset") {
        QString name = tileSetElement.attribute("name", NULL);
        int firstgid = tileSetElement.attribute("firstgid", "1").toInt();
        int tilewidth = tileSetElement.attribute("tilewidth", "0").toInt();
        int tileheight = tileSetElement.attribute("tileheight", "0").toInt();
        int spacing = tileSetElement.attribute("spacing", "0").toInt();
        int margin = tileSetElement.attribute("margin", "0").toInt();
        QString source = tileSetElement.attribute("source", NULL);

        int offsetX = 0;
        int offsetY = 0;

        QString imageSource = "";
        int imageWidth = 0, imageHeight = 0;

        QString imagePath = "";
        if (source != NULL) {
            QString tsx = findFile(mapPath, source);
//            try {
                tileSetElement = loadDomDocument(tsx)->documentElement();
                name = tileSetElement.attribute("name", NULL);
                tilewidth = tileSetElement.attribute("tilewidth", "0").toInt();
                tileheight = tileSetElement.attribute("tileheight", "0").toInt();
                spacing = tileSetElement.attribute("spacing", "0").toInt();
                margin = tileSetElement.attribute("margin", "0").toInt();
                QDomElement offsetElement = tileSetElement.firstChildElement("tileoffset");
                if (!offsetElement.isNull()) {
                    offsetX = offsetElement.attribute("x", "0").toInt();
                    offsetY = offsetElement.attribute("y", "0").toInt();
                }
                QDomElement imageElement = tileSetElement.firstChildElement("image");
                if (!imageElement.isNull()) {
                    imageSource = imageElement.attribute("source");
                    imageWidth = imageElement.attribute("width", "0").toInt();
                    imageHeight = imageElement.attribute("height", "0").toInt();
                    imagePath = findFile(tsx, imageSource);
                }
//            } catch (IOException e) {
//                throw new GdxRuntimeException("Error parsing external tileset.");
//            }
        } else {
            QDomElement offsetElement = tileSetElement.firstChildElement("tileoffset");
            if (!offsetElement.isNull()) {
                offsetX = offsetElement.attribute("x", "0").toInt();
                offsetY = offsetElement.attribute("y", "0").toInt();
            }
            QDomElement imageElement = tileSetElement.firstChildElement("image");
            if (!imageElement.isNull()) {
                imageSource = imageElement.attribute("source");
                imageWidth = imageElement.attribute("width", "0").toInt();
                imageHeight = imageElement.attribute("height", "0").toInt();
                imagePath = findFile(mapPath, imageSource);
            }
        }

        TileSet tileset(name);
//        tileset.setName(name);
        tileset.getProperties()->insert("firstgid", QString::number(firstgid));
        if (imagePath != "") {
            QPixmap texture = textures.value(imagePath);

            QMap<QString, QString> *props = tileset.getProperties();
            props->insert("imagesource", imageSource);
            props->insert("imagewidth", QString::number(imageWidth));
            props->insert("imageheight", QString::number(imageHeight));
            props->insert("tilewidth", QString::number(tilewidth));
            props->insert("tileheight", QString::number(tileheight));
            props->insert("margin", QString::number(margin));
            props->insert("spacing", QString::number(spacing));

            int stopWidth = texture.width() - tilewidth;
            int stopHeight = texture.height() - tileheight;

            int id = firstgid;

            for (int y = margin; y <= stopHeight; y += tileheight + spacing) {
                for (int x = margin; x <= stopWidth; x += tilewidth + spacing) {
                    QPixmap tilePix = texture.copy(x, y, tilewidth, tileheight);
                    Tile tile(tilePix);
                    tile.setId(id);
                    tile.setOffsetX(offsetX);
                    tile.setOffsetY(flipY ? -offsetY : offsetY);
                    tileset.putTile(id++, tile);
                }
            }
        } else {
            QDomNodeList tilesNodeList = tileSetElement.elementsByTagName("tile");
            for(int k = 0; k < tilesNodeList.length(); k++) {
                QDomNode tileNode = tilesNodeList.item(k);
                QDomElement imageElement = tileNode.firstChildElement("image");
                if (!imageElement.isNull()) {
                    imageSource = imageElement.attribute("source");
                    imageWidth = imageElement.attribute("width", "0").toInt();
                    imageHeight = imageElement.attribute("height", "0").toInt();
                    imagePath = findFile(mapPath, imageSource);
                }
                QPixmap texture = textures.value(imagePath);
//                TextureRegion texture = imageResolver.getImage(imagePath.path());
                Tile tile(texture);
                tile.setId(firstgid + tileNode.toElement().attribute("id").toInt());
                tile.setOffsetX(offsetX);
                tile.setOffsetY(flipY ? -offsetY : offsetY);
                tileset.putTile(tile.getId(), tile);
            }
        }
        QVector<AnimatedTile> animatedTiles;

        QDomNodeList tilesNodeList = tileSetElement.elementsByTagName("tile");
        for(int k = 0; k < tilesNodeList.length(); k++) {
            QDomElement tileElement = tilesNodeList.item(k).toElement();
            int localtid = tileElement.attribute("id", "0").toInt();
            Tile tile = tileset.getTile(firstgid + localtid);
            if (tile != null) {
                Element animationElement = tileElement.getChildByName("animation");
                if (animationElement != null) {

                    Array<StaticTiledMapTile> staticTiles = new Array<StaticTiledMapTile>();
                    IntArray intervals = new IntArray();
                    for (Element frameElement : animationElement.getChildrenByName("frame")) {
                        staticTiles.add((StaticTiledMapTile) tileset.getTile(firstgid + frameElement.attribute("tileid")));
                        intervals.add(frameElement.attribute("duration"));
                    }

                    AnimatedTiledMapTile animatedTile = new AnimatedTiledMapTile(intervals, staticTiles);
                    animatedTile.setId(tile.getId());
                    animatedTiles.add(animatedTile);
                    tile = animatedTile;
                }

                String terrain = tileElement.attribute("terrain", null);
                if (terrain != null) {
                    tile.getProperties().put("terrain", terrain);
                }
                String probability = tileElement.attribute("probability", null);
                if (probability != null) {
                    tile.getProperties().put("probability", probability);
                }
                Element properties = tileElement.getChildByName("properties");
                if (properties != null) {
                    loadProperties(tile.getProperties(), properties);
                }
            }
        }

        for (AnimatedTiledMapTile tile : animatedTiles) {
            tileset.putTile(tile.getId(), tile);
        }

        Element properties = element.getChildByName("properties");
        if (properties != null) {
            loadProperties(tileset.getProperties(), properties);
        }
        map.getTileSets().addTileSet(tileset);
    }
}

QString MapLoader::findFile(QString mapPath, QString filePath) {
    QString result = mapPath.left(mapPath.lastIndexOf("/"));
    bool finished = false;
    do {
        int slashIndex = filePath.indexOf("/");
        if(slashIndex == -1) {
            result = result.append("/" + filePath);
            finished = true;
        } else {
            QString token = filePath.left(slashIndex);
            filePath = filePath.mid(slashIndex+1);
            if(token == "..") {
                result = result.left(result.lastIndexOf("/"));
            } else {
                result = result.append("/" + token);
            }
        }
    } while (!finished);
    return result;
}
