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
    void createBody(b2World &world, bool dynamic = true);

public:
    b2Body* body;
    b2FixtureDef fixtureDef;
    Vector2f position;
    Vector2f size;
    Texture sprite_image;
    Sprite sprite;

    Mob(string, float, float, float, float, b2World &world);
    ~Mob();
    Sprite &getSprite();
    void Update(windowTransform);
};

#endif // SPRITE_H
