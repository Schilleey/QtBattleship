#ifndef AI_H
#define AI_H

#include <QObject>

class BattleField;


class AI : public QObject
{
    Q_OBJECT

public:
    explicit AI(QObject* parent, BattleField* field);

    int simpleMemory() const;
    int betterMemory() const;

    bool lastHit() const;
    void setLastHit(bool lastHit);

private:
    BattleField* _field;
    bool _lastHit;
};

#endif // AI_H
