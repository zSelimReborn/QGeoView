#ifndef GEOTIFF_H
#define GEOTIFF_H

#include "demoitem.h"

class QGVGeoTiffParser;

class GeoTiffDemo : public DemoItem
{
    Q_OBJECT
public:

    explicit GeoTiffDemo(QGVMap* geoMap, QObject* parent = 0);

    QString label() const override;

    QString comment() const override;
private:
    void onInit() override;

    void onStart() override;

    void onEnd() override;
private:
    QGVGeoTiffParser* mParser;
};

#endif // GEOTIFF_H
