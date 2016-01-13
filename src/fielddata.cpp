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

bool FieldData::hideImage() const
{
    return _hideImage;
}

void FieldData::setHideImage(bool hideImage)
{
    _hideImage = hideImage;
}

int FieldData::shipId() const
{
    return _shipId;
}

void FieldData::setShipId(int shipId)
{
    _shipId = shipId;
}

bool FieldData::isHit() const
{
    return _isHit;
}

void FieldData::setIsHit(bool isHit)
{
    _isHit = isHit;
}

bool FieldData::isTried() const
{
    return _isTried;
}

void FieldData::setIsTried(bool isTried)
{
    _isTried = isTried;
}

int FieldData::partNumber() const
{
    return _partNumber;
}

void FieldData::setPartNumber(int partNumber)
{
    _partNumber = partNumber;
}

void FieldData::reset()
{
    clear();
}

int FieldData::modelPosition() const
{
    return _modelPosition;
}

void FieldData::setData(int type, int part, int partNumber, int orientation, int shipId)
{
    setType(type);
    setPart(part);
    setPartNumber(partNumber);
    setOrientation(orientation);
    setShipId(shipId);
}

bool FieldData::isEmpty()
{
    return _type == None;
}

void FieldData::clear()
{
    _type = 0;
    _shipId = -1;
    _color = "";
    _part = 0;
    _partNumber = -1;
    _orientation = 0;
    _hideImage = false;
    _isHit = false;
    _isTried = false;
}
