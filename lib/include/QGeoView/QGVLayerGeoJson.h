#ifndef QGVLAYERGEOJSON_H
#define QGVLAYERGEOJSON_H

#include "QGVLayerFile.h"

class QJsonDocument;
class QJsonValue;

class QGV_LIB_DECL QGVLayerGeoJson : public QGVLayerFile
{
public:
    QGVLayerGeoJson(QGVItem*, const QString&);

    QGVLayerShapeType getShapeTypeFromString(const QString&);

protected:
    virtual void buildShapes() override;

private:
    void initializeMappingShapeTypes();
    QJsonDocument readFile();
    QGVLayerItemData createNewItemDataFromJsonFeature(const QJsonValue&);

private:
    QMap<QString, QGVLayerShapeType> mMappingShapeTypes;
};

#endif // QGVLAYERGEOJSON_H
