#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QQmlEngine>


class Settings : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Settings)

    Q_PROPERTY(int numFields READ numFields WRITE setNumFields NOTIFY numFieldsChanged)
    Q_PROPERTY(int shipPoints READ shipPoints WRITE setShipPoints NOTIFY shipPointsChanged)

    Settings();

public:
    static QObject* qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine);

    int numFields() const;
    void setNumFields(int numFields);

    int shipPoints() const;
    void setShipPoints(int shipPoints);

signals:
    void numFieldsChanged();
    void shipPointsChanged();

private:
    int _numFields;  // Number of rows and columns
    int _shipPoints; // Number of ship points
};

#endif // SETTINGS_H
