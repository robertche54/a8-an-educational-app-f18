#ifndef SPRITE_H
#define SPRITE_H
#include <SFML/Graphics.hpp>
#include <string>
#include <QImage>

class Sprite
{
public:
    sf::Sprite sprite;
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    QImage image;
    Sprite(std::string, int, int, int, int);
};

#endif // SPRITE_H
