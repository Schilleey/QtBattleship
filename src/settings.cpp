#include "settings.h"


Settings::Settings()
    : _numFields(16), _shipPoints(32)
{
}

QObject* Settings::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return new Settings;
}

int Settings::numFields() const
{
    return _numFields;
}

void Settings::setNumFields(int numFields)
{
    _numFields = numFields;
}

int Settings::shipPoints() const
{
    return _shipPoints;
}

void Settings::setShipPoints(int shipPoints)
{
    _shipPoints = shipPoints;
}

