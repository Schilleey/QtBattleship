#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QtQuick>
#include <QString>


class FieldView : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QVariant data READ data WRITE setData NOTIFY dataChanged)

public:
    FieldView(QQuickItem* parent = nullptr);

    void paint(QPainter* painter);

    QVariant data() const;
    void setData(const QVariant& data);

signals:
    void dataChanged(QVariant data);

private:
    QVariant _data;
};

#endif // FIELDVIEW_H
