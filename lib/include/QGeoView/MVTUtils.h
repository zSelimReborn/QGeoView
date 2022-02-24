#ifndef QGEOVIEW_MVTUTILS_H
#define QGEOVIEW_MVTUTILS_H

#include "QGVGlobal.h"

#include <QList>

class QGVDrawItem;

class QGV_LIB_DECL MVTUtils
{
public:
    static QList<QGVDrawItem*> buildFromFile(const QGV::GeoTilePos&, const QString&);
    static QList<QGVDrawItem*> buildFromContent(const QGV::GeoTilePos&, const std::string&);
    static QGV::GeoPos toLatLong(const QGV::GeoTilePos&, const QPoint&, const std::int32_t&);

private:
    static std::string readFile(const QString&);
    static QList<QGVDrawItem*> buildShapes(const QGV::GeoTilePos&, const std::string&);
};

#endif // QGEOVIEW_MVTUTILS_H
