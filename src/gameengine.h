/**
 * \class GameEngine
 *
 * \brief Logic implementation
 *
 * This class implements all the game logic. TODO
 *
 */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

#include "battlefield.h"


class GameEngine : public QObject
{
    Q_OBJECT

    Q_PROPERTY(BattleField* battlefield READ battlefield NOTIFY battleFieldChanged)

public:
    GameEngine(QObject* parent = nullptr);

    BattleField* battlefield() const;

signals:
    battleFieldChanged(BattleField* battlefield);

private:
    BattleField* _battlefield;
};

#endif // GAMEENGINE_H
