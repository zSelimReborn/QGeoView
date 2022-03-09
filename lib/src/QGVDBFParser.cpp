#include "QGVDBFParser.h"

QGVDBFParser::QGVDBFParser() :
    mSourceFileName{},
    mSourceFileNameAsCharArray{},
    mFieldsCount{0}
{

}

QGVDBFParser::QGVDBFParser(const QString& sourceFile) :
    QGVDBFParser()
{
    setSourceFile(sourceFile);
}

QGVLayerItemData::Properties QGVDBFParser::parseProperties(const int& shapeId)
{
    QGVLayerItemData::Properties shapeProperties{};
    if (mHandle == nullptr) {
        return shapeProperties;
    }

    for (int i = 0; i < getFieldsCount(); ++i) {
        QGVDBFParser::ShapeProperty property{};
        const bool isValid = readField(shapeId, i, property);
        if (!isValid) {
            continue;
        }

        shapeProperties.insert(property.first, property.second);
    }

    return shapeProperties;
}

bool QGVDBFParser::readField(const int& shapeId, const int& fieldId, QGVDBFParser::ShapeProperty& property)
{
    if (DBFIsAttributeNULL(mHandle, shapeId, fieldId)) {
        return false;
    }

    char* fieldName = new char[getFieldLength()];
    const auto fieldType = DBFGetFieldInfo(mHandle, fieldId, fieldName, nullptr, nullptr);

    QVariant value{};

    switch (fieldType) {
    case DBFFieldType::FTDate:
    case DBFFieldType::FTDouble:
        value = DBFReadDoubleAttribute(mHandle, shapeId, fieldId);
        break;
    case DBFFieldType::FTInteger:
        value = DBFReadIntegerAttribute(mHandle, shapeId, fieldId);
        break;
    case DBFFieldType::FTLogical:
        value = DBFReadLogicalAttribute(mHandle, shapeId, fieldId);
        break;
    case DBFFieldType::FTString:
        value = DBFReadStringAttribute(mHandle, shapeId, fieldId);
        break;
    case DBFFieldType::FTInvalid:
        return false;
    }

    property.first = fieldName;
    property.second = value;
    return true;
}

void QGVDBFParser::setSourceFile(const QString& file)
{
    mSourceFileName = file;
    initializeSourceFileName();
    initializeHandle();
}

QString QGVDBFParser::getSourceFile() const
{
    return mSourceFileName;
}

void QGVDBFParser::initializeSourceFileName()
{
    mSourceFileNameAsCharArray = QGVLayerFile::stringToCharArr(getSourceFile());
}

void QGVDBFParser::initializeHandle()
{
    mHandle = DBFOpen(mSourceFileNameAsCharArray, "rb");
    if (mHandle == nullptr) {
        qDebug() << "[DBF Parser] Unable to read" << mSourceFileNameAsCharArray;
        return;
    }

    readFieldsCount();
}

void QGVDBFParser::readFieldsCount()
{
    mFieldsCount = DBFGetFieldCount(mHandle);
}

int QGVDBFParser::getFieldLength() const
{
    return 25;
}

void QGVDBFParser::close()
{
    if (mHandle) {
        DBFClose(mHandle);
    }
    mFieldsCount = 0;
}

int QGVDBFParser::getFieldsCount() const
{
    return mFieldsCount;
}
