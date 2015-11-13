#include <QTime>
#include <QDebug>

#include "gameengine.h"
#include "config.h"
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

bool GameEngine::placeShipsRandom()
{
    if(!_battlefield)
        return false;

    _battlefield->clear();

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
                    ok = _battlefield->setShip(qrand()%numFields,
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
                            ok = _battlefield->setShip(pos,
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

