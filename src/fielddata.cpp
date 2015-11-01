#include "fielddata.h"


FieldData::FieldData()
    : _type(0), _color("#ffffff")
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

int FieldData::part() const
{
    return _part;
}

void FieldData::setPart(int part)
{
    _part = part;
}

int FieldData::orientation() const
{
    return _orientation;
}

void FieldData::setOrientation(int orientation)
{
    _orientation = orientation;
}

void FieldData::setData(int type, int part, int orientation)
{
    setType(type);
    setPart(part);
    setOrientation(orientation);
}
