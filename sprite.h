#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <QImage>

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

using namespace std;

class Sprite
{

private:
    b2Body* body;

    const int scale = 1;

    void createBody(b2World &world, bool dynamic = true);

public:
    sf::Vector2f position;
    sf::Vector2f origin;
   // sf::RenderTexture texture; // belongs to window
    sf::Texture sprite_image;
    sf::Sprite sprite;

    Sprite(string, int, int, b2World &world);
    ~Sprite() { body->GetWorld()->DestroyBody(body); }
    sf::Sprite &getSprite() { return sprite; }
    void Update();
};

#endif // SPRITE_H
