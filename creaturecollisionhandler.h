#ifndef CREATURECOLLISIONHANDLER_H
#define CREATURECOLLISIONHANDLER_H
#include "Box2D/Box2D.h"
#include "creature.h"

class CreatureCollisionHandler : public b2ContactListener
{
public:
    CreatureCollisionHandler();
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};

#endif // CREATURECOLLISIONHANDLER_H
