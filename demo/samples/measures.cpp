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

    const auto ballonBackground = QColor::fromRgb(0, 62, 126);
    const auto ballonText = Qt::white;

    mWidgetMeasure->setDistanceLabelPrefix("Distanza: ");
    mWidgetMeasure->setBearingLabelPrefix("Rotta: ");
    mWidgetMeasure->setBallonValueSeparator("-");
    mWidgetMeasure->setBallonBackgroundColor(ballonBackground);
    mWidgetMeasure->setBallonTextColor(ballonText);
    mWidgetMeasure->setBallonTextPadding(7);
    mWidgetMeasure->setLineColor(Qt::red);
    mWidgetMeasure->setIconPinMovement(":/resources/pin-icon-highlight.png");

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
