/**
 * \class Settings
 *
 * \brief Global game settings
 *
 * This class provides all informations about the game context,
 * such as the number of rows and columns or the shippoints. The
 * Settings object is implemented as a singleton.
 *
 */

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

public:
    static QObject* qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine); ///< For qml singleton creation

    int numFields() const;
    void setNumFields(int numFields);

    int shipPoints() const;
    void setShipPoints(int shipPoints);

    static Settings* instance();

signals:
    void numFieldsChanged();
    void shipPointsChanged();

private:
    explicit Settings(QObject* parent = nullptr);

    int _numFields;  ///< Number of rows and columns
    int _shipPoints; ///< Number of ship points

    static Settings* _instance; ///< Actual instance of the singleton
};

#endif // SETTINGS_H
