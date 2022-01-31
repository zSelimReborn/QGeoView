#include "QGVLayerGeoJson.h"
#include "QGVDrawItem.h"
#include "QGVLayerShape.h"

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

QGVLayerGeoJson::QGVLayerGeoJson(QGVItem* parent, const QString& sourceFile) :
    QGVLayerFile(parent, sourceFile)
{

}

void QGVLayerGeoJson::buildShapes()
{
    const auto document = readFile();
    const auto documentObj = document.object();
    const auto shapesObj = documentObj.value(shapesKey);
    const auto shapesArray = shapesObj.toArray();

    for (const auto &shapeData : shapesArray) {
        auto itemData = createNewItemDataFromJsonFeature(shapeData);
        auto newShape = QGVLayerFile::createNewShape(getParent(), itemData);
        addShape(newShape);
    }
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
    const auto shapeType = QGVLayerShapeType::Point;

    const auto shapeCoordinates = shapeGeometry.value(shapePointsKey).toArray();
    QVector<QGV::GeoPos> geoCoordinates;
    for (const auto &shapeCoordinate : shapeCoordinates) {
        qDebug() << shapeCoordinate;
    }
}
