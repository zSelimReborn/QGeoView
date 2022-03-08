#ifndef QGVTILEPARSER_H
#define QGVTILEPARSER_H

#include "QGVGlobal.h"

#include <QColor>
#include <QList>

class QGVDrawItem;

class QGV_LIB_DECL QGVTileParser
{
public:
    QGVTileParser();

    void setPointsIcon(const QString&);
    QString getPointsIcon() const;

    void setLinesColor(const QColor&);
    QColor getLinesColor() const;

    void setPolygonsColor(const QColor&);
    QColor getPolygonsColor() const;

public:
    virtual QList<QGVDrawItem*> buildFromFile(const QGV::GeoTilePos&, const QString&, const QString&) = 0;
    virtual QList<QGVDrawItem*> buildFromContent(const QGV::GeoTilePos&, const QByteArray&, const QString&) = 0;
    static QGV::GeoPos toLatLong(const QGV::GeoTilePos&, const QPoint&, const quint32&);

private:
    QString mPointsIcon;
    QColor mLinesColor;
    QColor mPolygonsColor;
};

#endif // QGVTILEPARSER_H
