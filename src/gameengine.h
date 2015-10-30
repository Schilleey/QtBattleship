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


class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine(QObject* parent = nullptr);
};

#endif // GAMEENGINE_H
