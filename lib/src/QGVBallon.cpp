#include "QGVBallon.h"

#include <QPainter>

QGVBallon::QGVBallon(QGVItem* parent, const QGV::GeoPos& pos, const QString& text) :
    mGeoPos(pos),
    mBallonText(text),
    bShouldShowBallon(true),
    mBallonBackground(Qt::blue),
    mBallonTextColor(Qt::white),
    mBallonTextPadding(5),
    mMarginBottom(0)
{
    setParent(parent);
    const auto flags = QGV::ItemFlag::Transformed | QGV::ItemFlag::IgnoreScale;
    setFlags(flags);
    setSelectable(true);
}

void QGVBallon::showBallon()
{
    bShouldShowBallon = true;
    repaint();
}

void QGVBallon::hideBallon()
{
    bShouldShowBallon = false;
    repaint();
}

bool QGVBallon::shouldShowBallon()
{
    return bShouldShowBallon;
}

void QGVBallon::setBallonText(const QString& baloonText)
{
    resetBoundary();
    mBallonText = baloonText;
    refresh();
    repaint();
}

QString QGVBallon::getBallonText() const
{
    return mBallonText;
}

void QGVBallon::setBallonBackground(const QColor& background)
{
    mBallonBackground = background;
}

QColor QGVBallon::getBallonBackground() const
{
    return mBallonBackground;
}

void QGVBallon::setBallonTextColor(const QColor& textColor)
{
    mBallonTextColor = textColor;
}

QColor QGVBallon::getBallonTextColor() const
{
    return mBallonTextColor;
}

void QGVBallon::setBallonTextPadding(const int& textPadding)
{
    mBallonTextPadding = textPadding;
}

int QGVBallon::getBallonTextPadding() const
{
    return mBallonTextPadding;
}

void QGVBallon::setMarginBottom(const int& marginBottom)
{
    mMarginBottom = marginBottom;
}

int QGVBallon::getMarginBottom() const
{
    return mMarginBottom;
}

void QGVBallon::onProjection(QGVMap* geoMap)
{
    QGVDrawItem::onProjection(geoMap);
    mProjAnchor = geoMap->getProjection()->geoToProj(mGeoPos);
    // Hardcoded starting rect
    mProjRect = QRectF(mProjAnchor, QSize(40, 20));
}

QPainterPath QGVBallon::projShape() const
{
    QPainterPath path;
    path.addRect(mProjRect);
    return path;
}

void QGVBallon::projPaint(QPainter* painter)
{
    if (!shouldShowBallon()) {
        return;
    }
    // Ballon size
    // Create rect to fit the text
    const auto fontMetrics = painter->fontMetrics();
    const auto ballonRect = fontMetrics.boundingRect(getBallonText());

    // Center the rect
    const auto rectAnchor = QPointF(ballonRect.width() / 2, ballonRect.height() / 2 + getMarginBottom());
    const QPointF basePos = getMap()->getProjection()->geoToProj(mGeoPos);
    const QPointF rectPos = basePos - rectAnchor;

    resetBoundary();
    // Padding management
    mProjRect = QRectF(rectPos.x(), rectPos.y(), ballonRect.width() + getBallonTextPadding(), ballonRect.height() + getBallonTextPadding());

    // Ballon rect drawing
    painter->setPen(QPen(QBrush(getBallonBackground()), 1));
    painter->setBrush(QBrush(getBallonBackground()));
    painter->drawRoundedRect(mProjRect, 5, 5);

    // Ballon text drawing
    // Center the text plus padding
    const auto textAnchor = QPointF(projAnchor().x() + getBallonTextPadding(), projAnchor().y() + mProjRect.height() - 5);
    painter->setPen(QPen(QBrush(getBallonTextColor()), 1));
    painter->setBrush(QBrush(getBallonTextColor()));
    painter->drawText(textAnchor - rectAnchor, getBallonText());
}

QPointF QGVBallon::projAnchor() const
{
    return mProjAnchor;
}

void QGVBallon::move(const QGV::GeoPos& newPos)
{
    mGeoPos = newPos;
    mProjAnchor = getMap()->getProjection()->geoToProj(mGeoPos);

    // Center the rect to the new position (with same width and height)
    const auto rectAnchor = QPointF(mProjRect.width() / 2, mProjRect.height() / 2 + getMarginBottom());
    const QPointF rectPos = mProjAnchor - rectAnchor;

    resetBoundary();
    mProjRect = QRectF(rectPos, mProjRect.size());

    refresh();
    repaint();
}
