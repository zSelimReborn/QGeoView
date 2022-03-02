#ifndef QGVVECTORTILE_H
#define QGVVECTORTILE_H

#include "QGVDrawItem.h"

#include <QList>

class QGV_LIB_DECL QGVVectorTile : public QGVDrawItem
{
public:
    QGVVectorTile(QGVItem*);
    QGVVectorTile(QGVItem*, const QList<QGVDrawItem*>&);

    void addItems(const QList<QGVDrawItem*>&);

protected:
    QPainterPath projShape() const override;
    void projPaint(QPainter* painter) override;
};

#endif // QGVVECTORTILE_H
