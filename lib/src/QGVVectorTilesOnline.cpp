#include "QGVVectorTilesOnline.h"

#include "QGVDrawItem.h"

QGVVectorTilesOnline::QGVVectorTilesOnline() :
    bHasApiKey{false},
    mApiKey{""}
{

}

QGVVectorTilesOnline::QGVVectorTilesOnline(const QString& apiKey) :
    QGVVectorTilesOnline()
{
    setApiKey(apiKey);
}

void QGVVectorTilesOnline::onReplyFinished(QNetworkReply *reply)
{
    const auto tileRequest = reply->property("TILE_REQUEST").toBool();
    if (!tileRequest) {
        return;
    }
    const auto tileOwner = reply->property("TILE_OWNER").value<QGVLayerTilesOnline*>();
    if (tileOwner != this) {
        return;
    }
    const auto tilePos = reply->property("TILE_POS").value<QGV::GeoTilePos>();

    if (reply->error() != QNetworkReply::NoError) {
        if (reply->error() != QNetworkReply::OperationCanceledError) {
            qgvCritical() << "ERROR" << reply->errorString();
        }
        removeReply(tilePos);
        return;
    }

    removeReply(tilePos);
    const auto rawImage = reply->readAll();
    const auto shapes = buildShapes(tilePos, rawImage);
    for (const auto& shape : shapes) {
        onTile(tilePos, shape);
        // removeItem(shape);
        // addItem(shape);
    }
}

void QGVVectorTilesOnline::setHasApiKey(const bool& val)
{
    bHasApiKey = val;
}

bool QGVVectorTilesOnline::hasApiKey() const
{
    return bHasApiKey;
}

void QGVVectorTilesOnline::setApiKey(const QString& apiKey)
{
    mApiKey = apiKey;
    if (mApiKey.isEmpty()) {
        setHasApiKey(false);
    } else {
        setHasApiKey(true);
    }
}

QString QGVVectorTilesOnline::getApiKey() const
{
    return mApiKey;
}
