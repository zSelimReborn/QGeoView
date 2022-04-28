#ifndef QGVJSONTILEPARSER_H
#define QGVJSONTILEPARSER_H

#include "QGVTileParser.h"
#include "QGVLayerShape.h"

#include <QMap>

class QGV_LIB_DECL QGVJsonTileParser : public QGVTileParser
{
public:
    QGVJsonTileParser();
    QList<QGVDrawItem*> buildFromFile(const QGV::GeoTilePos&, const QString&, const QString&) override;
    QList<QGVDrawItem*> buildFromContent(const QGV::GeoTilePos&, const QByteArray&, const QString&) override;
    QGVLayerItemData createNewItemDataFromJsonFeature(const QJsonValue&);

    QGVLayerShapeType getShapeTypeFromString(const QString&);
protected:
    QByteArray readFile(const QString&fileName);
    void convertInGeoCoordinates(const QGV::GeoTilePos&, QGVLayerItemData&, const quint32&);

private:
    void initializeMappingShapeTypes();

private:
    QMap<QString, QGVLayerShapeType> mMappingShapeTypes;
};

#endif // QGVJSONTILEPARSER_H
