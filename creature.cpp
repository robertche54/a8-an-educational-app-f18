#include "creature.h"
#include <limits>

Creature::Creature(string file, float locationX, float locationY, float score, b2World &wor, function<float(float)>*f) :
    Mob(file, locationX, locationY, (*f)(score), (*f)(score), wor),
    //radius((*f)(score)),
    newRadius((*f)(score)),
    score(score),
    scoreToRadiusFunction(f)
{
    SetRadius(this->radius);
}
bool Creature::Update(windowTransform tf) {
    if (fabs(newRadius - radius) > numeric_limits<float>::min()) {
        SetRadius(newRadius);
    }
    if (this->radius > 0) {
        auto impulse = -this->body->GetWorldCenter();
        if (signbit(impulse.x)) {
            impulse.x = -sqrt(-impulse.x);
        } else {
            impulse.x = sqrt(impulse.x);
        }
        if (signbit(impulse.y)) {
            impulse.y = -sqrt(-impulse.y);
        } else {
            impulse.y = sqrt(impulse.y);
        }
        impulse.x *= this->radius/15;
        impulse.y *= this->radius/15;
        this->body->ApplyLinearImpulse(impulse,this->body->GetWorldCenter(),true);
    }
    this->Mob::Update(tf);
    if (radius == 0) {
        return false;
    }
    return true;
}

void Creature::SetRadius(float rad) {
    if (rad > 31 || rad < 0)
        rad = 0;
    this->radius = rad;
    this->size.x = rad*2;
    this->size.y = rad*2;
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    if (body->GetPosition().IsValid()) {
        myBodyDef.position.Set(body->GetPosition().x, body->GetPosition().y);
        myBodyDef.linearVelocity.Set(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
        myBodyDef.angle = body->GetAngle();
        myBodyDef.angularVelocity = body->GetAngularVelocity();
    }

    b2Body* newBody = this->world->CreateBody(&myBodyDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = max(this->radius,0.1f);

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
