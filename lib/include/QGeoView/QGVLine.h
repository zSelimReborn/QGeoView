#ifndef QGVLINE_H
#define QGVLINE_H

#include <QGeoView/QGVDrawItem.h>

/**
 * @brief The QGVLine class places a line between two points (latitude, longitude) on the map.
 * It inherits from the QGVDrawItem.
 * It allows the customization of color and width of the line.
 */
class QGV_LIB_DECL QGVLine : public QGVDrawItem
{
    Q_OBJECT

public:
    /**
     * @brief QGVLine constructor
     * Parameters: parent item, two endpoints (latitude, longitude) to draw the line, color
     */
    explicit QGVLine(QGVItem*, const QGV::GeoPos&, const QGV::GeoPos&, const QColor&);

    /**
     * @brief getGeoFirstPoint returns the first endpoint of the line
     * @return QGV::GeoPos
     */
    QGV::GeoPos getGeoFirstPoint() const;

    /**
     * @brief getGeoSecondPoint returns the second endpoint of the line
     * @return QGV::GeoPos
     */
    QGV::GeoPos getGeoSecondPoint() const;

    /**
     * @brief line returns the QLineF object representing the line.
     * @return QLineF
     */
    QLineF line() const;

    /**
     * @brief getColor returns the color of the line
     * @return QColor
     */
    QColor getColor() const;

    /**
     * @brief setWidth setter for line width.
     * Parameter: new line widht
     */
    void setWidth(const quint16&);

    /**
     * @brief getWidth returns the line width
     * @return quint18
     */
    quint16 getWidth() const;

    /**
     * @brief showLine draws the line
     */
    void showLine();

    /**
     * @brief hideLine prevents drawing the line
     */
    void hideLine();

    /**
     * @brief shouldShowLine returns true if the line is drawn on the screen, false otherwise
     * @return bool
     */
    bool shouldShowLine();

    /**
     * @brief move allows the movement of the line between two new endpoints.
     * Parameters: two new endpoints (latitude, longitude)
     */
    void move(const QGV::GeoPos&, const QGV::GeoPos&);

private:
    /**
     * @brief onProjection inherited from QGVDrawItem, it's called when the map has a new projection (also on start).
     */
    void onProjection(QGVMap*) override;

    /**
     * @brief projShape returns the rect containing the line.
     * @return QPainterPath
     */
    QPainterPath projShape() const override;

    /**
     * @brief projPaint it's called every frame for drawing the line on the screen.
     */
    void projPaint(QPainter*) override;

    /**
     * @brief projAnchor returns line anchor
     * @return QPointF
     */
    QPointF projAnchor() const override;

    /**
     * @brief projTooltip returns a message to show as a tooltip.
     * @return QString
     */
    QString projTooltip(const QPointF&) const override;
    QTransform projTransform() const override;

private:
    // Geo settings
    /**
     * @brief mGeoFirstPoint first endpoint of the line
     */
    QGV::GeoPos mGeoFirstPoint;

    /**
     * @brief mGeoSecondPoint second endpoint of the line
     */
    QGV::GeoPos mGeoSecondPoint;

    /**
     * @brief mGeoRect rect containing the line (geo coordinate)
     */
    QGV::GeoRect mGeoRect;

    // Draw settings
    /**
     * @brief mLine line object (scene coordinate)
     */
    QLineF mLine;

    /**
     * @brief mRect rect containing the line (scene coordinate)
     */
    QRectF mRect;

    /**
     * @brief mColor color of the line
     */
    QColor mColor;

    /**
     * @brief mWidth width of the line
     */
    quint16 mWidth;

    /**
     * @brief bShow true if the line has to be shown, false otherwise
     */
    bool bShow;
};


#endif // QGVLINE_H
