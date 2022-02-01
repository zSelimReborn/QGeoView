#ifndef QGVLAYERSHAPE_H
#define QGVLAYERSHAPE_H

#include "QGVGlobal.h"
#include "QGVLayerFile.h"
#include "QGVDrawItem.h"

class QGV_LIB_DECL QGVLayerShape
{
public:
    QGVLayerShape(const QGVLayerItemData&);

    QGVLayerItemData getShapeData();
    QVariant getProperty(const QString&);
    QGVLayerItemData::GeoCoordinates getCoordinates();
    QGVLayerShapeType getType();

private:
    QGVLayerItemData mShapeData;
};

#endif // QGVLAYERSHAPE_H
