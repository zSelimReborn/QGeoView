#ifndef QGVICON_H
#define QGVICON_H

#include "QGVImage.h"

/**
 * @brief The QGVIcon class places an icon on the map.
 * It inherits from the QGVImage, adding signals to allow the icon to move on the map.
 * Icon url, icon size and icon anchor can be customized.
 */
class QGV_LIB_DECL QGVIcon : public QGVImage
{
    Q_OBJECT

public:
    /**
     * @brief QGVIcon constructor.
     * Parameters: parent item, position on map (latitude, longitude), image url, image size, item flags (such as ItemFlag::Movable for movement)
     */
    QGVIcon(QGVItem*, const QGV::GeoPos&, const QString&, const QSize&, const QGV::ItemFlags&);

    /**
     * @brief QGVIcon constructor.
     * Parameters: parent item, position on map (latitude, longitude), image url, image size, image anchor, item flags (such as ItemFlag::Movable for movement)
     */
    QGVIcon(QGVItem*, const QGV::GeoPos&, const QString&, const QSize&, const QPoint&,const QGV::ItemFlags&);

    /**
     * @brief pos returns current position on map (latitude, longitude)
     * @return QGV::GeoPos
     */
    QGV::GeoPos pos();

    /**
     * @brief size returns the icon size
     * @return QSize
     */
    QSize size();

    /**
     * @brief anchor returns the icon anchor
     * @return QPoint
     */
    QPoint anchor();

    /**
     * @brief projOnObjectStartMove method inherited from QGVItem, it is called when the icon starts moving.
     * Parameters: point where the movement starts.
     */
    virtual void projOnObjectStartMove(const QPointF&) override;

    /**
     * @brief projOnObjectMovePos method inherited from QGVItem, it is called when the icon is moving.
     * Parameters: current icon position
     */
    virtual void projOnObjectMovePos(const QPointF&) override;

    /**
     * @brief projOnObjectStopMove method inherited from QGVItem, it is called when the icon stops moving.
     * Parameters: point where the movement stops.
     */
    virtual void projOnObjectStopMove(const QPointF&) override;

Q_SIGNALS:
    /**
     * @brief onStartMove signal triggered when the icon starts moving.
     * Parameters: point where the movement starts.
     */
    void onStartMove(const QPointF&);

    /**
     * @brief onMove signal triggered when the icon is moving.
     * Parameters: current icon position.
     */
    void onMove(const QPointF&);

    /**
     * @brief onStopMove signal triggered when the icon stops moving.
     * Parameters: point where the movement stops.
     */
    void onStopMove(const QPointF&);
private:
    /**
     * @brief mSize size of the icon
     */
    QSize mSize;

    /**
     * @brief mAnchor anchor of the icon
     */
    QPoint mAnchor;
};

#endif // QGVICON_H
