#ifndef CONFIG_H
#define CONFIG_H

#include <QList>
#include <QString>
#include "fielddata.h"


namespace Config
{

static const int lengthOfShip[FieldData::typeSize] = {0, 5, 4, 3, 2};
static const QString playerFieldName = QString("Player");
static const QString opponentFieldName = QString("Opponent");

QList<int> shipsPerBattlefield(int size);
int imageOfShip(FieldData::ImageType type, int part);

}

#endif // CONFIG_H

