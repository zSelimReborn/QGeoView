#ifndef QGVLINE_H
#define QGVLINE_H

#include <QGeoView/QGVDrawItem.h>

class QGV_LIB_DECL QGVLine : public QGVDrawItem
{
    Q_OBJECT

public:
    explicit QGVLine(QGVItem*, const QGV::GeoPos&, const QGV::GeoPos&, const QColor&);

    QGV::GeoPos getGeoFirstPoint() const;
    QGV::GeoPos getGeoSecondPoint() const;
    QLineF line() const;
    QColor getColor() const;

private:
    void onProjection(QGVMap*) override;
    QPainterPath projShape() const override;
    void projPaint(QPainter*) override;
    QString projTooltip(const QPointF&) const override;

private:
    QGV::GeoPos mGeoFirstPoint;
    QGV::GeoPos mGeoSecondPoint;
    QLineF mLine;
    QRectF mRect;
    QColor mColor;
};


#endif // QGVLINE_H
