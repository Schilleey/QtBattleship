#include <QCoreApplication>
#include <QTime>
#include <QDebug>

#include "gameengine.h"
#include "config.h"
#include "settings.h"
#include "fielddata.h"


GameEngine::GameEngine(QObject *parent)
    : QObject(parent),
      _playerField(nullptr),
      _opponentField(nullptr),
      _isRunning(false),
      _isPlayersTurn(true)
{
    if(!_playerField)
        _playerField = new BattleField(playerFieldName(), this);

    if(!_opponentField)
        _opponentField = new BattleField(opponentFieldName(), this);
}

int GameEngine::simpleAI() const
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int numFields = Settings::instance()->numFields();
    int numAllFields = numFields * numFields;

    return qrand()%numAllFields;
}

void GameEngine::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

BattleField *GameEngine::playerField() const
{
    return _playerField;
}

QString GameEngine::playerFieldName() const
{
    return Config::playerFieldName;
}

BattleField *GameEngine::opponentField() const
{
    return _opponentField;
}

QString GameEngine::opponentFieldName() const
{
    return Config::opponentFieldName;
}

QString GameEngine::gameInformation() const
{
    return _gameInformation;
}

void GameEngine::setGameInformation(const QString &gameInformation)
{
    _gameInformation = gameInformation;

    emit gameInformationChanged(_gameInformation);
}

bool GameEngine::placeShipsRandom(QString battleFieldName)
{    
    BattleField* field = nullptr;

    if(battleFieldName == playerFieldName())
        field = playerField();
    else if(battleFieldName == opponentFieldName())
        field = opponentField();

    if(!field)
        return false;

    field->clear();

    int numFields = Settings::instance()->numFields();
    int numAllFields = numFields*numFields;

    QList<int> numShips = Config::shipsPerBattlefield(numFields);

    for(int ship = 1; ship < FieldData::typeSize; ship++)
    {
        for(int i = 0; i < numShips.at(ship); i++)
        {
            // Seed the random generator with current time
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());

            bool ok;
            int loops = 0;

            do
            {
                if(loops++ < 30) // Try to place ship random
                {
                    ok = field->setShip(qrand()%numFields,
                                        qrand()%numFields,
                                        static_cast<FieldData::ImageType>(ship),
                                        static_cast<FieldData::ImageOrientation>(qrand()%FieldData::orientationSize));
                }
                else // If this takes more than 30 tries, go through every field and try again
                {
                    int startPos = qrand()%numAllFields;
                    for(int ori = 0; ori < FieldData::orientationSize; ori++)
                    {
                        for(int pos = startPos; pos < (numAllFields + startPos); pos++)
                        {
                            ok = field->setShip(pos,
                                                static_cast<FieldData::ImageType>(ship),
                                                static_cast<FieldData::ImageOrientation>(ori));

                            if(ok) break;
                        }
                        if(ok) break;
                    }
                    if(!ok) return false; // Ship cant be placed on any field
                }

            }while(!ok); // Try again if ship could not be placed
        }
    }

    return true;
}

void GameEngine::start()
{
    setIsRunning(true);

    qDebug() << "Game started.";

    setGameInformation("Game started, your turn");
}

void GameEngine::stop()
{
    setIsRunning(false);

    qDebug() << "Game stoped.";
}

bool GameEngine::processTurn(int position)
{
    if(!isRunning())
        return true;

    BattleField* activeField;
    if(isPlayersTurn())
        activeField = opponentField();
    else
        activeField = playerField();

    bool hit = !activeField->fieldIsEmpty(position);
    bool ok = activeField->setFieldHit(position, hit);

    if(!ok)
        return false;

    int shipsLeft = activeField->numberOfShips();
    if(shipsLeft == 0)
    {
        setGameInformation("Game over!");
        delay(1000);
        stop();
    }

    _isPlayersTurn = !_isPlayersTurn;

    if(isPlayersTurn())
    {
        setGameInformation("Your turn!");
    }
    else
    {
        setGameInformation("Opponents turn!");
        delay(3000);
        bool aiok = processTurn(simpleAI());

        if(!aiok)
        {
            // TODO: try again but without random dead lock
        }
    }

    return true;
}

bool GameEngine::isRunning() const
{
    return _isRunning;
}

void GameEngine::setIsRunning(bool isRunning)
{
    _isRunning = isRunning;

    emit isRunningChanged(_isRunning);
}

bool GameEngine::isPlayersTurn() const
{
    return _isPlayersTurn;
}

