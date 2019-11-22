#include "mob.h"

Mob::Mob(std::string file, float locationX, float locationY, float sizeX, float sizeY, b2World &world)
    : position(locationX, locationY),
      size(sizeX,sizeY)
{
    sprite_image.loadFromFile(file);
    sprite_image.setSmooth(true);
    sprite.setTexture(sprite_image);
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(Vector2f(bounds.width/2, bounds.height/2));
    sprite.setPosition(position);

    createBody(world);
}


void Mob::Update(windowTransform transform)
{
    // Updates SFML sprite with b2Body position and rotation
    sprite.setPosition(transform.transformX(body->GetPosition().x), transform.transformY(body->GetPosition().y));
    //printf("%f, %d; %f, %d\n",body->GetPosition().x, transform.transformX(body->GetPosition().x)
    //                 ,body->GetPosition().y, transform.transformY(body->GetPosition().y));
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
    fixtureDef.restitution = 0.25f;
    body->CreateFixture(&fixtureDef);
}

Mob::~Mob() {
    body->GetWorld()->DestroyBody(body);
}

Sprite& Mob::getSprite() {
    return sprite;
}
