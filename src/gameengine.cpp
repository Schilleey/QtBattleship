#include "gameengine.h"

GameEngine::GameEngine(QObject *parent)
    : QObject(parent), _battlefield(nullptr)
{
    if(!_battlefield)
        _battlefield = new BattleField(this);
}

BattleField *GameEngine::battlefield() const
{
    return _battlefield;
}

