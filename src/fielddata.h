/**
 * \class FieldData
 *
 * \brief Holds the information for one field of the battlefield
 *
 * This class is a plain old C++ object with all information needed
 * for one single field of the battlefield. It is registered with QML
 * to send it via QVariant to the FieldView. Most of the implementation
 * are getters and setters.
 *
 */

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
    int _type;          ///< Indicates the type of the ship
    int _shipId;        ///< ID for the corresponding ship
    QString _color;     ///< Background color for the field
    int _part;          ///< Indicates the image for the field
    int _partNumber;    ///< Index of the part of the ship
    int _orientation;   ///< Orientation of the corresponding ship
    int _modelPosition; ///< Index in the linear model
    bool _hideImage;    ///< Indicates if image should be hidden on the battlefield
    bool _isHit;        ///< Field is hit or not
    bool _isTried;      ///< Field has been tried already
};

Q_DECLARE_METATYPE(FieldData)

#endif // FIELDDATA_H
