#include "battlefield.h"
#include "settings.h"

#include <QColor>
#include <QDebug>


BattleField::BattleField(QObject *parent)
    : QAbstractListModel(parent)
{
}

void BattleField::initialize()
{
    // Fill model with data
    int size = Settings::instance()->numFields();
    for(int i = 0; i < size*size; i++)
        _model.push_back(new FieldData(i));
}

void BattleField::setField(int row, int column, int data)
{
    Q_UNUSED(data);

    int position = getPosition(row, column);

    QColor randomColor(rand()%255, rand()%255, rand()%255);
    _model[position]->setColor(randomColor.name());

    updateField(position);
}

bool BattleField::setShip(int row, int column, FieldData::ImageType type, FieldData::ImageOrientation orientation)
{
    int shipLength = 0;

    switch(type)
    {
    case FieldData::BattleShip:
        {
            shipLength = 4;
            break;
        }
    }

    if(shipLength == 0)
        return false;

    int xleft = column - 1;
    int ytop = row - 1;
    int xright, ybottom;

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

    // Check if ship can be placed
    if(!checkRectEmpty(xleft, ytop, xright, ybottom))
        return false;

    // Place ship
    if(orientation == FieldData::Horizontal)
    {
        getFieldData(row, column + 0)->setData(type, 1, orientation);
        getFieldData(row, column + 1)->setData(type, 2, orientation);
        getFieldData(row, column + 2)->setData(type, 2, orientation);
        getFieldData(row, column + 3)->setData(type, 3, orientation);

        updateRect(row, column, row, column + shipLength);
    }
    else
    {
        getFieldData(row + 0, column)->setData(type, 1, orientation);
        getFieldData(row + 1, column)->setData(type, 2, orientation);
        getFieldData(row + 2, column)->setData(type, 2, orientation);
        getFieldData(row + 3, column)->setData(type, 3, orientation);

        updateRect(row, column, row + shipLength, column);
    }

    return true;
}

void BattleField::clear()
{
    int size = Settings::instance()->numFields();
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            getFieldData(i, j)->clear();

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
    return floor(index / Settings::instance()->numFields());
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

