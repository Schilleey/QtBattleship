/**
 * \class BattleField
 *
 * \brief Battlefield related informations
 *
 * This class represents the battlefield of the game. TODO
 *
 */

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <QObject>
#include <QAbstractListModel>
#include <QVector>
#include <QQmlEngine>

#include "fielddata.h"


class BattleField : public QAbstractListModel
{
    Q_OBJECT

public:
    BattleField(QObject* parent = nullptr);

    Q_INVOKABLE void initialize();
    Q_INVOKABLE void setField(int row, int column, int data);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QVector<FieldData*> _model;

    int indexToRow(const int index) const;
    int indexToColumn(const int index) const;
};

#endif // BATTLEFIELD_H
