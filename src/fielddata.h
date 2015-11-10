#ifndef FIELDDATA_H
#define FIELDDATA_H

#include <QMetaType>
#include <QString>

class BattleField;


class FieldData
{
public:
    FieldData();
    FieldData(int modelPosition);

    enum ImageType
    {
        None,
        BattleShip,
        typeSize // Last element is size of enum
    };

    enum ImageOrientation
    {
        Horizontal,
        Vertical,
        orientationSize
    };

    int type() const;
    void setType(int type);

    QString color() const;
    void setColor(const QString &color);

    int part() const;
    void setPart(int part);

    int orientation() const;
    void setOrientation(int orientation);

    int modelPosition() const;

    void setData(int type, int part, int orientation);
    int getShipSize(ImageType type);
    bool isEmpty();
    void clear();

private:
    int _type;
    QString _color;
    int _part;
    int _orientation;
    int _modelPosition;

    const int shipLength[typeSize] = {0, 3};
};

Q_DECLARE_METATYPE(FieldData)

#endif // FIELDDATA_H
