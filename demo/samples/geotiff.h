#ifdef USE_GDAL_FEATURES

#ifndef GEOTIFF_H
#define GEOTIFF_H

#include "demoitem.h"

class QGVRasterLayer;
class QGVLayer;

class GeoTiffDemo : public DemoItem
{
    Q_OBJECT
public:

    explicit GeoTiffDemo(QGVMap* geoMap, QObject* parent = 0);

    QString label() const override;

    QString comment() const override;

    void setSelected(QGVLayer* layer, bool selected);
private:
    void onInit() override;

    void onStart() override;

    void onEnd() override;
private:
    QGVRasterLayer* mLayer;
};

#endif // GEOTIFF_H
#endif // USE_GDAL_FEATURES
