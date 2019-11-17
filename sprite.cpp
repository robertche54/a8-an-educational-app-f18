#include "sprite.h"

Sprite::Sprite(std::string file, int x, int y, int locationX, int locationY, b2World world)
    : position(locationX, locationY)
{
    texture.create(unsigned(x), unsigned(y));
    sprite_texture.loadFromFile(file);
    sprite_texture.setSmooth(true);
    sprite.setTexture(sprite_texture);
    sprite.setOrigin(position);
    sprite.setPosition(position);
    texture.draw(sprite);
    texture.display();

    createBody(world);
}

void Sprite::Update()
{
    // Updates SFML sprite with b2Body position and rotation
    sprite.setPosition(body->GetPosition().x * scale, body->GetPosition().y * scale);
    sprite.setRotation(body->GetAngle() * 180/b2_pi);
}

void Sprite::createBody(b2World world, bool dynamic)
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
