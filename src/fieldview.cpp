#include <QDebug>
#include <QTransform>

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

    const FieldData& fielddata = _data.value<FieldData>();

    QColor color(fielddata.color());
    QBrush brush(color);

    painter->fillRect(boundingRect(), brush);

    if(fielddata.type() != FieldData::None)
    {
        if(_svgRenderer.isValid())
        {
            const QRectF& rect = boundingRect();

            if(fielddata.orientation() == FieldData::Vertical)
            {
                painter->translate(rect.width(), 0.0);
                painter->rotate(90.0);
            }

            _svgRenderer.render(painter, rect);
        }
    }
}

QVariant FieldView::data() const
{
    return _data;
}

void FieldView::setData(const QVariant &data)
{
    if(!data.canConvert<FieldData>())
        return;

    _data = data;

    const FieldData& fielddata = _data.value<FieldData>();

    switch(fielddata.type())
    {
    case FieldData::None:
        {
            break;
        }
    case FieldData::BattleShip:
        {
            const QString imagePath = QString(":/images/resources/BattleShip_%1.svg").arg(fielddata.part());
            _svgRenderer.load(imagePath);
            break;
        }
    }

    update();
}
