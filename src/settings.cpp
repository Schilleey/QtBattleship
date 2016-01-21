#include <QDebug>

#include "settings.h"


Settings* Settings::_instance = nullptr;

Settings::Settings(QObject* parent)
    : QSettings(QSettings::IniFormat, QSettings::UserScope, "HSA", "QBattleShip", parent)
{
}

QObject* Settings::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return Settings::instance();
}

Settings *Settings::instance()
{
    if(!_instance)
        _instance = new Settings;

    return _instance;
}

void Settings::save()
{
    setValue("numFields", QVariant(_numFields));
    setValue("fieldSize", QVariant(_fieldSize));
    setValue("boardColor", QVariant(_boardColor));
    setValue("difficulty", QVariant((int)_difficulty));

    qDebug() << "Settings saved.";
}

void Settings::load()
{
    _numFields = value("numFields", QVariant(16)).toInt();
    _fieldSize = value("fieldSize", QVariant(20)).toInt();
    _boardColor = value("boardColor", QVariant("white")).toString();
    _difficulty = (Settings::Difficulty) value("difficulty", QVariant((int)Better)).toInt();
}

int Settings::numFields() const
{
    return _numFields;
}

void Settings::setNumFields(int numFields)
{
    _numFields = numFields;
    emit numFieldsChanged(_numFields);
}

int Settings::fieldSize() const
{
    return _fieldSize;
}

void Settings::setFieldSize(int fieldSize)
{
    _fieldSize = fieldSize;
    emit fieldSizeChanged(_fieldSize);
}

QString Settings::boardColor() const
{
    return _boardColor;
}

void Settings::setBoardColor(QString boardColor)
{
    _boardColor = boardColor;
    emit boardColorChanged(_boardColor);
}

Settings::Difficulty Settings::difficulty() const
{
    return _difficulty;
}

void Settings::setDifficulty(const Settings::Difficulty &difficulty)
{
    _difficulty = difficulty;
    emit difficultyChanged(_difficulty);
}
