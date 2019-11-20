#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <QImage>

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

using namespace std;

class Mob
{

private:
    b2Body* body;

    const int scale = 1;

    void createBody(b2World &world, bool dynamic = true);

public:
    sf::Vector2f position;
    sf::Vector2f origin;
    sf::Vector2f size;
   // sf::RenderTexture texture; // belongs to window
    sf::Texture sprite_image;
    sf::Sprite sprite;

    Mob(string, int, int, b2World &world);
    ~Mob();
    sf::Sprite &getSprite();
    void Update();
};

#endif // SPRITE_H
