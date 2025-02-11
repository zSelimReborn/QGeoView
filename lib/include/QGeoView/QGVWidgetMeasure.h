#ifndef QGVWIDGETMEASURE_H
#define QGVWIDGETMEASURE_H

#include "QGVWidget.h"
#include "utils/DistanceUnits.hpp"

class QGVIcon;
class QGVBallon;
class QGVLine;
class QToolButton;

/**
 * @brief The QGVWidgetMeasure class is a widget which places two pins (connected by a line) with two ballons above them.
 * Every pins can be moved on the map and the distance and the bearing between the two pins is shown on the ballon above.
 */
class QGV_LIB_DECL QGVWidgetMeasure : public QGVWidget
{
public:
    /**
     * @brief QGVWidgetMeasure default constructor. Defines default values for every attribute.
     */
    QGVWidgetMeasure();

    /**
     * @brief QGVWidgetMeasure constructor. Defines a custom unit for distances and accuracy.
     */
    QGVWidgetMeasure(const DistanceUnits&, const quint8&);

    /**
     * @brief QGVWidgetMeasure constructor. Defines unit for distances, accuracy, pin image, pin size, pin anchor.
     */
    QGVWidgetMeasure(
            const DistanceUnits&,
            const quint8&,
            const QString&,
            const QSize&,
            const QPoint&
    );

    /**
     * @brief setUnit change distance unit.
     * Parameters: new unit
     */
    void setUnit(const DistanceUnits&);

    /**
     * @brief getUnit returns the unit used for distance
     * @return enum DistanceUnits
     */
    DistanceUnits getUnit();

    /**
     * @brief setAccuracy change accuracy for distance.
     * Parameters: new accuracy
     */
    void setAccuracy(const quint8&);

    /**
     * @brief getAccuracy returns the accuracy for distance.
     * @return  quint8
     */
    quint8 getAccuracy();

    /**
     * @brief setIconPin change pin icon.
     * Parameters: new image url
     */
    void setIconPin(const QString&);

    /**
     * @brief getIconPin returns current pin icon
     * @return QString
     */
    QString getIconPin();

    /**
     * @brief setIconPinMovement change pin icon during movement.
     * Parameters: new image url
     */
    void setIconPinMovement(const QString&);

    /**
     * @brief getIconPinMovement returns current pin icon used during movement
     * @return QString
     */
    QString getIconPinMovement();

    /**
     * @brief setIconSize change pin icon size.
     * Parameters: new icon size
     */
    void setIconSize(const QSize&);

    /**
     * @brief getIconSize returns current icon size
     * @return QSize
     */
    QSize getIconSize();

    /**
     * @brief setIconAnchor change pin icon anchor.
     * Parameters: new icon anchor
     */
    void setIconAnchor(const QPoint&);

    /**
     * @brief getIconAnchor returns current pin icon anchor
     * @return QPoint
     */
    QPoint getIconAnchor();

    /**
     * @brief setLeftPinStartingPoint change starting position of left pin (latitude, longitude).
     * Parameters: new position
     */
    void setLeftPinStartingPoint(const QGV::GeoPos&);

    /**
     * @brief getLeftPinStartingPoint returns starting position of left pin (latitude, longitude)
     * @return QGV::GeoPos
     */
    QGV::GeoPos getLeftPinStartingPoint();

    /**
     * @brief setRightPinStartingPoint change starting position of right pin (latitude, longitude).
     * Parameters: new position
     */
    void setRightPinStartingPoint(const QGV::GeoPos&);

    /**
     * @brief getRightPinStartingPoint returns starting position of right pin (latitude, longitude).
     * @return QGV::GeoPos
     */
    QGV::GeoPos getRightPinStartingPoint();

    void setPinStartingPointMetersOffset(const qreal&);
    qreal getPinStartingPointMetersOffset();

    void setLeftPinAzimuthOffset(const qreal&);
    qreal getLeftPinAzimuthOffset();

    void setRightPinAzimuthOffset(const qreal&);
    qreal getRightPinAzimuthOffset();

    /**
     * @brief setDistanceLabelPrefix change distance label prefix.
     * Parameters: new prefix
     */
    void setDistanceLabelPrefix(const QString&);

    /**
     * @brief getDistanceLabelPrefix returns the current prefix for distance label
     * @return QString
     */
    QString getDistanceLabelPrefix();

    /**
     * @brief setBearingLabelPrefix change bearing label prefix.
     * Parameters: new prefix
     */
    void setBearingLabelPrefix(const QString&);

    /**
     * @brief getBearingLabelPrefix returns the current prefix for bearing label
     * @return QString
     */
    QString getBearingLabelPrefix();

    /**
     * @brief setBallonValueSeparator change separator between distance and bearing label.
     * Parameters: new separator
     */
    void setBallonValueSeparator(const QString&);

    /**
     * @brief getBallonValueSeparator returns current separator between distance and bearing label
     * @return QString
     */
    QString getBallonValueSeparator();

    /**
     * @brief setBallonBackgroundColor change ballon background color.
     * Parameters: new ballon background color
     */
    void setBallonBackgroundColor(const QColor&);

    /**
     * @brief getBallonBackgroundColor returns the current ballon background color
     * @return QColor
     */
    QColor getBallonBackgroundColor();

    /**
     * @brief setBallonTextColor change ballon text color.
     * Parameters: new ballon text color
     */
    void setBallonTextColor(const QColor&);

    /**
     * @brief getBallonTextColor returns the current ballon text color.
     * @return QColor
     */
    QColor getBallonTextColor();

    /**
     * @brief setBallonTextPadding change ballon text padding.
     * Parameters: new ballon text padding
     */
    void setBallonTextPadding(const int&);

    /**
     * @brief getBallonTextPadding returns the current ballon text padding
     * @return int
     */
    int getBallonTextPadding();

    /**
     * @brief setLineColor change the current line color.
     * Parameters: new line color
     */
    void setLineColor(const QColor&);

    /**
     * @brief getLineColor returns current line color
     * @return QColor
     */
    QColor getLineColor();

    /**
     * @brief setLineWidth change the current line width.
     * Parameters: new line width
     */
    void setLineWidth(const quint16&);

    /**
     * @brief getLineWidth returns the current line width
     * @return quint16
     */
    quint16 getLineWidth();

    /**
     * @brief showPinLine draws the line between the two pins
     */
    void showPinLine();

    /**
     * @brief hidePinLine prevent drawing the line between the two pins
     */
    void hidePinLine();

    /**
     * @brief shouldShowPinLine returns true if the line has to be shown, false otherwise
     * @return bool
     */
    bool shouldShowPinLine();    

    void setWidgetAnchorEdges(const QSet<Qt::Edge>&);

    QSet<Qt::Edge> getWidgetAnchorEdges();

    /**
     * @brief setWidgetBtnIcon change btn icon.
     */
    void setWidgetBtnIcon(const QString&);

    /**
     * @brief getWidgetBtnIcon get btn icon url
     * @return QString
     */
    QString getWidgetBtnIcon();

    /**
     * @brief setWidgetBtnSize change main btn size
     */
    void setWidgetBtnSize(const QSize&);

    /**
     * @brief getWidgetBtnSize returns main btn size
     * @return QSize
     */
    QSize getWidgetBtnSize();

    void setBtnExternalRectColor(const QColor&);
    void setBtnExternalBorderColor(const QColor&);
    void setBtnInternalRectColor(const QColor&);
    void setBtnActiveInternalRectColor(const QColor&);

    QColor getBtnExternalRectColor();
    QColor getBtnExternalBorderColor();
    QColor getBtnInternalRectColor();
    QColor getBtnActiveInternalRectColor();

    /**
     * @brief activateWidget method for placing items (pins, line and ballons) on map
     */
    void activateWidget();

    /**
     * @brief deactivateWidget method for removing items (pins, line and ballons) from map
     */
    void deactivateWidget();

    /**
     * @brief isActive returns true when widget is active, false otherwise
     * @return bool
     */
    bool isActive();

private:
    /**
     * @brief createNewPin factory method which creates a pin in a certain position with all the configuration needed.
     * Parameters: starting position of the pin.
     * @return QGVIcon*
     */
    QGVIcon* createNewPin(const QGV::GeoPos&);

    /**
     * @brief createNewBallon factory method which create a ballon in a certain position with all the configuration needed.
     * Parameters: starting position of the ballon.
     * @return QGVBallon*
     */
    QGVBallon* createNewBallon(const QGV::GeoPos&);

    /**
     * @brief getDistanceLabel returns the correct distance label to show in a ballon with the given meters. It also converts to other units if needed.
     * @return QString
     */
    QString getDistanceLabel(const qreal&);

    /**
     * @brief getBearingLabel returns the correct bearing label to show in a ballon with the given degrees.
     * @return QString
     */
    QString getBearingLabel(const qreal&);

    /**
     * @brief onPinMove method triggered when a pin is moving on the map.
     * Parameters: current position of the pin on the scene
     */
    void onPinMove(const QPointF&);

    /**
     * @brief onLeftPinStartMove method triggered when the left pin starts moving.
     * Parameters: current position of the left pin on the scene
     */
    void onLeftPinStartMove(const QPointF&);

    /**
     * @brief onRightPinStartMove method triggered when the right pin starts moving.
     * Parameters: current position of the right pin on the scene
     */
    void onRightPinStartMove(const QPointF&);

    /**
     * @brief updateBallons change text in the ballons according to new distance and bearings.
     */
    void updateBallons(const qreal&, const qreal&, const qreal&);

    /**
     * @brief moveBallons helper methods which move the ballons according to pin position.
     */
    void moveBallons();

    /**
     * @brief moveLine helper methods which move the line between the two pins for the new positions.
     */
    void moveLine();

    /**
     * @brief initializePinLine initialize line between pins with all the configuration needed.
     */
    void initializePinLine();

    /**
     * @brief onWidgetBtnClick method triggered when btn is clicked. It activates or deactivates the widget
     */
    void onWidgetBtnClick();

    /**
     * @brief addPinToMap method which add the two pins on the map, the line between them and the ballons.
     * It also initializes the listeners for calculating the distance and the bearing. Call this after adding widget on the map.
     */
    void addPinToMap();

    /**
     * @brief removePinFromMap method which remove the two pins, line and ballons from the map.
     */
    void removePinFromMap();

    /**
     * @brief initializeLayout method which create main widget layout
     */
    void initializeLayout();

    /**
     * @brief initializeWidgetButton method which create main widget button and adds it to layout
     */
    void initializeWidgetButton();

    /**
     * @brief refreshButton method which change button icon and size
     */
    void refreshWidgetButton();

    /**
     * @brief calculateMiddlePosition returns current middle geo position based on camera location adding an offset (meters) and bearing (degrees) passed.
     * @return QGV::GeoPos
     */
    QGV::GeoPos calculateMiddlePosition(const qreal&, const qreal&);

    /**
     * @brief paintEvent called every frame
     */
    void paintEvent(QPaintEvent* event) override;

private:
    // Widget functionality
    /**
     * @brief leftPin first pin
     */
    QGVIcon* leftPin;

    /**
     * @brief rightPin second pin
     */
    QGVIcon* rightPin;

    /**
     * @brief mUnit distance unit
     */
    DistanceUnits mUnit;

    /**
     * @brief mAccuracy distance accuracy
     */
    quint8 mAccuracy;

    /**
     * @brief leftBallon first ballon connected to the first pin
     */
    QGVBallon* leftBallon;

    /**
     * @brief rightBallon second ballon connected to the second pin
     */
    QGVBallon* rightBallon;

    /**
     * @brief bIsActive true when widget is active (pin, line and ballons on map), false otherwise (no items on map)
     */
    bool bIsActive;

    // Pin settings
    /**
     * @brief mIconPin image url for the pins
     */
    QString mIconPin;

    /**
     * @brief mIconPinMovement image url for the pins during movement
     */
    QString mIconPinMovement;

    /**
     * @brief mIconSize pins size
     */
    QSize mIconSize;

    /**
     * @brief mIconAnchor pins anchor
     */
    QPoint mIconAnchor;

    /**
     * @brief mLeftPinStartingPoint first pin starting point (latitude, longitude)
     */
    QGV::GeoPos mLeftPinStartingPoint;

    /**
     * @brief mRightPinStartingPoint second pin starting point (latitude, longitude)
     */
    QGV::GeoPos mRightPinStartingPoint;

    qreal mPinStartingPointMetersOffset;

    qreal mLeftPinAzimuthOffset;
    qreal mRightPinAzimuthOffset;

    // Ballon settings
    /**
     * @brief mDistanceLabelPrefix prefix for distance label
     */
    QString mDistanceLabelPrefix;

    /**
     * @brief mBearingLabelPrefix prefix for bearing label
     */
    QString mBearingLabelPrefix;

    /**
     * @brief mBallonValueSeparator separator between distance and bearing labels
     */
    QString mBallonValueSeparator;

    /**
     * @brief mBallonBackgroundColor ballons background color
     */
    QColor mBallonBackgroundColor;

    /**
     * @brief mBallonTextColor ballons text color
     */
    QColor mBallonTextColor;

    /**
     * @brief mBallonTextPadding ballons text padding
     */
    int mBallonTextPadding;

    // Line settings
    /**
     * @brief mPinLine line between the two pins
     */
    QGVLine* mPinLine;

    /**
     * @brief mLineColor line color
     */
    QColor mLineColor;

    /**
     * @brief mLineWidth line width
     */
    quint16 mLineWidth;

    // Widget drawing settings

    /**
     * @brief mWidgetAnchorEdges anchor edges for widget
     */
    QSet<Qt::Edge> mWidgetAnchorEdges;

    /**
     * @brief mWidgetActivateBtn main switch button which activate or deactivate the widget
     */
    QToolButton* mWidgetActivateBtn;

    /**
     * @brief mWidgetBtnIcon icon url inside main button
     */
    QString mWidgetBtnIcon;

    /**
     * @brief mWidgetBtnSize icon size inside main button
     */
    QSize mWidgetBtnSize;

    /**
     * @brief mBtnExternalRectColor color of external rect around main button
     */
    QColor mBtnExternalRectColor;

    /**
     * @brief mBtnExternalRectBorderColor color of external border around main button
     */
    QColor mBtnExternalRectBorderColor;

    /**
     * @brief mBtnInternalRectColor default color of internal rect around main button
     */
    QColor mBtnInternalRectColor;

    /**
     * @brief mBtnActiveInternalRectColor active color of internal rect around main button
     */
    QColor mBtnActiveInternalRectColor;
};

#endif // QGVWIDGETMEASURE_H
