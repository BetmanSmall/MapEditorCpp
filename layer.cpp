#include "layer.h"

//Layer::Layer(QDomElement layerElement, QVector<TileSet> tileSets) {
////    properties = new QHash<QString, QString>;
//    QDomNamedNodeMap attributes = layerElement.attributes();
//    for(int k = 0; k < attributes.length(); k++) {
//        QDomNode node = attributes.item(k);
//        if(node.isAttr()) {
//            QDomAttr attr = node.toAttr();
//            properties.insert(attr.name(), attr.value());
//        }
//    }

//    QDomNode propertiesNode = layerElement.namedItem("properties");
//    if(!propertiesNode.isNull()) {
//        QDomElement propertyNode = propertiesNode.firstChildElement();
//        while (!propertyNode.isNull()) {
//            QString tagName = propertyNode.tagName();
//            if(tagName == "property") {
//                QString name = propertyNode.attribute("name");
//                QString value = propertyNode.attribute("value");
//                if(name != NULL && value != NULL) {
//                    properties.insert(name, value);
//                }
//            }
//            propertyNode = propertyNode.nextSiblingElement();
//        }
//    }

//    QDomElement dataElement = layerElement.firstChildElement("data");
//    QString encoding = dataElement.attribute("encoding");
//    if(encoding == NULL) {
//        QDomNodeList tilesNodeList = layerElement.toElement().elementsByTagName("tile");
//        for(int l = 0; l < tilesNodeList.length(); l++) {
//            QDomNode tileNode = tilesNodeList.item(l);
//            QString gid = tileNode.toElement().attribute("gid");
//            if(gid != NULL) {
//                for(int k = tileSets.length()-1; k >= 0; k--) {
//                    TileSet tileSet = tileSets.value(k);
//                    QString firstTileID = tileSet.properties->value("firstgid");
//                    if(firstTileID != NULL) {
//                        if(gid.toInt() >= firstTileID.toInt()) {
//                            int id = gid.toInt() - firstTileID.toInt();
//                            Tile tile = tileSet.tiles.value(id);
//                            tiles.append(&tile);
//                        }
//                    }
//                }
//            }
//        }
//    } else if(encoding == "csv") {
//        qDebug() << "Not released this fucking encoding CSV!";
//    }
//}
