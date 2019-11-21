#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <QImage>

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Mob
{

private:
    b2Body* body;

    const int scale = 1;

    void createBody(b2World &world, bool dynamic = true);

public:
    Vector2f position;
    Vector2f origin;
    Vector2f size;
    Texture sprite_image;
    Sprite sprite;

    Mob(string, int, int, b2World &world);
    ~Mob() { body->GetWorld()->DestroyBody(body); }
    Sprite &getSprite() { return sprite; }
    void Update();
};

#endif // SPRITE_H
