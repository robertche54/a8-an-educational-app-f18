#include "mob.h"

Mob::Mob(std::string file, int locationX, int locationY, b2World &world)
    : position(locationX, locationY), origin(locationX, locationY)
{
    sprite_image.loadFromFile(file);
    sprite_image.setSmooth(true);
    sprite.setTexture(sprite_image);
    sprite.setOrigin(origin);
    sprite.setPosition(position);

    createBody(world);
}


void Mob::Update(windowTransform transform)
{
    // Updates SFML sprite with b2Body position and rotation
    sprite.setPosition(transform.transformX(body->GetPosition().x), transform.transformY(body->GetPosition().y));
    sprite.setRotation(transform.transformAngle(body->GetAngle()));
    auto bounds = sprite.getLocalBounds();
    sprite.setScale(transform.transformWidth(size.x) / bounds.width, transform.transformHeight(size.y) / bounds.height);
}

void Mob::createBody(b2World &world, bool dynamic)
{
    // Uses the b2World factory to create a new body
    b2BodyDef bodyDef;
    if(dynamic) bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    body = world.CreateBody(&bodyDef);

    // Sets body data
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x, size.y);

    fixtureDef.shape = &polygonShape;
    fixtureDef.density = dynamic;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}

Mob::~Mob() {
    body->GetWorld()->DestroyBody(body);
}

Sprite& Mob::getSprite() {
    return sprite;
}
