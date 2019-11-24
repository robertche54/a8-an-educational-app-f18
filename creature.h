#ifndef CREATURE_H
#define CREATURE_H
#include "mob.h"


class Creature : public Mob
{
protected:
    float size;
public:
    Creature(std::string file, float locationX, float locationY, float sizeX, float sizeY, b2World &world);
    void Update(windowTransform);
};

#endif // CREATURE_H
