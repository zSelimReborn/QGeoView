#ifndef QGVICON_H
#define QGVICON_H

#include "QGVImage.h"

/**
 * @brief The QGVIcon class
 */
class QGV_LIB_DECL QGVIcon : public QGVImage
{
    Q_OBJECT

public:
    QGVIcon(QGVItem*, const QGV::GeoPos&, const QString&, const QSize&, const QGV::ItemFlags&);
    QGV::GeoPos pos();

    QSize size();
    QPoint anchor();

    virtual void projOnObjectStartMove(const QPointF&) override;
    virtual void projOnObjectMovePos(const QPointF&) override;
    virtual void projOnObjectStopMove(const QPointF&) override;

Q_SIGNALS:
    void onStartMove(const QPointF&);
    void onMove(const QPointF&);
    void onStopMove(const QPointF&);
private:
    QSize mSize;
    QPoint mAnchor;
};

#endif // QGVICON_H
