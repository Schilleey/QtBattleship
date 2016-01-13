#include <QTime>
#include <QDebug>

#include "ai.h"
#include "settings.h"
#include "battlefield.h"


AI::AI(QObject *parent, BattleField *field)
    : QObject(parent), _field(field), _lastHit(false)
{
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

int AI::betterMemory() const
{
    return 0;
}

bool AI::lastHit() const
{
    return _lastHit;
}

void AI::setLastHit(bool lastHit)
{
    _lastHit = lastHit;

    if(_lastHit)
        qDebug() << "Got a hit... LOOOL xD";
}

