#ifndef CONFIG_H
#define CONFIG_H

#include <QList>
#include "fielddata.h"


namespace Config
{

static const int lengthOfShip[FieldData::typeSize] = {0, 5, 4, 3, 2};

QList<int> shipsPerBattlefield(int size);
int imageOfShip(FieldData::ImageType type, int part);

}

#endif // CONFIG_H

