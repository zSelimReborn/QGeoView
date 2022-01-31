#ifndef QGVLAYERGEOJSON_H
#define QGVLAYERGEOJSON_H

#include "QGVLayerFile.h"

class QJsonDocument;
class QJsonValue;

class QGV_LIB_DECL QGVLayerGeoJson : public QGVLayerFile
{
public:
    QGVLayerGeoJson(QGVItem*, const QString&);

protected:
    virtual void buildShapes() override;

private:
    QJsonDocument readFile();
    QGVLayerItemData createNewItemDataFromJsonFeature(const QJsonValue&);
};

#endif // QGVLAYERGEOJSON_H
