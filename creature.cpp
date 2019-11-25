#include "creature.h"

Creature::Creature(std::string file, float locationX, float locationY, float sizeX, float sizeY, b2World &world) :
    Mob(file, locationX, locationY, sizeX, sizeY, world)
{
    fixtureDef.userData = reinterpret_cast<void*>(1);
}

void Creature::Update(windowTransform tf) {
    this->Mob::Update(tf);
}

void Creature::SetRadius(float radius) {
    size = radius;
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

float Creature::GetRadius() {
    return size;
}
