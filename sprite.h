#ifndef SPRITE_H
#define SPRITE_H
#include <SFML/Graphics.hpp>
#include <string>
class Sprite
{
public:
    sf::Sprite sprite;
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    Sprite(std::string, int, int, int, int);

};

#endif // SPRITE_H
