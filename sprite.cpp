#include "sprite.h"

Sprite::Sprite(std::string file, int x, int y, int locationX, int locationY){
    texture.create(x,y);
    sprite_texture.loadFromFile(file);
    sprite_texture.setSmooth(true);
    sprite.setTexture(sprite_texture);
    sprite.setOrigin(locationX, locationY);
    sprite.setPosition(locationX, locationY);
}
