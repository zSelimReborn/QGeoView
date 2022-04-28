#ifndef QGVLAYERGEOJSON_H
#define QGVLAYERGEOJSON_H

#include "QGVLayerFile.h"

class QJsonDocument;
class QJsonValue;

class QGVJsonTileParser;

class QGV_LIB_DECL QGVLayerGeoJson : public QGVLayerFile
{
public:
    QGVLayerGeoJson(QGVItem*, const QString&);

protected:
    virtual void buildShapes() override;

private:
    QJsonDocument readFile();

private:
    QGVJsonTileParser* mJsonParser;
};

#endif // QGVLAYERGEOJSON_H
