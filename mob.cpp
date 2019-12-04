#include "mob.h"

Mob::Mob(string file, float locationX, float locationY, float sizeX, float sizeY, b2World &world)
    : position(locationX, locationY),
      size(sizeX,sizeY),
      world(&world)
{
    createSprite(file);
    createBody(world);
}

Mob::Mob(string file, float locationX, float locationY, float sizeX, float sizeY, b2World &world, b2BodyType type)
    : position(locationX, locationY),
      size(sizeX,sizeY)
{
    createSprite(file);
    createBody(world, type);
}

Mob::Mob(string file, float locationX, float locationY, float rad, b2World &world, b2BodyType type)
    : position(locationX, locationY),
      world(&world),
      radius(rad)
{
    createSprite(file);
    //pass in 1 for a circle
    createBody(world, type, 1);
}

Mob::Mob(string file, float locationX, float locationY, vector<b2Vec2> ver, b2World &world, b2BodyType type)
    : position(locationX, locationY),
      world(&world)
{
    vertices = ver;
    createSprite(file);
    //pass in 2 for a polygon
    createBody(world, type, 2);
}

bool Mob::Update(windowTransform transform)
{
    // Updates SFML sprite with b2Body position and rotation
    sprite.setPosition(transform.transformX(body->GetPosition().x), transform.transformY(body->GetPosition().y));
    //printf("%f, %d; %f, %d\n",body->GetPosition().x, transform.transformX(body->GetPosition().x)
    //                 ,body->GetPosition().y, transform.transformY(body->GetPosition().y));
    sprite.setRotation(transform.transformAngle(body->GetAngle()));
    auto bounds = sprite.getLocalBounds();
    sprite.setScale(transform.transformWidth(size.x) / bounds.width, transform.transformHeight(size.y) / bounds.height);
    return true;
}

void Mob::createSprite(string file)
{
    sprite_image.loadFromFile(file);
    sprite_image.setSmooth(true);
    sprite.setTexture(sprite_image);
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(Vector2f(bounds.width/2, bounds.height/2));
    sprite.setPosition(position);
}

void Mob::createBody(b2World &world, b2BodyType type)
{
    // Uses the b2World factory to create a new body
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position.Set(position.x, position.y);
    body = world.CreateBody(&bodyDef);

    // Sets body data
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x/2, size.y/2);

    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 1; //(type == b2_dynamicBody) || (type == b2_kinematicBody);
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.2f;
    body->CreateFixture(&fixtureDef);
}

void Mob::createBody(b2World &world, b2BodyType type, int shape)
{
    // Uses the b2World factory to create a new body
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position.Set(position.x, position.y);
    body = world.CreateBody(&bodyDef);

    // Sets body data
    if(shape == 1){//this check means it's a circle.
        b2CircleShape circleShape;
        circleShape.m_p.Set(0, 0); //position, relative to body position
        circleShape.m_radius = radius; //radius
        fixtureDef.shape = &circleShape;
    }
    else{//else it's a polygon
        b2Vec2 polygonVertices[vertices.size()];
        for(unsigned long i = 0; i < vertices.size(); i++){
            polygonVertices[i].Set(vertices[i].x, vertices[i].x);
        }

        b2PolygonShape polygonShape;
        polygonShape.Set(polygonVertices, vertices.size());
        fixtureDef.shape = &polygonShape;
    }

    fixtureDef.density = 1; //(type == b2_dynamicBody) || (type == b2_kinematicBody);
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.2f;
    body->CreateFixture(&fixtureDef);
}

Mob::~Mob() {
    body->GetWorld()->DestroyBody(body);
}

Sprite& Mob::getSprite() {
    return sprite;
}
