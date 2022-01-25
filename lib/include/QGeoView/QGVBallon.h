#ifndef QGVBALLON_H
#define QGVBALLON_H

#include "QGVDrawItem.h"

class QGV_LIB_DECL QGVBallon : public QGVDrawItem
{
    Q_OBJECT

public:
    QGVBallon(QGVItem*, const QGV::GeoPos&, const QString&);

    // Baloon methods
    void showBallon();
    void hideBallon();
    bool shouldShowBallon();

    void setBallonText(const QString&);
    QString getBallonText() const;

    void setBallonBackground(const QColor&);
    QColor getBallonBackground() const;

    void setBallonTextColor(const QColor&);
    QColor getBallonTextColor() const;

    void setBallonTextPadding(const int&);
    int getBallonTextPadding() const;

    void setMarginBottom(const int&);
    int getMarginBottom() const;

    // Draw item methods
    void move(const QGV::GeoPos&);

protected:
    // Draw item life cycle
    void onProjection(QGVMap* geoMap) override;
    QPainterPath projShape() const override;
    QPointF projAnchor() const override;
    void projPaint(QPainter* painter) override;

private:
    // Draw item settings
    QGV::GeoPos mGeoPos;
    QRectF mProjRect;
    QPointF mProjAnchor;
    int mMarginBottom;

    // Ballon settings
    QString mBallonText;
    bool bShouldShowBallon;
    QColor mBallonBackground;
    QColor mBallonTextColor;
    int mBallonTextPadding;
};

#endif // QGVBALLON_H
