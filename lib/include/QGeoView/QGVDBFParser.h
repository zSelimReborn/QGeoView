#ifndef QGVDBFPARSER_H
#define QGVDBFPARSER_H

#include "QGVGlobal.h"
#include "QGVLayerFile.h"

#include "shapefil.h"

#include <QPair>

class QGV_LIB_DECL QGVDBFParser
{
public:
    using ShapeProperty = QPair<QGVLayerItemData::Properties::key_type, QGVLayerItemData::Properties::mapped_type>;

public:
    QGVDBFParser();
    QGVDBFParser(const QString&);

    QGVLayerItemData::Properties parseProperties(const int&);
    bool readField(const int&, const int&, ShapeProperty&);

    void setSourceFile(const QString&);
    QString getSourceFile() const;

    void close();

    int getFieldsCount() const;
private:
    void initializeSourceFileName();
    void initializeHandle();
    void readFieldsCount();

    int getFieldLength() const;

private:
    QString mSourceFileName;
    char* mSourceFileNameAsCharArray;

    DBFHandle mHandle;
    int mFieldsCount;
};

#endif // QGVDBFPARSER_H
