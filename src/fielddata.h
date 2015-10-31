#ifndef FIELDDATA_H
#define FIELDDATA_H

#include <QMetaType>
#include <QString>


class FieldData
{
public:
    FieldData();

    int type() const;
    void setType(int type);

    QString color() const;
    void setColor(const QString &color);

private:
    int _type;
    QString _color;
};

Q_DECLARE_METATYPE(FieldData)

#endif // FIELDDATA_H
