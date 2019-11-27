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
                printf("A vore B\n");
                cA->SetScore(cA->GetScore() + cB->GetScore());
                cB->ScheduleRadiusChange(0);
            } else if (cB->GetRadius() > cA->GetRadius()*1.3f) {
                printf("B vore A\n");
                cB->SetScore(cA->GetScore() + cB->GetScore());
                cA->ScheduleRadiusChange(0);
            }

        }
    }
    fflush(stdout);
}

void CreatureCollisionHandler::EndContact(b2Contact* contact) {

}
