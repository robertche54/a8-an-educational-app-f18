#include "creaturecollisionhandler.h"
#include "creature.h"

CreatureCollisionHandler::CreatureCollisionHandler()
{

}

void CreatureCollisionHandler::BeginContact(b2Contact* contact) {
    //Get userdata from the two bodies involved in the collision
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

    if (bodyAUserData != nullptr && bodyBUserData != nullptr) {
        Creature* cA = reinterpret_cast<Creature*>(bodyAUserData);
        Creature* cB = reinterpret_cast<Creature*>(bodyBUserData);
        if (cA->GetRadius() > 0 && cB->GetRadius() > 0) {
            if (cA->GetRadius() > cB->GetRadius()*1.3f) {
                cA->ScheduleRadiusChange(cA->GetRadius() + cB->GetRadius());
                cB->ScheduleRadiusChange(0);
            } else if (cB->GetRadius() > cA->GetRadius()*1.3f) {
                cB->ScheduleRadiusChange(cB->GetRadius() + cA->GetRadius());
                cA->ScheduleRadiusChange(0);
            }

        }
    }

}

void CreatureCollisionHandler::EndContact(b2Contact* contact) {

}
