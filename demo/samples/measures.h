#ifndef MEASURES_H
#define MEASURES_H

#include "demoitem.h"

class QGVWidgetMeasure;

/**
 * @brief The MeasuresDemo class is a demo class which places a QGVWidgetMeasure on the map
 */
class MeasuresDemo : public DemoItem
{
    Q_OBJECT

public:
    /**
     * @brief MeasuresDemo constructor.
     * Parameters: map and parent object
     */
    explicit MeasuresDemo(QGVMap* geoMap, QObject* parent = 0);

    /**
     * @brief label returns demo title
     * @return QString
     */
    QString label() const override;

    /**
     * @brief comment returns demo description
     * @return QString
     */
    QString comment() const override;

private:
    /**
     * @brief onInit method called for demo initialization.
     */
    void onInit() override;

    /**
     * @brief onStart method called when the demo starts.
     */
    void onStart() override;

    /**
     * @brief onEnd method called when the demo stops.
     */
    void onEnd() override;

    /**
     * @brief setSelected allows changing the visility of a widget inside demo.
     * Parameters: widget to change visibility, new visiblity
     */
    void setSelected(QGVWidget* widget, bool selected);

private:
    /**
     * @brief mWidgetMeasure widget measure object
     */
    QGVWidgetMeasure* mWidgetMeasure;
};

#endif // MEASURES_H
