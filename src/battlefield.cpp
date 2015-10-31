#include "battlefield.h"
#include "settings.h"

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
}

int BattleField::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _model.size();
}

int BattleField::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Settings::instance()->numFields();
}

QVariant BattleField::data(const QModelIndex &index, int role) const
{
//    qDebug() << "Row: " << index.row() << "Col: " << index.column();

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

