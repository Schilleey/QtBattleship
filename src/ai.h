#ifndef AI_H
#define AI_H

#include <QObject>
#include <QList>

class BattleField;


class AI : public QObject
{
    Q_OBJECT

private:
    enum Direction
    {
        UP = 0,
        RIGHT,
        DOWN,
        LEFT
    };

public:
    explicit AI(QObject* parent, BattleField* field);

    int simpleMemory() const;
    int betterMemory();

    bool lastHit() const;
    void setLastHit(bool lastHit);

    void reset();

    bool shipActive() const;
    void setShipActive(bool shipActive);

    AI::Direction lastDirection() const;
    void setLastDirection(const AI::Direction &lastDirection);

private:
    int positionInDirection(Direction direction, const int lastPos) const;
    Direction oppositeDirection(Direction direction) const;
    Direction randomDirection() const;
    Direction nextDirection(Direction direction) const;

    BattleField* _field;
    bool _lastHit;
    Direction _lastDirection;
    bool _shipActive;
    bool _shipSunken;
    int _currentHitsOnShip;
    int _shipFirstHit;
    QList<int> _alreadyTried;
};

#endif // AI_H
