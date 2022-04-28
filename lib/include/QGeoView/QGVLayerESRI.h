#ifndef QGVLAYERESRI_H
#define QGVLAYERESRI_H

#include "QGVLayerFile.h"

class QGVDBFParser;

class QGV_LIB_DECL QGVLayerESRI : public QGVLayerFile
{
public:
    QGVLayerESRI(QGVItem*, const QString&);
    QGVLayerESRI(QGVItem*, const QString&, const QString&);

    QGVLayerShapeType getShapeTypeFromNumber(const quint8&);
    char* getSourceFileNameAsCharArray();

    QString getDbfSourceFile() const;
    void setSourceFileName(const QString&);

protected:
    virtual void buildShapes() override;

private:
    void initializeMappingShapeTypes();
    void initializeSourceFileAsCharArray();
    void initializeDbfParser();
    void closeDbfParser();

private:
    QMap<quint8, QGVLayerShapeType> mMappingShapeTypes;
    char* mSourceFileNameAsCharArray;

    QGVDBFParser* mDbfParser;
    QString mDbfSourceFile;
};

#endif // QGVLAYERESRI_H
