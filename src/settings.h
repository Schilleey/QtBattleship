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

#include <QSettings>
#include <QQmlEngine>


class Settings : public QSettings
{
    Q_OBJECT
    Q_DISABLE_COPY(Settings)
    Q_ENUMS(Difficulty)

    Q_PROPERTY(int numFields READ numFields WRITE setNumFields NOTIFY numFieldsChanged)
    Q_PROPERTY(int fieldSize READ fieldSize WRITE setFieldSize NOTIFY fieldSizeChanged)
    Q_PROPERTY(QString boardColor READ boardColor WRITE setBoardColor NOTIFY boardColorChanged)
    Q_PROPERTY(Settings::Difficulty difficulty READ difficulty WRITE setDifficulty NOTIFY difficultyChanged)

public:
    static QObject* qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine); ///< For qml singleton creation
    static Settings* instance();

    Q_INVOKABLE void save();
    Q_INVOKABLE void load();

    enum Difficulty
    {
        Simple,
        Better
    };

    int numFields() const;
    void setNumFields(int numFields);

    int fieldSize() const;
    void setFieldSize(int fieldSize);

    QString boardColor() const;
    void setBoardColor(QString boardColor);

    Settings::Difficulty difficulty() const;
    void setDifficulty(const Settings::Difficulty &difficulty);

signals:
    void numFieldsChanged(int numFields);
    void fieldSizeChanged(int fieldSize);
    void boardColorChanged(QString boardColor);
    void difficultyChanged(Settings::Difficulty difficulty);

private:
    explicit Settings(QObject* parent = nullptr);

    int _numFields;         ///< Number of rows and columns
    int _fieldSize;         ///< Size of one field on the board
    QString _boardColor;    ///< Battlefield background color
    Difficulty _difficulty; ///< Difficulty of AI

    static Settings* _instance; ///< Actual instance of the singleton
};

#endif // SETTINGS_H
