#include "fielddata.h"
#include "battlefield.h"


FieldData::FieldData()
{
    clear();
}

FieldData::FieldData(int modelPosition)
    : _modelPosition(modelPosition)
{
    FieldData();
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

int FieldData::modelPosition() const
{
    return _modelPosition;
}

void FieldData::setData(int type, int part, int orientation)
{
    setType(type);
    setPart(part);
    setOrientation(orientation);
}

int FieldData::getShipSize(FieldData::ImageType type)
{
    return shipLength[type];
}

bool FieldData::isEmpty()
{
    return _type == None;
}

void FieldData::clear()
{
    _type = 0;
    _color = "";
    _part = 0;
    _orientation = 0;
}
