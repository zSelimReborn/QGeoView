#include "QGVVectorTile.h"

QGVVectorTile::QGVVectorTile(QGVItem* parent)
{
    setParent(parent);
}

QGVVectorTile::QGVVectorTile(QGVItem* parent, const QList<QGVDrawItem*>& items)
{
    setParent(parent);
    addItems(items);
}

void QGVVectorTile::addItems(const QList<QGVDrawItem *>& items)
{
    for (const auto& item : qAsConst(items)) {
        addItem(item);
    }
}

QPainterPath QGVVectorTile::projShape() const
{
    return QPainterPath{};
}

void QGVVectorTile::projPaint(QPainter* painter)
{
    qt_noop();
}
