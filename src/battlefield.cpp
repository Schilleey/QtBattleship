#include "battlefield.h"
#include "config.h"
#include "settings.h"

#include <QRect>
#include <QColor>
#include <QDebug>


BattleField::BattleField(QString name, QObject *parent)
    : QAbstractListModel(parent),
      _name(name),
      _currentShipId(0),
      _numberOfShips(0)
{
}

void BattleField::initialize()
{
    // Fill model with data
    int size = Settings::instance()->numFields();
    for(int i = 0; i < size*size; i++)
        _model.push_back(new FieldData(i));

    calculateNumberOfShips();
}

void BattleField::setField(int row, int column, int data)
{
    Q_UNUSED(data);

    int position = getPosition(row, column);

    QColor randomColor(rand()%255, rand()%255, rand()%255);
    _model[position]->setColor(randomColor.name());

    updateField(position);
}

bool BattleField::setFieldHit(int position, bool hit)
{
    FieldData* fieldData = getFieldData(position);
    if(fieldData)
    {
        if(fieldData->isHit())
            return false;

        fieldData->setIsHit(hit);

        if(hit)
        {
            fieldData->setColor("#00ff00");

            QList<FieldData*> shipFields = _fieldsById[fieldData->shipId()];
            bool shipSunken = true;
            foreach(FieldData* field, shipFields)
            {
                shipSunken = field->isHit();
                if(!shipSunken)
                    break;
            }

            if(shipSunken)
            {
                _numberOfShips--;
                emit numberOfShipsChanged(_numberOfShips);
                foreach(FieldData* field, shipFields)
                {
                    field->setHideImage(false);
                    updateField(field->modelPosition());
                }
            }
        }
        else
        {
            fieldData->setColor("#ff0000");
        }

        updateField(position);
    }

    return true;
}

bool BattleField::setShip(int row, int column, FieldData::ImageType type, FieldData::ImageOrientation orientation)
{
    if(type == FieldData::None)
        return false;

    int shipLength = Config::lengthOfShip[type];

    int xleft = column - 1;
    int ytop = row - 1;
    int xright, ybottom;

    int size = Settings::instance()->numFields();

    if(orientation == FieldData::Horizontal) // Horizontal
    {
        xright = xleft + shipLength + 1;
        ybottom = ytop + 2;
    }
    else // Vertical
    {
        xright = xleft + 2;
        ybottom = ytop + shipLength + 1;
    }

    // Check if ship is outside the board
    if(xleft < -1 || ytop < -1 || xright > size || ybottom > size)
        return false;

    QRect boardRect(0, 0, size, size);
    QRect shipRect(QPoint(xleft, ytop), QPoint(xright, ybottom));

    // Get actual ship rectangle
    QRect iRect = boardRect.intersected(shipRect);

    // Check if ship can be placed
    if(!checkRectEmpty(iRect.x(), iRect.y(), iRect.right(), iRect.bottom()))
        return false;

    // Place ship
    if(orientation == FieldData::Horizontal)
    {
        FieldData* field;
        for(int i = 0; i < shipLength; i++)
        {
            field = getFieldData(row, column + i);
            field->setData(type, Config::imageOfShip(type, i), orientation, _currentShipId);
            _fieldsById[_currentShipId].push_back(field);
        }

        updateRect(row, column, row, column + shipLength - 1);
    }
    else
    {
        FieldData* field;
        for(int i = 0; i < shipLength; i++)
        {
            field = getFieldData(row + i, column);
            field->setData(type, Config::imageOfShip(type, i), orientation, _currentShipId);
            _fieldsById[_currentShipId].push_back(field);
        }

        updateRect(row, column, row + shipLength - 1, column);
    }

    _currentShipId++;

    return true;
}

bool BattleField::setShip(int position, FieldData::ImageType type, FieldData::ImageOrientation orientation)
{
    int row = indexToRow(position);
    int column = indexToColumn(position);

    return setShip(row, column, type, orientation);
}

bool BattleField::fieldIsEmpty(int position)
{
    FieldData* data = getFieldData(position);
    if(!data)
        return false;

    return data->isEmpty();
}

void BattleField::clear()
{
    int size = Settings::instance()->numFields();
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            getFieldData(i, j)->clear();

    _currentShipId = 0;
    _fieldsById.clear();

    calculateNumberOfShips();

    emit layoutChanged();
}

QString BattleField::getName()
{
    return _name;
}

void BattleField::hideImages(bool hide)
{
    int size = Settings::instance()->numFields();
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            getFieldData(i, j)->setHideImage(hide);

    emit layoutChanged();
}

int BattleField::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _model.size();
}

QVariant BattleField::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant::Invalid;

    if(role == Qt::DisplayRole)
        return QVariant::fromValue(*_model[indexToRow(index.row()) * Settings::instance()->numFields() + indexToColumn(index.row())]);

    return QVariant::Invalid;
}

int BattleField::numberOfShips() const
{
    return _numberOfShips;
}

void BattleField::updateField(const int row, const int column)
{
    int position = getPosition(row, column);
    if(position < 0)
        return;

    updateField(position);
}

void BattleField::updateField(const int position)
{
    QModelIndex index = createIndex(position, 0);
    emit dataChanged(index, index);
}

void BattleField::updateRect(const int xleft, const int ytop, const int xright, const int ybottom)
{
    int topLeft = getPosition(xleft, ytop);
    int bottomRight = getPosition(xright, ybottom);

    if(topLeft < 0 || bottomRight < 0)
        return;

    emit dataChanged(createIndex(topLeft, 0), createIndex(bottomRight, 0));
}

int BattleField::indexToRow(const int index) const
{
    int size = Settings::instance()->numFields();
    return int(floor(index / size)) % size;
}

int BattleField::indexToColumn(const int index) const
{
    return index % Settings::instance()->numFields();
}

int BattleField::getPosition(const int row, const int column) const
{
    int size = Settings::instance()->numFields();
    if(row < 0 || row >= size || column < 0 || column >= size)
        return -1;

    return row * size + column;
}

FieldData *BattleField::getFieldData(const int row, const int column) const
{
    int position = getPosition(row, column);
    if(position < 0)
        return nullptr;

    return _model[position];
}

FieldData *BattleField::getFieldData(const int position) const
{
    int size = Settings::instance()->numFields();
    int size2 = size * size;
    if(position < 0 || position >= size2)
        return nullptr;

    return _model[position];
}

QList<FieldData *> BattleField::getFieldDataItemsById(const int id) const
{
    if(_fieldsById.contains(id))
        return _fieldsById[id];

    return QList<FieldData*>();
}

void BattleField::calculateNumberOfShips()
{
    int numFields = Settings::instance()->numFields();

    QList<int> numShips = Config::shipsPerBattlefield(numFields);

    _numberOfShips = 0;
    foreach(int i, numShips)
        _numberOfShips += i;

    emit numberOfShipsChanged(_numberOfShips);
}

bool BattleField::checkRectEmpty(const int xleft, const int ytop, const int xright, const int ybottom) const
{
    int leftTop = getPosition(xleft, ytop);
    int bottomRight = getPosition(xright, ybottom);

    if((leftTop == bottomRight) || leftTop < 0 || bottomRight < 0)
        return false;

    int width = xright - xleft;
    int height = ybottom - ytop;

    if(width < 0 || height < 0)
        return false;

    FieldData* data = nullptr;
    for(int i = 0; i <= height; i++)
    {
        for(int j = 0; j <= width; j++)
        {
            data = getFieldData(ytop + i, xleft + j);
            if(!data)
                return false;
            if(!data->isEmpty())
                return false;
        }
    }

    return true;
}

