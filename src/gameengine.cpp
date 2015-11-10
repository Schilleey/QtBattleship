#include <QTime>

#include "gameengine.h"
#include "settings.h"
#include "fielddata.h"


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

void GameEngine::placeShipsRandom()
{
    if(!_battlefield)
        return;

    _battlefield->clear();

    int numFields = Settings::instance()->numFields();

    for(int i = 0; i < 10; i++)
    {
        // Seed the random generator with current time
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());

        bool ok = _battlefield->setShip(qrand()%numFields,
                                        qrand()%numFields,
                                        static_cast<FieldData::ImageType>(qrand()%FieldData::typeSize),
                                        static_cast<FieldData::ImageOrientation>(qrand()%FieldData::orientationSize));

        if(!ok) i--; // Try again if ship could not be placed
    }
}

