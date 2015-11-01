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
    // Test data
    int size = Settings::instance()->numFields();
    for(int i = 0; i < size*size; i++)
    {
        _model.push_back(new FieldData());
    }

    _model[2 * size + 4]->setColor("black");
    _model[3 * size + 4]->setColor("cyan");
    _model[4 * size + 4]->setColor("yellow");

    // BattleShip
    _model[1 * size + 1]->setData(FieldData::BattleShip, 1, FieldData::Vertical);
    _model[2 * size + 1]->setData(FieldData::BattleShip, 2, FieldData::Vertical);
    _model[3 * size + 1]->setData(FieldData::BattleShip, 2, FieldData::Vertical);
    _model[4 * size + 1]->setData(FieldData::BattleShip, 3, FieldData::Vertical);
}

void BattleField::setField(int row, int column, int data)
{
    Q_UNUSED(data);

    int size = Settings::instance()->numFields();
    int position = row * size + column;

    QColor randomColor(rand()%255, rand()%255, rand()%255);
    _model[position]->setColor(randomColor.name());

    QModelIndex index = createIndex(position, 0);
    emit dataChanged(index, index);
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

//    if(role == FieldType)
//        return _model[indexToRow(index.row()) * Settings::instance()->numFields() + indexToColumn(index.row())].getType();
//    else if(role == FieldColor)
//        return _model[indexToRow(index.row()) * Settings::instance()->numFields() + indexToColumn(index.row())].getColor();

    return QVariant::Invalid;
}

int BattleField::indexToRow(const int index) const
{
    return floor(index / Settings::instance()->numFields());
}

int BattleField::indexToColumn(const int index) const
{
    return index % Settings::instance()->numFields();
}

