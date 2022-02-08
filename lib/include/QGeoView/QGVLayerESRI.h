#ifndef QGVLAYERESRI_H
#define QGVLAYERESRI_H

#include "QGVLayerFile.h"

class QGV_LIB_DECL QGVLayerESRI : public QGVLayerFile
{
public:
    QGVLayerESRI(QGVItem*, const QString&);

    QGVLayerShapeType getShapeTypeFromNumber(const quint8&);
    char* getSourceFileNameAsCharArray();

protected:
    virtual void buildShapes() override;

private:
    void initializeMappingShapeTypes();
    void initializeSourceFileAsCharArray();

private:
    QMap<quint8, QGVLayerShapeType> mMappingShapeTypes;
    char* mSourceFileNameAsCharArray;
};

#endif // QGVLAYERESRI_H
