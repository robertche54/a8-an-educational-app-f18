#include "creature.h"
#include <limits>

Creature::Creature(string file, float locationX, float locationY, float score, b2World &wor, float (*f)(float)) :
    Mob(file, locationX, locationY, (*f)(score), (*f)(score), wor),
    radius((*f)(score)),
    newRadius((*f)(score)),
    score(score),
    scoreToRadiusFunction(f)
{
    SetRadius(radius);
}
bool Creature::Update(windowTransform tf) {
    if (fabs(newRadius - radius) > numeric_limits<float>::min()) {
        SetRadius(newRadius);
    }
    this->Mob::Update(tf);
    if (radius == 0) {
        return false;
    }
    return true;
}

void Creature::SetRadius(float radius) {
    this->radius = radius;
    this->size.x = radius;
    this->size.y = radius;
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(body->GetPosition().x, body->GetPosition().y);
    myBodyDef.linearVelocity.Set(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
    myBodyDef.angle = body->GetAngle();
    myBodyDef.angularVelocity = body->GetAngularVelocity();

    b2Body* newBody = this->world->CreateBody(&myBodyDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = max(radius,0.01f);

    this->fixtureDef.shape = &circleShape;

    newBody->CreateFixture(&(this->fixtureDef));
    newBody->SetUserData(this);

    world->DestroyBody(body);
    body = newBody;
}

void Creature::ScheduleRadiusChange(float nradius) {
    newRadius = nradius;
}
void Creature::SetScore(float score) {
    this->score = score;
    this->ScheduleRadiusChange((*scoreToRadiusFunction)(score));
}
float Creature::GetRadius() {
    return this->newRadius;
}
float Creature::GetScore() {
    return this->score;
}
