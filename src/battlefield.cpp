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
      _numberOfShips(0),
      _isInitialized(false)
{
    connect(Settings::instance(), SIGNAL(numFieldsChanged(int)), SLOT(updateModelSize(int)));
}

void BattleField::initialize()
{
    if(_isInitialized)
        return;

    _isInitialized = true;

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
        if(fieldData->isTried())
            return false;

        fieldData->setIsHit(hit);
        fieldData->setIsTried(true);

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
            field->setData(type, Config::imageOfShip(type, i), i, orientation, _currentShipId);
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
            field->setData(type, Config::imageOfShip(type, i), i, orientation, _currentShipId);
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

bool BattleField::removeShip(int row, int column)
{
    FieldData* data = getFieldData(row, column);
    if(data)
    {
        FieldData::ImageOrientation orientation = (FieldData::ImageOrientation)data->orientation();
        int shipId = data->shipId();
        int shipLength = Config::lengthOfShip[data->type()];
        int shipPart = data->partNumber();

        QList<FieldData*> items = getFieldDataItemsById(shipId);
        foreach(FieldData* item, items)
        {
            item->clear();
        }

        if(orientation == FieldData::Horizontal)
            updateRect(row, column - shipPart, row, (column - shipPart) + shipLength - 1);
        else
            updateRect(row - shipPart, column, (row - shipPart) + shipLength - 1, column);

        return true;
    }

    return false;
}

bool BattleField::removeShip(int position)
{
    int row = indexToRow(position);
    int column = indexToColumn(position);

    return removeShip(row, column);
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

    if(role == FieldDataRole)
        return QVariant::fromValue(*_model[indexToRow(index.row()) * Settings::instance()->numFields() + indexToColumn(index.row())]);
    else if(role == TriedRole)
        return QVariant::fromValue(_model[indexToRow(index.row()) * Settings::instance()->numFields() + indexToColumn(index.row())]->isTried());
    else if(role == SizeRole)
        return QVariant::fromValue(shipSizeAtIndex(index.row()));
    else if(role == OrientationRole)
        return QVariant::fromValue(_model[indexToRow(index.row()) * Settings::instance()->numFields() + indexToColumn(index.row())]->orientation());

    return QVariant::Invalid;
}

int BattleField::numberOfShips() const
{
    return _numberOfShips;
}

QHash<int, QByteArray> BattleField::roleNames() const
{
    QHash<int, QByteArray> roles;
        roles[FieldDataRole] = "fielddata";
        roles[TriedRole] = "tried";
        roles[SizeRole] = "shipSize";
        roles[OrientationRole] = "shipOrientation";
    return roles;
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

void BattleField::updateModelSize(const int numFields)
{
    if(!_isInitialized)
        return;

    int currentSize = _model.size();
    if(currentSize == (numFields*numFields))
        return;

    _model.clear();

    _isInitialized = false;
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

bool BattleField::moveShip(const int oldIndex, const int newIndex)
{
    // Get ship information
    FieldData* data = getFieldData(oldIndex);
    if(!data)
        return false;

    FieldData::ImageType shipType = (FieldData::ImageType)data->type();
    FieldData::ImageOrientation shipOri = (FieldData::ImageOrientation)data->orientation();
    int partNumber = data->partNumber();

    // Remove ship
    bool remove = removeShip(oldIndex);
    if(!remove)
        return false;

    // Place ship at new location
    bool place = setShip(newIndex, shipType, shipOri);
    if(!place)
    {
        // If this fails, put old ship back
        if(shipOri == FieldData::Horizontal)
            setShip(oldIndex - partNumber, shipType, shipOri);
        else
            setShip(oldIndex - partNumber * Settings::instance()->numFields(), shipType, shipOri);

        return false;
    }

    return true;
}

bool BattleField::changeShipOrientation(const int index)
{
    // Get ship information
    FieldData* data = getFieldData(index);
    if(!data)
        return false;

    FieldData::ImageType shipType = (FieldData::ImageType)data->type();
    FieldData::ImageOrientation shipOri = (FieldData::ImageOrientation)data->orientation();
    int partNumber = data->partNumber();
    int indexPart0 = 0;
    FieldData::ImageOrientation shipOriSwitched = FieldData::Horizontal;
    if(shipOri == FieldData::Horizontal)
    {
        shipOriSwitched = FieldData::Vertical;
        indexPart0 = index - partNumber;
    }
    else
    {
        shipOriSwitched = FieldData::Horizontal;
        indexPart0 = index - partNumber * Settings::instance()->numFields();
    }

    // Remove ship
    bool remove = removeShip(index);
    if(!remove)
        return false;

    // Place ship with new orientation
    bool place = setShip(indexPart0, shipType, shipOriSwitched);
    if(!place)
    {
        setShip(indexPart0, shipType, shipOri);
        return false;
    }

    return true;
}

int BattleField::shipSizeAtIndex(const int index) const
{
    FieldData* data = getFieldData(index);
    if(data)
    {
        QList<FieldData*> items = getFieldDataItemsById(data->shipId());
        return items.size();
    }

    return 0;
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
    if(!checkPos(position))
        return nullptr;

    return _model[position];
}

int BattleField::getLeftPos(const int position) const
{
    if(!checkPos(position - 1))
        return -1;

    if(((position+1) % Settings::instance()->numFields()) == 1)
        return -1;

    return position - 1;
}

int BattleField::getRightPos(const int position) const
{    
    if(!checkPos(position + 1))
        return -1;

    if(((position+1) % Settings::instance()->numFields()) == 0)
        return -1;

    return position + 1;
}

int BattleField::getUpPos(const int position) const
{
    int size = Settings::instance()->numFields();
    if(!checkPos(position - size))
        return - 1;

    return position - size;
}

int BattleField::getDownPos(const int position) const
{
    int size = Settings::instance()->numFields();
    if(!checkPos(position + size))
        return - 1;

    return position + size;
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

bool BattleField::checkPos(const int position) const
{
    int size = Settings::instance()->numFields();
    int size2 = size * size;
    if(position < 0 || position >= size2)
        return false;

    return true;
}

