#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <QImage>
#include "windowtransform.h"

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Mob
{

private:
    const int scale = 1;

    b2Body* body;
    b2FixtureDef fixtureDef;

    void createBody(b2World &world, b2BodyType type = b2_dynamicBody);
    void createSprite(string);

public:
    Vector2f position;
    Vector2f size;
    Texture sprite_image;
    Sprite sprite;

    Mob(string, float, float, float, float, b2World&);
    Mob(string, float, float, float, float, b2World&, b2BodyType type);
    ~Mob() { body->GetWorld()->DestroyBody(body); }
    Sprite &getSprite() { return sprite; }
    void Update(windowTransform);
};

#endif // SPRITE_H
