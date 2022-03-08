#include "QGVTileParser.h"

#include <QtMath>

QGVTileParser::QGVTileParser() :
    mPointsIcon{":/resources/pin-icon.png"},
    mLinesColor{Qt::black},
    mPolygonsColor{Qt::black}
{

}

void QGVTileParser::setPointsIcon(const QString& icon)
{
    mPointsIcon = icon;
}

QString QGVTileParser::getPointsIcon() const
{
    return mPointsIcon;
}

void QGVTileParser::setLinesColor(const QColor& color)
{
    mLinesColor = color;
}

QColor QGVTileParser::getLinesColor() const
{
    return mLinesColor;
}

void QGVTileParser::setPolygonsColor(const QColor& color)
{
    mPolygonsColor = color;
}

QColor QGVTileParser::getPolygonsColor() const
{
    return mPolygonsColor;
}

QGV::GeoPos QGVTileParser::toLatLong(const QGV::GeoTilePos& tile, const QPoint& point, const quint32& extent)
{
    double size = (double)extent * qPow(2, (double)tile.zoom());
    double x0 = (double)extent * (double)tile.pos().x();
    double y0 = (double)extent * (double)tile.pos().y();

    double dblY = (double)point.y();
    double dblX = (double) point.x();

    double y2 = 180 - (dblY + y0) * 360 / size;
    double lng = (dblX + x0) * 360 / size - 180;
    double lat = 360 / M_PI * qAtan(qExp(y2 * M_PI / 180)) - 90;

    return QGV::GeoPos{lat, lng};
}
