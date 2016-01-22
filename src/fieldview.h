/**
 * \class FieldView
 *
 * \brief Renders one field of the battlefield
 *
 * This class defines how the rendering of one field of the
 * battlefield is done. Every ship image is saved as an SVG.
 *
 */

#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QtQuick>
#include <QtSvg/QSvgRenderer>
#include <QString>


class FieldView : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QVariant data READ data WRITE setData)

public:
    FieldView(QQuickItem* parent = nullptr);

    void paint(QPainter* painter);

    QVariant data() const;
    void setData(const QVariant& data);

private:
    QVariant _data;            ///< Actual data from the model
    QSvgRenderer _svgRenderer; ///< Renderer for svg graphics
};

#endif // FIELDVIEW_H
