

#ifndef QGVGEOTIFFPARSER_H
#define QGVGEOTIFFPARSER_H

#include "QGVGlobal.h"

class QGVImage;

class QGV_LIB_DECL QGVGeoTiffParser
{
public:
    QGVGeoTiffParser();
    QGVImage* buildFromFile(const QString&);
    bool loadGeometryFromFile(const QString&, QGV::GeoRect&, const QString&);

public:
    void setDestSpatialRefName(const QString&);
    QString getDestSpatialRefName() const;
private:
    QString mDestSpatialRefName;
};

#endif // QGVGEOTIFFPARSER_H

