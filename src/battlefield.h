/**
 * \class BattleField
 *
 * \brief Battlefield related information
 *
 * This class represents the battlefield of the game (model).
 * It provides functions for ship placement and for obtaining
 * information about the underlying model. Further it provides
 * many functions to access from QML. The model is rendered using
 * the FieldView class.
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
    Q_INVOKABLE int indexToRow(const int index) const;
    Q_INVOKABLE int indexToColumn(const int index) const;
    Q_INVOKABLE bool moveShip(const int oldIndex, const int newIndex);
    Q_INVOKABLE bool changeShipOrientation(const int index);

    bool setFieldHit(int position, bool hit);
    bool setShip(int row, int column, FieldData::ImageType type, FieldData::ImageOrientation orientation);
    bool setShip(int position, FieldData::ImageType type, FieldData::ImageOrientation orientation);
    bool removeShip(int row, int column);
    bool removeShip(int position);

    FieldData* getFieldData(const int row, const int column) const;
    FieldData* getFieldData(const int position) const;
    int getLeftPos(const int position) const;
    int getRightPos(const int position) const;
    int getUpPos(const int position) const;
    int getDownPos(const int position) const;

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    int numberOfShips() const;

    enum FieldRoles
    {
        FieldDataRole = Qt::UserRole + 1,
        TriedRole,
        SizeRole,
        OrientationRole
    };

protected:
    QHash<int, QByteArray> roleNames() const;

signals:
    void numberOfShipsChanged(int numberOfShips);

public slots:
    void updateField(const int row, const int column);
    void updateField(const int position);
    void updateRect(const int xleft, const int ytop, const int xright, const int ybottom);
    void updateModelSize(const int numFields);

private:
    QVector<FieldData*> _model;                ///< The main model with all information
    QMap<int, QList<FieldData*> > _fieldsById; ///< Map to get all fields related to a ship id
    QString _name;                             ///< Name of battlefield
    int _currentShipId;                        ///< ID of the current ship (gets incremented).
    int _numberOfShips;                        ///< Number of all ships on the battelfield
    bool _isInitialized;                       ///< Indicates if the battlefield is already initialized

    int getPosition(const int row, const int column) const;
    QList<FieldData*> getFieldDataItemsById(const int id) const;
    int shipSizeAtIndex(const int index) const;
    void calculateNumberOfShips();
    bool checkRectEmpty(const int xleft, const int ytop, const int xright, const int ybottom) const;
    bool checkPos(const int position) const;
};

#endif // BATTLEFIELD_H
