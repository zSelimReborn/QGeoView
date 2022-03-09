#include "QGVLayerGeoJson.h"
#include "QGVDrawItem.h"
#include "QGVLayerShape.h"
#include "QGVJsonTileParser.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

namespace  {
    const auto shapesKey            = "features";
}

QGVLayerGeoJson::QGVLayerGeoJson(QGVItem* parent, const QString& sourceFile) :
    QGVLayerFile(parent, sourceFile)
{
    mJsonParser = new QGVJsonTileParser();
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
        auto itemData = mJsonParser->createNewItemDataFromJsonFeature(shapeData);
        auto newShape = QGVLayerFile::createNewShape(getParent(), itemData);
        if (newShape != nullptr) {
            addShape(newShape);
        }
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
