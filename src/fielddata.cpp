#include "fielddata.h"


FieldData::FieldData()
    : _type(0), _color("#ff0000")
{

}

int FieldData::type() const
{
    return _type;
}

void FieldData::setType(int type)
{
    _type = type;
}

QString FieldData::color() const
{
    return _color;
}

void FieldData::setColor(const QString &color)
{
    _color = color;
}
