#include "tilting.h"

#include "QGeoView/QGVWidgetPerspective.h"

TiltingDemo::TiltingDemo(QGVMap* geoMap, QObject* parent)
    : DemoItem(geoMap, SelectorDialog::Multi, parent)
{}

QString TiltingDemo::label() const
{
    return "Tilting";
}

QString TiltingDemo::comment() const
{
    return "QGV now supports widget for a perspective rotation of the map. This includes:<br>"
           "- QGVWidgetPerspective<br>";
}

void TiltingDemo::onStart()
{
    selector()->show();
}

void TiltingDemo::onEnd()
{
    selector()->hide();
}

void TiltingDemo::setSelected(QGVWidget* widget, bool selected)
{
    if (widget == nullptr) {
        return;
    }

    widget->setVisible(selected);
}

void TiltingDemo::onInit()
{
    mWidget = new QGVWidgetPerspective();

    QList<QPair<QString, QGVWidget*>> widgets = {
        { "QGVWidgetPerspective",  mWidget}
    };

    for (auto pair : widgets) {
        auto name = pair.first;
        auto widget = pair.second;
        geoMap()->addWidget(widget);
        selector()->addItem(name, std::bind(&TiltingDemo::setSelected, this, widget, std::placeholders::_1));
    }

    mWidget->setSliderOrientation(Qt::Orientation::Horizontal);
    mWidget->setAnchor(QPoint(150, 10), QSet<Qt::Edge>({Qt::Edge::BottomEdge, Qt::Edge::RightEdge}));

    selector()->selectAll();
}

