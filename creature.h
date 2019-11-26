#ifndef CREATURE_H
#define CREATURE_H
#include "mob.h"


class Creature : public Mob
{
protected:
    float radius;
    float newRadius;
public:
    Creature(std::string file, float locationX, float locationY, float radius, b2World &world);
    void Update(windowTransform);
    void SetRadius(float radius);
    void ScheduleRadiusChange(float radius);
    float GetRadius();
};

#endif // CREATURE_H
