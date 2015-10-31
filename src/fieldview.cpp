#include <QDebug>
#include "fielddata.h"
#include "fieldview.h"


FieldView::FieldView(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    setFlag(QQuickItem::ItemHasContents, true);
}

void FieldView::paint(QPainter *painter)
{
//    qDebug() << "Draw field" << _color;

    if(!_data.canConvert<FieldData>())
        return;

    const FieldData& fielddata = _data.value<FieldData>();

    QColor color(fielddata.color());
    QBrush brush(color);

    painter->fillRect(boundingRect(), brush);
}

QVariant FieldView::data() const
{
    return _data;
}

void FieldView::setData(const QVariant &data)
{
    _data = data;
}
