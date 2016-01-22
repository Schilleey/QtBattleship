/**
 * \class AI
 *
 * \brief Artificial intelligence of the opponent
 *
 * This class represents the "brain" of the opponent (computer).
 * There are two difficulties: simple and better
 *
 */

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

    BattleField* _field;      ///< Operating battlefield
    bool _lastHit;            ///< Indicates the last turn was a hit
    Direction _lastDirection; ///< Last direction
    bool _shipActive;         ///< Indicates if a ship was hit but the ship is not sunken
    bool _shipSunken;         ///< Indicates if the ship is now sunken
    int _currentHitsOnShip;   ///< Number of hits on the active ship
    int _shipFirstHit;        ///< First position a ship was hit
    QList<int> _alreadyTried; ///< Holds the indices of the already tried fields
};

#endif // AI_H
