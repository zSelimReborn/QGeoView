#ifndef QGVBALLON_H
#define QGVBALLON_H

#include "QGVDrawItem.h"

/**
 * @brief The QGVBallon class places a ballon on the map.
 * It inherits from QGVDrawItem class.
 * It allows the customization of the text, background color, text color, text padding and extra margin.
 */
class QGV_LIB_DECL QGVBallon : public QGVDrawItem
{
    Q_OBJECT

public:
    /**
     * @brief QGVBallon constructor
     * Parameters: parent item, position on map (latitude, longitude), text inside the ballon
     */
    QGVBallon(QGVItem*, const QGV::GeoPos&, const QString&);

    // Baloon methods
    /**
     * @brief showBallon draws the ballon
     */
    void showBallon();

    /**
     * @brief hideBallon prevents drawing the ballon
     */
    void hideBallon();

    /**
     * @brief shouldShowBallon returns true if the ballon is drawn on the screen, false otherwise
     * @return
     */
    bool shouldShowBallon();

    /**
     * @brief setBallonText change the text inside the ballon.
     * Parameters: new text
     */
    void setBallonText(const QString&);

    /**
     * @brief getBallonText returns the current text inside the ballon
     * @return QString
     */
    QString getBallonText() const;

    /**
     * @brief setBallonBackground change the background color of the ballon.
     * Parameters: new background color
     */
    void setBallonBackground(const QColor&);

    /**
     * @brief getBallonBackground returns the current background color of the ballon
     * @return QColor
     */
    QColor getBallonBackground() const;

    /**
     * @brief setBallonTextColor change the text color of the ballon.
     * Parameters: new text color
     */
    void setBallonTextColor(const QColor&);

    /**
     * @brief getBallonTextColor returns the current text color of the ballon
     * @return QColor
     */
    QColor getBallonTextColor() const;

    /**
     * @brief setBallonTextPadding change the text padding of the ballon.
     * Parameters: new text padding
     */
    void setBallonTextPadding(const int&);

    /**
     * @brief getBallonTextPadding returns the text padding of the ballon
     * @return int
     */
    int getBallonTextPadding() const;

    /**
     * @brief setMarginBottom change the extra margin bottom of the ballon.
     * Parameters: new margin bottom
     */
    void setMarginBottom(const int&);

    /**
     * @brief getMarginBottom returns the current extra margin bottom of the ballon
     * @return int
     */
    int getMarginBottom() const;

    // Draw item methods
    /**
     * @brief move allows the movement of the ballon to a new point (latitude, longitude)
     * Parameters: new point of the ballon
     */
    void move(const QGV::GeoPos&);

protected:
    // Draw item life cycle
    /**
     * @brief onProjection inherited from QGVDrawItem, it's called when the map has a new projection (also on start).
     */
    void onProjection(QGVMap* geoMap) override;

    /**
     * @brief projShape returns the rect containing the ballon.
     * @return QPainterPath
     */
    QPainterPath projShape() const override;

    /**
     * @brief projAnchor returns ballon anchor
     * @return
     */
    QPointF projAnchor() const override;

    /**
     * @brief projPaint it's called every frame for drawing the ballon on the screen.
     */
    void projPaint(QPainter* painter) override;

private:
    // Draw item settings
    /**
     * @brief mGeoPos current ballon position on the map
     */
    QGV::GeoPos mGeoPos;

    /**
     * @brief mProjRect rect shape containing the ballon (for drawing)
     */
    QRectF mProjRect;

    /**
     * @brief mProjAnchor ballon anchor
     */
    QPointF mProjAnchor;

    // Ballon settings
    /**
     * @brief mBallonText current ballon text
     */
    QString mBallonText;

    /**
     * @brief bShouldShowBallon true if the ballon has to be shown, false otherwise
     */
    bool bShouldShowBallon;

    /**
     * @brief mBallonBackground current ballon background
     */
    QColor mBallonBackground;

    /**
     * @brief mBallonTextColor current ballon text color
     */
    QColor mBallonTextColor;

    /**
     * @brief mBallonTextPadding current ballon text padding
     */
    int mBallonTextPadding;

    /**
     * @brief mMarginBottom extra margin bottom
     */
    int mMarginBottom;
};

#endif // QGVBALLON_H
