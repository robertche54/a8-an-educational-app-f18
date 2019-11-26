#include "creature.h"
#include <limits>

Creature::Creature(std::string file, float locationX, float locationY, float radius, b2World &wor) :
    Mob(file, locationX, locationY, radius, radius, wor),
    radius(radius),
    newRadius(radius)
{

    fixtureDef.userData = reinterpret_cast<void*>(this);
}
void Creature::Update(windowTransform tf) {
    if (fabs(newRadius - radius) < numeric_limits<float>::min()) {
        SetRadius(newRadius);
    }
    this->Mob::Update(tf);
}

void Creature::SetRadius(float radius) {
    this->radius = radius;
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(body->GetPosition().x, body->GetPosition().y);

    b2Body* newBody = this->world->CreateBody(&myBodyDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = radius;

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape;
    newBody->CreateFixture(&myFixtureDef);

    world->DestroyBody(body);
    body = newBody;
}

void Creature::ScheduleRadiusChange(float radius) {
    newRadius = radius;
}
float Creature::GetRadius() {
    return this->newRadius;
}
