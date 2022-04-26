#ifdef USE_GDAL_FEATURES

#ifndef QGVRASTERLAYER_H
#define QGVRASTERLAYER_H

#include "QGVLayerFile.h"

class QGVGeoTiffParser;

class QGV_LIB_DECL QGVRasterLayer : public QGVLayerFile
{
public:
    QGVRasterLayer(QGVItem*, const QString&);
protected:
    void buildShapes() override;
private:
    QGVGeoTiffParser* mParser;
};

#endif // QGVRASTERLAYER_H
#endif // USE_GDAL_FEATURES
