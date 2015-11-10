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
    Q_INVOKABLE bool setShip(int row, int column, FieldData::ImageType type, FieldData::ImageOrientation orientation);
    Q_INVOKABLE void clear();

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

public slots:
    void updateField(const int row, const int column);
    void updateField(const int position);
    void updateRect(const int xleft, const int ytop, const int xright, const int ybottom);

private:
    QVector<FieldData*> _model;

    int indexToRow(const int index) const;
    int indexToColumn(const int index) const;
    int getPosition(const int row, const int column) const;
    FieldData* getFieldData(const int row, const int column) const;
    bool checkRectEmpty(const int xleft, const int ytop, const int xright, const int ybottom) const;
};

#endif // BATTLEFIELD_H
