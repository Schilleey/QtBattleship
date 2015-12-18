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
    QVariant _data;
    QSvgRenderer _svgRenderer;
};

#endif // FIELDVIEW_H
