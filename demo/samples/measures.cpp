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
    mWidgetMeasure = new QGVWidgetMeasure(QGV::GeoPos(41.9027835, 12.4963655), QGV::GeoPos(40.851775, 14.268124));
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
    const auto distanceLabelPrefix = QString("Distanza: ");
    const auto bearingLabelPrefix = QString("Rotta: ");
    const auto ballonValueSeparator = QString("-");
    const auto ballonBackground = QColor::fromRgb(0, 62, 126);
    const auto ballonText = Qt::white;
    const auto ballonTextPadding = 7;
    const auto lineColor = Qt::red;
    const auto lineWidth = 250;
    const auto iconPinMovement = QString(":/resources/pin-icon-highlight.png");

    mWidgetMeasure->setDistanceLabelPrefix(distanceLabelPrefix);
    mWidgetMeasure->setBearingLabelPrefix(bearingLabelPrefix);
    mWidgetMeasure->setBallonValueSeparator(ballonValueSeparator);
    mWidgetMeasure->setBallonBackgroundColor(ballonBackground);
    mWidgetMeasure->setBallonTextColor(ballonText);
    mWidgetMeasure->setBallonTextPadding(ballonTextPadding);
    mWidgetMeasure->setLineColor(lineColor);
    mWidgetMeasure->setLineWidth(lineWidth);
    mWidgetMeasure->setIconPinMovement(iconPinMovement);

    mWidgetMeasure->addPinToMap();

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
