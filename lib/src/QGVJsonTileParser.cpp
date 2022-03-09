#include "QGVJsonTileParser.h"

#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

namespace  {
    const auto shapesKey            = "features";

    const auto shapeGeometryKey     = "geometry";
    const auto shapePointsKey       = "coordinates";
    const auto shapeTypeKey         = "type";

    const auto shapePropsKey        = "properties";
}

QGVJsonTileParser::QGVJsonTileParser() :
    QGVTileParser()
{
    initializeMappingShapeTypes();
}

void QGVJsonTileParser::initializeMappingShapeTypes()
{
    mMappingShapeTypes.clear();

    mMappingShapeTypes["Point"]         = QGVLayerShapeType::Point;
    mMappingShapeTypes["LineString"]    = QGVLayerShapeType::Line;
    mMappingShapeTypes["Polygon"]       = QGVLayerShapeType::Polygon;
}

QByteArray QGVJsonTileParser::readFile(const QString& fileName)
{
    QByteArray content;
    QFile reader;
    reader.setFileName(fileName);
    reader.open(QIODevice::ReadOnly | QIODevice::Text);
    content = reader.readAll();
    reader.close();

    return content;
}

QList<QGVDrawItem*> QGVJsonTileParser::buildFromFile(const QGV::GeoTilePos& tile, const QString& fileName, const QString& tileType)
{
    const auto content = readFile(fileName);
    return buildFromContent(tile, content, tileType);
}

QList<QGVDrawItem*> QGVJsonTileParser::buildFromContent(const QGV::GeoTilePos& tile, const QByteArray& content, const QString& tileType)
{
    QList<QGVDrawItem*> shapes{};

    const auto document = QJsonDocument::fromJson(content);
    const auto documentObj = document.object();
    const auto layers = documentObj.keys();

    for (const auto& layer : layers) {
        if (layer != tileType) {
            qDebug() << "[JSON] Layer" << layer << "to skip";
            continue;
        }

        const auto layerObj = documentObj.value(layer).toObject();
        const auto shapesObj = layerObj.value(shapesKey);
        const auto shapesArray = shapesObj.toArray();

        shapes.reserve(shapesArray.size());

        for (const auto& shapeData : shapesArray) {
            auto itemData = createNewItemDataFromJsonFeature(shapeData);
            // convertInGeoCoordinates(itemData);
            const auto newShape = QGVLayerFile::createNewShape(nullptr, itemData, getPointsIcon(), getLinesColor(), getPolygonsColor());
            shapes.append(newShape);
        }
    }

    return shapes;
}

QGVLayerItemData QGVJsonTileParser::createNewItemDataFromJsonFeature(const QJsonValue& shapeData)
{
    const auto shapeObj = shapeData.toObject();

    const auto shapeGeometry = shapeObj.value(shapeGeometryKey).toObject();
    const auto shapeProperties = shapeObj.value(shapePropsKey).toObject();
    const auto shapeTypeString = shapeGeometry.value(shapeTypeKey).toString();
    const auto shapeType = getShapeTypeFromString(shapeTypeString);

    QGVLayerItemData::GeoCoordinates coordinates;
    QGVLayerItemData::Properties props;

    for (const auto& shapeProperty : shapeProperties.keys()) {
        const auto shapePropertyValue = shapeProperties.value(shapeProperty).toVariant();
        props.insert(shapeProperty, shapePropertyValue);
    }

    const auto shapeCoordinates = shapeGeometry.value(shapePointsKey).toArray();

    // Build point shape
    if (shapeType == QGVLayerShapeType::Point) {
        const auto longitude    = shapeCoordinates[0].toDouble();
        const auto latitude     = shapeCoordinates[1].toDouble();
        const auto pointPosition = QGV::GeoPos(latitude, longitude);

        coordinates.append(pointPosition);
    } else {
        // Build Line or Polygon
        auto polygonPoints = shapeCoordinates;
        if (shapeType == QGVLayerShapeType::Polygon) {
            polygonPoints = shapeCoordinates[0].toArray();
        }

        for (const QJsonValue& polygonPoint : polygonPoints) {
            const auto longitude = polygonPoint[0].toDouble();
            const auto latitude = polygonPoint[1].toDouble();
            const auto polygonPointPosition = QGV::GeoPos(latitude, longitude);

            coordinates.append(polygonPointPosition);
        }
    }

    return QGVLayerItemData(coordinates, props, shapeType);
}

void QGVJsonTileParser::convertInGeoCoordinates(const QGV::GeoTilePos& tile, QGVLayerItemData& shapeData, const quint32& extent)
{

}

QGVLayerShapeType QGVJsonTileParser::getShapeTypeFromString(const QString& type)
{
    if (mMappingShapeTypes.contains(type)) {
        return mMappingShapeTypes[type];
    }

    return QGVLayerShapeType();
}
