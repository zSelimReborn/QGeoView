#ifndef QGVSHAPEICON_H
#define QGVSHAPEICON_H

#include "QGVLayerFile.h"
#include "QGVLayerShape.h"
#include "QGVIcon.h"

class QGV_LIB_DECL QGVShapeIcon : public QGVIcon, public QGVLayerShape
{
public:
    QGVShapeIcon(QGVItem*, const QGVLayerItemData&, const QString&);
};

#endif // QGVSHAPEICON_H
