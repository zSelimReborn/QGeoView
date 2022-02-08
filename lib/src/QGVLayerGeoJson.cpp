#include "QGVLayerGeoJson.h"
#include "QGVDrawItem.h"
#include "QGVLayerShape.h"

#include "shapefil.h"

#include <QFile>
#include <QTemporaryDir>
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

QGVLayerGeoJson::QGVLayerGeoJson(QGVItem* parent, const QString& sourceFile) :
    QGVLayerFile(parent, sourceFile)
{
    initializeMappingShapeTypes();
}

void QGVLayerGeoJson::buildShapes()
{
    const auto document = readFile();
    if (document.isNull()) {
        qDebug() << "QGVLayerGeoJson::buildShapes(): Unable to open" << getSourceFileName();
        return;
    }

    const auto documentObj = document.object();
    const auto shapesObj = documentObj.value(shapesKey);
    const auto shapesArray = shapesObj.toArray();

    for (const auto &shapeData : shapesArray) {
        auto itemData = createNewItemDataFromJsonFeature(shapeData);
        auto newShape = QGVLayerFile::createNewShape(getParent(), itemData);
        if (newShape != nullptr) {
            addShape(newShape);
        }
    }
}

void QGVLayerGeoJson::initializeMappingShapeTypes()
{
    mMappingShapeTypes.clear();

    mMappingShapeTypes["Point"]         = QGVLayerShapeType::Point;
    mMappingShapeTypes["LineString"]    = QGVLayerShapeType::Line;
    mMappingShapeTypes["Polygon"]       = QGVLayerShapeType::Polygon;
}

QGVLayerShapeType QGVLayerGeoJson::getShapeTypeFromString(const QString& type)
{
    if (mMappingShapeTypes.contains(type)) {
        return mMappingShapeTypes[type];
    }

    return QGVLayerShapeType();
}

QJsonDocument QGVLayerGeoJson::readFile()
{
    QString val;
    QFile reader;
    reader.setFileName(getSourceFileName());
    reader.open(QIODevice::ReadOnly | QIODevice::Text);
    val = reader.readAll();
    reader.close();

    return QJsonDocument::fromJson(val.toUtf8());
}

QGVLayerItemData QGVLayerGeoJson::createNewItemDataFromJsonFeature(const QJsonValue& shapeData)
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
