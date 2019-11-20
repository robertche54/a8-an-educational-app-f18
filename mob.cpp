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


void Mob::Update()
{
    // Updates SFML sprite with b2Body position and rotation
    sprite.setPosition(body->GetPosition().x * scale, body->GetPosition().y * scale);
    sprite.setRotation(body->GetAngle() * 180/b2_pi);
}

void Mob::createBody(b2World &world, bool dynamic)
{
    // Uses the b2World factory to create a new body
    b2BodyDef bodyDef;
    if(dynamic) bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x/scale, position.y/scale);
    body = world.CreateBody(&bodyDef);

    // Sets body data
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(sprite.getLocalBounds().width/2/scale, sprite.getLocalBounds().height/2/scale);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = dynamic;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}

sf::Sprite& Mob::getSprite() {
    return sprite;
}

Mob::~Mob() {
    body->GetWorld()->DestroyBody(body);
}
