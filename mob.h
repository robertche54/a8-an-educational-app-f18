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
    b2Body* body;
    b2FixtureDef fixtureDef;

    void createBody(b2World &world, bool dynamic = true);

public:
    Vector2f position;
    Vector2f size;
   // sf::RenderTexture texture; // belongs to window
    Texture sprite_image;
    Sprite sprite;

    Mob(string, int, int, int, int, b2World &world);
    ~Mob();
    Sprite &getSprite();
    void Update(windowTransform);
};

#endif // SPRITE_H
