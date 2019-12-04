#ifndef CREATURE_H
#define CREATURE_H
#include "mob.h"
#include <functional>


class Creature : public Mob
{
protected:
    //float radius;
    float newRadius;
    float score;
    function<float(float)>*scoreToRadiusFunction;
public:
    explicit Creature(std::string file, float locationX, float locationY, float radius, b2World &world, std::function<float(float)>*);
    bool Update(windowTransform);
    void SetRadius(float radius);
    void SetScore(float score);
    void ScheduleRadiusChange(float radius);
    float GetRadius();
    float GetScore();
};

#endif // CREATURE_H
