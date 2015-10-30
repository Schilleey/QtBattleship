/**
 * \class BattleField
 *
 * \brief Battlefield related informations
 *
 * This class represents the battlefield of the game. TODO
 *
 */

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <QObject>
#include <QQmlEngine>

#include "settings.h"


class BattleField : public QObject
{
    Q_OBJECT

public:
    BattleField(QObject* parent = nullptr);

public slots:
    void render(); ///< Render the battlefield
};

#endif // BATTLEFIELD_H
