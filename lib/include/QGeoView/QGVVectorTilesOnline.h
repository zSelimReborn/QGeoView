#ifndef QGVVECTORTILESONLINE_H
#define QGVVECTORTILESONLINE_H

#include "QGVLayerTilesOnline.h"

class QGV_LIB_DECL QGVVectorTilesOnline : public QGVLayerTilesOnline
{
    Q_OBJECT
public:
    QGVVectorTilesOnline();
    QGVVectorTilesOnline(const QString&);

    void setHasApiKey(const bool&);
    bool hasApiKey() const;

    void setApiKey(const QString&);
    QString getApiKey() const;

protected:
    void onReplyFinished(QNetworkReply* reply) override;
    virtual QList<QGVDrawItem*> buildShapes(const QGV::GeoTilePos&, const QByteArray&) = 0;

private:
    QString mApiKey;
    bool bHasApiKey;
};

#endif // QGVVECTORTILESONLINE_H
