#ifndef FIELDDATA_H
#define FIELDDATA_H

#include <QMetaType>
#include <QString>


class FieldData
{
public:
    FieldData();

    enum ImageType
    {
        None,
        BattleShip
    };

    enum ImageOrientation
    {
        Horizontal,
        Vertical
    };

    int type() const;
    void setType(int type);

    QString color() const;
    void setColor(const QString &color);

    int part() const;
    void setPart(int part);

    int orientation() const;
    void setOrientation(int orientation);

    void setData(int type, int part, int orientation);

private:
    int _type;
    QString _color;
    int _part;
    int _orientation;
};

Q_DECLARE_METATYPE(FieldData)

#endif // FIELDDATA_H
