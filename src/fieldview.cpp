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
        painter->drawImage(boundingRect(), _image);
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
            const QString imagePath = QString(":/images/resources/BattleShip_%1.png").arg(fielddata.part());
            _image.load(imagePath, "PNG");
            break;
        }
    }

    if(fielddata.orientation() == FieldData::Vertical)
    {
        QTransform imageTransformation;
        imageTransformation.rotate(90.0);
        _image = _image.transformed(imageTransformation);
    }

    update();
}
