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
        Cruiser,
        Destroyer,
        Submarine,
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

    bool hideImage() const;
    void setHideImage(bool hideImage);

    int modelPosition() const;

    void setData(int type, int part, int partNumber, int orientation, int shipId);
    bool isEmpty();
    void clear();
    void reset();

    int shipId() const;
    void setShipId(int shipId);

    bool isHit() const;
    void setIsHit(bool isHit);

    bool isTried() const;
    void setIsTried(bool isTried);

    int partNumber() const;
    void setPartNumber(int partNumber);

private:
    int _type;
    int _shipId;
    QString _color;
    int _part;
    int _partNumber;
    int _orientation;
    int _modelPosition;
    bool _hideImage;
    bool _isHit;
    bool _isTried;
};

Q_DECLARE_METATYPE(FieldData)

#endif // FIELDDATA_H
