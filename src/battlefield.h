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
#include <QMap>
#include <QQmlEngine>

#include "fielddata.h"


class BattleField : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int numberOfShips READ numberOfShips NOTIFY numberOfShipsChanged)

public:
    BattleField(QString name, QObject* parent = nullptr);

    Q_INVOKABLE void initialize();
    Q_INVOKABLE bool fieldIsEmpty(int position);
    Q_INVOKABLE void clear();
    Q_INVOKABLE QString getName();
    Q_INVOKABLE void hideImages(bool hide);

    void setField(int row, int column, int data);
    bool setFieldHit(int position, bool hit);
    bool setShip(int row, int column, FieldData::ImageType type, FieldData::ImageOrientation orientation);
    bool setShip(int position, FieldData::ImageType type, FieldData::ImageOrientation orientation);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    int numberOfShips() const;

signals:
    void numberOfShipsChanged(int numberOfShips);

public slots:
    void updateField(const int row, const int column);
    void updateField(const int position);
    void updateRect(const int xleft, const int ytop, const int xright, const int ybottom);

private:
    QVector<FieldData*> _model;
    QMap<int, QList<FieldData*> > _fieldsById;
    QString _name;
    int _currentShipId;
    int _numberOfShips;

    int indexToRow(const int index) const;
    int indexToColumn(const int index) const;
    int getPosition(const int row, const int column) const;
    FieldData* getFieldData(const int row, const int column) const;
    FieldData* getFieldData(const int position) const;
    QList<FieldData*> getFieldDataItemsById(const int id) const;
    void calculateNumberOfShips();
    bool checkRectEmpty(const int xleft, const int ytop, const int xright, const int ybottom) const;
};

#endif // BATTLEFIELD_H
