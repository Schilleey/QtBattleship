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

    Q_PROPERTY(int numFields READ numFields WRITE setNumFields NOTIFY numFieldsChanged)
    Q_PROPERTY(int shipPoints READ shipPoints WRITE setShipPoints NOTIFY shipPointsChanged)
    Q_PROPERTY(int fieldSize READ fieldSize WRITE setFieldSize NOTIFY fieldSizeChanged)
    Q_PROPERTY(QString boardColor READ boardColor WRITE setBoardColor NOTIFY boardColorChanged)

public:
    static QObject* qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine); ///< For qml singleton creation
    static Settings* instance();

    Q_INVOKABLE void save();
    Q_INVOKABLE void load();

    int numFields() const;
    void setNumFields(int numFields);

    int shipPoints() const;
    void setShipPoints(int shipPoints);

    int fieldSize() const;
    void setFieldSize(int fieldSize);

    QString boardColor() const;
    void setBoardColor(QString boardColor);

signals:
    void numFieldsChanged(int numFields);
    void shipPointsChanged(int shipPoints);
    void fieldSizeChanged(int fieldSize);
    void boardColorChanged(QString boardColor);

private:
    explicit Settings(QObject* parent = nullptr);

    int _numFields;      ///< Number of rows and columns
    int _shipPoints;     ///< Number of ship points
    int _fieldSize;      ///< Size of one field on the board
    QString _boardColor; ///< Battlefield background color

    static Settings* _instance; ///< Actual instance of the singleton
};

#endif // SETTINGS_H
