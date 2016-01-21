#include <QTime>
#include <QDebug>

#include "ai.h"
#include "settings.h"
#include "battlefield.h"


AI::AI(QObject *parent, BattleField *field)
    : QObject(parent), _field(field)
{
    reset();

    connect(_field, &BattleField::numberOfShipsChanged, [&](){
        if(shipActive())
        {
            setShipActive(false);
            _shipSunken = true;
            _currentHitsOnShip = 0;
            _shipFirstHit = -1;
            setLastDirection(randomDirection());
        }
    });
}

int AI::simpleMemory() const
{
    if(!_field)
        return -1;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int numFields = Settings::instance()->numFields();
    int numAllFields = numFields * numFields;

    bool ok = false;
    int position, loops = 0;

    do
    {
        position = qrand()%numAllFields;

        if(loops++ < 30)
            ok = !_field->getFieldData(position)->isTried();
        else
        {
            for(int pos = position; pos < (numAllFields + position); pos++)
            {
                ok = !_field->getFieldData(pos)->isTried();
                if(ok)
                {
                    position = pos;
                    break;
                }
            }

            if(!ok) return -1; // Ship cant be placed on any field
        }

    }while(!ok);

    return position;
}

int AI::betterMemory()
{
    int position = 0;
    int nextPos = 0;
    int lastPos = 0;
    bool ok = false;
    Direction lastDir = AI::UP;
    bool keepPosAndDir = false;

    do
    {
        if(shipActive())
        {
            if(!keepPosAndDir)
            {
                lastPos = _alreadyTried.last();
                lastDir = lastDirection();
                keepPosAndDir = false;
            }

            if(lastHit())
            {
                nextPos = positionInDirection(lastDir, lastPos);
            }
            else
            {
                if(_currentHitsOnShip >= 2)
                {
                    if(!keepPosAndDir)
                        lastDir = oppositeDirection(lastDir);
                    nextPos = positionInDirection(lastDir, _shipFirstHit);
                }
                else
                {
                    if(!keepPosAndDir)
                        lastDir = nextDirection(lastDir);
                    nextPos = positionInDirection(lastDir, _shipFirstHit);
                }
            }

            if(nextPos < 0)
            {
                if(_currentHitsOnShip >= 2)
                    lastDir = oppositeDirection(lastDir);
                else
                    lastDir = nextDirection(lastDir);

                lastPos = _shipFirstHit;
                keepPosAndDir = true;
                continue;
            }

            if(_alreadyTried.contains(nextPos))
            {
                lastDir = nextDirection(lastDir);
                lastPos = _shipFirstHit;
                keepPosAndDir = true;
                continue;
            }
            else
            {
                ok = true;
            }

            position = nextPos;
        }
        else
        {
            position = simpleMemory();
            _shipSunken = false;
            ok = true;
        }

    }while(!ok);

    _alreadyTried.append(position);
    setLastDirection(lastDir);

    return position;
}

bool AI::lastHit() const
{
    return _lastHit;
}

void AI::setLastHit(bool lastHit)
{   
    _lastHit = lastHit;

    if(_lastHit)
    {
        Settings::Difficulty diff = Settings::instance()->difficulty();
        if(!_shipSunken && (diff == Settings::Better))
        {
            if((_currentHitsOnShip == 0) && (_shipFirstHit < 0))
                _shipFirstHit = _alreadyTried.last();
            _currentHitsOnShip++;
            setShipActive(true);
        }
        qDebug() << "Got a hit...";
    }
}

bool AI::shipActive() const
{
    return _shipActive;
}

void AI::setShipActive(bool shipActive)
{
    _shipActive = shipActive;
}

AI::Direction AI::lastDirection() const
{
    return _lastDirection;
}

void AI::setLastDirection(const AI::Direction &lastDirection)
{
    _lastDirection = lastDirection;
}

int AI::positionInDirection(AI::Direction direction, const int lastPos) const
{
    if(direction == UP)
        return _field->getUpPos(lastPos);
    else if(direction == DOWN)
        return _field->getDownPos(lastPos);
    else if(direction == LEFT)
        return _field->getLeftPos(lastPos);
    else if(direction == RIGHT)
        return _field->getRightPos(lastPos);
    else
        return -1;
}

AI::Direction AI::oppositeDirection(AI::Direction direction) const
{
    if(direction == UP)
        return DOWN;
    else if(direction == DOWN)
        return UP;
    else if(direction == LEFT)
        return RIGHT;
    else if(direction == RIGHT)
        return LEFT;
    else
        return UP;
}

AI::Direction AI::randomDirection() const
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    return (AI::Direction) (qrand() % 4);
}

AI::Direction AI::nextDirection(Direction direction) const
{
    return (AI::Direction) ((direction+1) % 4);
}

void AI::reset()
{
    _alreadyTried.clear();
    _lastHit = false;
    _shipActive = false;
    _shipSunken = false;
    _lastDirection = randomDirection();
    _currentHitsOnShip = 0;
    _shipFirstHit = -1;
}
