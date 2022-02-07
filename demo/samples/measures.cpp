#include "measures.h"

#include <QGeoView/QGVGlobal.h>
#include <QGeoView/QGVWidgetMeasure.h>

MeasuresDemo::MeasuresDemo(QGVMap* geoMap, QObject* parent)
    : DemoItem(geoMap, SelectorDialog::Multi, parent)
{}

QString MeasuresDemo::label() const
{
    return "Measuring";
}

QString MeasuresDemo::comment() const
{
    return "QGV now supports widget for measuring distances. This includes:<br>"
           "- QGVWidgetMeasure<br>";
}

void MeasuresDemo::onInit()
{
    /*
     * List of available widgets.
     */

    // Rome and Naples as starting positions of the pins
    mWidgetMeasure = new QGVWidgetMeasure();
    QList<QPair<QString, QGVWidget*>> widgets = {
        { "QGVWidgetMeasure",  mWidgetMeasure}
    };
    /*
     *
     * Widgets will be owned by map.
     */
    for (auto pair : widgets) {
        auto name = pair.first;
        auto widget = pair.second;
        geoMap()->addWidget(widget);
        selector()->addItem(name, std::bind(&MeasuresDemo::setSelected, this, widget, std::placeholders::_1));
    }

    // Widget configuration
    const auto distanceLabelPrefix = QString("");
    const auto bearingLabelPrefix = QString("Rotta:");
    const auto ballonValueSeparator = QString("-");
    const auto ballonBackground = QColor::fromRgb(0, 62, 126);
    const auto ballonText = Qt::white;
    const auto ballonTextPadding = 7;
    const auto lineColor = Qt::red;
    const auto lineWidth = 100;
    const auto iconPinMovement = QString(":/resources/pin-icon-highlight.png");
    const qreal pinMetersOffset{25000};
    const qreal leftPinAzimuthOffset{90};
    const qreal rightPinAzimuthOffset{270};

    const auto widgetBtnIcon = iconPinMovement;
    const auto widgetBtnSize = QSize(45, 45);

    const auto widgetBtnActiveColor = QColor::fromRgb(154, 211, 254);

    // How to change widget position on screen
    /* mWidgetMeasure->setAnchor(QPoint(30, 30), mWidgetMeasure->getWidgetAnchorEdges());
    mWidgetMeasure->setWidgetAnchorEdges({Qt::TopEdge, Qt::LeftEdge}); */

    // How to change widget btn icon/size
    // mWidgetMeasure->setWidgetBtnIcon(widgetBtnIcon);
    mWidgetMeasure->setWidgetBtnSize(widgetBtnSize);

    mWidgetMeasure->setPinStartingPointMetersOffset(pinMetersOffset);
    mWidgetMeasure->setLeftPinAzimuthOffset(leftPinAzimuthOffset);
    mWidgetMeasure->setRightPinAzimuthOffset(rightPinAzimuthOffset);

    mWidgetMeasure->setBtnExternalBorderColor(Qt::white);
    mWidgetMeasure->setBtnExternalRectColor(ballonBackground);
    mWidgetMeasure->setBtnInternalRectColor(Qt::white);
    mWidgetMeasure->setBtnActiveInternalRectColor(widgetBtnActiveColor);

    mWidgetMeasure->setDistanceLabelPrefix(distanceLabelPrefix);
    mWidgetMeasure->setBearingLabelPrefix(bearingLabelPrefix);
    mWidgetMeasure->setBallonValueSeparator(ballonValueSeparator);
    mWidgetMeasure->setBallonBackgroundColor(ballonBackground);
    mWidgetMeasure->setBallonTextColor(ballonText);
    mWidgetMeasure->setBallonTextPadding(ballonTextPadding);
    mWidgetMeasure->setLineColor(lineColor);
    mWidgetMeasure->setLineWidth(lineWidth);
    mWidgetMeasure->setIconPinMovement(iconPinMovement);

    // mWidgetMeasure->hidePinLine();
    selector()->selectAll();
}

void MeasuresDemo::onStart()
{
    selector()->show();
}

void MeasuresDemo::onEnd()
{
    selector()->hide();
}

void MeasuresDemo::setSelected(QGVWidget* widget, bool selected)
{
    if (widget == nullptr) {
        return;
    }
    widget->setVisible(selected);
}
