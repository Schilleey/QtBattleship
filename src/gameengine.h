/**
 * \class GameEngine
 *
 * \brief Logic implementation
 *
 * This class implements all the game logic. Further
 * here is the initialization of the battelfields and
 * the AI done. The GameEngine can be accessed from
 * QML.
 *
 */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

#include "battlefield.h"
#include "ai.h"


class GameEngine : public QObject
{
    Q_OBJECT

    Q_PROPERTY(BattleField* playerField READ playerField NOTIFY playerFieldChanged)
    Q_PROPERTY(BattleField* opponentField READ opponentField NOTIFY opponentFieldChanged)
    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY isRunningChanged)
    Q_PROPERTY(bool isPlayersTurn READ isPlayersTurn)
    Q_PROPERTY(QString gameInformation READ gameInformation WRITE setGameInformation NOTIFY gameInformationChanged)

public:
    GameEngine(QObject* parent = nullptr);

    BattleField* playerField() const;
    BattleField* opponentField() const;

    void delay(int millisecondsToWait);

    Q_INVOKABLE QString playerFieldName() const;
    Q_INVOKABLE QString opponentFieldName() const;

    Q_INVOKABLE bool placeShipsRandom(QString battleFieldName);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop(bool showText = false);
    Q_INVOKABLE void reset();
    Q_INVOKABLE bool processTurn(int position);

    bool isRunning() const;
    void setIsRunning(bool isRunning);

    bool isPlayersTurn() const;

    QString gameInformation() const;
    void setGameInformation(const QString &gameInformation);

signals:
    void playerFieldChanged(BattleField* field);
    void opponentFieldChanged(BattleField* field);
    void gameInformationChanged(const QString &gameInformation);
    void isRunningChanged(bool isRunning);
    void gameOver(bool winnerIsUser);

private:
    BattleField* _playerField;   ///< Players battlefield
    BattleField* _opponentField; ///< Opponents battlefield
    AI* _ai;                     ///< The AI object
    bool _isRunning;             ///< Indicates that the game is running
    bool _isPlayersTurn;         ///< Indicates players turn
    QString _gameInformation;    ///< Gives an information on the GUI
    int _computerDelay;          ///< Delay in milliseconds for the AIs turn
};

#endif // GAMEENGINE_H
