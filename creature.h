#ifndef CREATURE_H
#define CREATURE_H
#include "mob.h"


class Creature : public Mob
{
protected:
    float radius;
    float newRadius;
    float score;
    float (*scoreToRadiusFunction)(float);
public:
    Creature(std::string file, float locationX, float locationY, float radius, b2World &world, float (*scoreToRadius)(float));
    bool Update(windowTransform);
    void SetRadius(float radius);
    void SetScore(float score);
    void ScheduleRadiusChange(float radius);
    float GetRadius();
    float GetScore();
};

#endif // CREATURE_H
