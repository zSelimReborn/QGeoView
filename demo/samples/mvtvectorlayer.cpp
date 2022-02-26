#include "mvtvectorlayer.h"

#include "QGeoView/MVTUtils.h"

#include <QTemporaryDir>

MVTVectorLayerDemo::MVTVectorLayerDemo(QGVMap* geoMap, QObject* parent)
    : DemoItem(geoMap, SelectorDialog::Multi, parent)
{}

QString MVTVectorLayerDemo::label() const
{
    return "Vectorial Layers Online";
}

QString MVTVectorLayerDemo::comment() const
{
    return "QGV now can request vectorial layers online. This includes:<br>"
           "- MVT format<br>"
           "- PBF format<br>";
}

void MVTVectorLayerDemo::onInit()
{

    QTemporaryDir tempDir;
    const QString mvtFile = ":/resources/test2048.mvt";
    const QString mvtTempFile = tempDir.path() + "/shapes.mvt";

    if (tempDir.isValid()) {
        if (QFile::copy(mvtFile, mvtTempFile)) {
            try {
                const QGV::GeoTilePos tile{1, QPoint(0, 0)};
                const auto shapes = MVTUtils::buildFromFile(tile, mvtTempFile);
                qDebug() << "Created" << shapes.size() << "shapes";
            }  catch (const std::exception& exception) {
                qDebug() << "[MVT] ERROR READING FILE:" << exception.what();
            }
        }
    }

    selector()->selectAll();
}

void MVTVectorLayerDemo::onStart()
{
    selector()->show();
}

void MVTVectorLayerDemo::onEnd()
{
    selector()->hide();
}
