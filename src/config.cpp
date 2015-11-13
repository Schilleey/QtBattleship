#include "config.h"


namespace Config
{

int imageOfShip(FieldData::ImageType type, int part)
{
    const static int battleshipParts[5] = {1, 2, 2, 2, 3};
    const static int cruiserParts[4] = {1, 2, 2, 3};
    const static int destoyerParts[3] = {1, 2, 3};
    const static int submarineParts[2] = {1, 3};

    switch(type)
    {
    case FieldData::BattleShip: return battleshipParts[part];
    case FieldData::Cruiser: return cruiserParts[part];
    case FieldData::Destroyer: return destoyerParts[part];
    case FieldData::Submarine: return submarineParts[part];
    default: return 0;
    }
}

QList<int> shipsPerBattlefield(int size)
{
    const static int ships[19][FieldData::typeSize] = {
        { 0, 0, 1, 2, 3 }, // 8
        { 0, 0, 2, 3, 3 }, // 9
        { 0, 1, 2, 3, 4 }, // 10
        { 0, 1, 2, 4, 5 }, // 11
        { 0, 1, 3, 4, 5 }, // 12
        { 0, 1, 3, 4, 6 }, // 13
        { 0, 1, 3, 5, 6 }, // 14
        { 0, 2, 3, 4, 6 }, // 15
        { 0, 2, 4, 4, 6 }, // 16
        { 0, 2, 4, 5, 6 }, // 17
        { 0, 2, 4, 5, 8 }, // 18
        { 0, 3, 4, 4, 6 }, // 19
        { 0, 3, 4, 5, 6 }, // 20
        { 0, 3, 4, 4, 8 }, // 21
        { 0, 3, 4, 5, 6 }, // 22
        { 0, 3, 4, 6, 6 }, // 23
        { 0, 4, 5, 4, 6 }, // 24
        { 0, 4, 5, 5, 6 }, // 25
        { 0, 4, 5, 5, 8 }  // 26
    };

    QList<int> val;
    for(int i = 0; i < FieldData::typeSize; i++)
        val << ships[size-8][i];

    return val;
}

}
