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

    void setWidth(const quint16&);
    quint16 getWidth() const;

    void showLine();
    void hideLine();
    bool shouldShowLine();

    void move(const QGV::GeoPos&, const QGV::GeoPos&);

private:
    void onProjection(QGVMap*) override;
    QPainterPath projShape() const override;
    void projPaint(QPainter*) override;
    QPointF projAnchor() const override;
    QString projTooltip(const QPointF&) const override;
    QTransform projTransform() const override;

private:
    // Geo settings
    QGV::GeoPos mGeoFirstPoint;
    QGV::GeoPos mGeoSecondPoint;
    QGV::GeoRect mGeoRect;

    // Draw settings
    QLineF mLine;
    QRectF mRect;
    QColor mColor;
    quint16 mWidth;
    bool bShow;
};


#endif // QGVLINE_H
