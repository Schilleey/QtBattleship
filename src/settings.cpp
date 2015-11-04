#include "settings.h"


Settings* Settings::_instance = nullptr;

Settings::Settings(QObject* parent)
    : QObject(parent), _numFields(16), _shipPoints(32), _fieldSize(20)
{
}

QObject* Settings::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    if(!_instance)
        _instance = new Settings;

    return _instance;
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

Settings *Settings::instance()
{
    return _instance;
}

int Settings::fieldSize() const
{
    return _fieldSize;
}

void Settings::setFieldSize(int fieldSize)
{
    _fieldSize = fieldSize;
}

