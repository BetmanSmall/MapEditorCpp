#include "map.h"

Map::Map() {
    properties.insert("key1", "value1");
}

QMap<QString, QString> *Map::getProperties() {
    return &properties;
}

TileSets Map::getTileSets() {
    return tileSets;
}

/*void Map::loadMap(QString filePath) {
//    QString fileName = fileName.left(filePath.mid(filePath.lastIndexOf("/")+1).lastIndexOf("."));
    QString fileName = "arena";
    qDebug() << "fileName: " << fileName;
    QDomDocument domDocument(fileName);
    QFile file(filePath);
    qDebug() << "Try open file: " << filePath;
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Can't load map: " << fileName;
        return;
    }
    if (!domDocument.setContent(&file)) {
        qDebug() << "Could not convert to xml format: " << fileName;
        file.close();
        return;
    }
    file.close();
    this->mapPath = filePath;
    QDomElement mapElement = domDocument.documentElement();
    QDomNamedNodeMap attributes = mapElement.attributes();
    qDebug() << "attributes.length():" << attributes.length();
    for(int k = 0; k < attributes.length(); k++) {
        QDomNode domNode = attributes.item(k);
        if(domNode.isAttr()) {
            QDomAttr attribute = domNode.toAttr();
            properties.insert(attribute.name(), attribute.value());
//            qDebug() << attribute.name() <<  ":" << attribute.value();
        }
    }
    QDomNodeList tileSetsNodeList = mapElement.elementsByTagName("tileset");
    for(int k = 0; k < tileSetsNodeList.length(); k++) {
        QDomNode tileSetNode = tileSetsNodeList.item(k);
        QString source = tileSetNode.toElement().attribute("source");
        TileSet *tileSet;
        if(source == NULL) {
            tileSet = new TileSet(tileSetNode.toElement(), mapPath);
        } else {
        }
        tileSets.append(*tileSet);
    }
    QDomNodeList layersNodeList = mapElement.elementsByTagName("layer");
    for(int k = 0; k < layersNodeList.length(); k++) {
        QDomNode layerNode = layersNodeList.item(k);
    }
    domDocument.clear();
    foreach (QString name, properties.keys()) {
        qDebug() << name << ":" << properties.value(name);
    }
}*/
