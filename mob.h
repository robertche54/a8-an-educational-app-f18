#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <QImage>
#include "windowtransform.h"

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Mob : QObject
{
    Q_OBJECT

protected:
    b2World* world;
    const int scale = 1;

    b2FixtureDef fixtureDef;

    void createBody(b2World &world, b2BodyType type = b2_dynamicBody);
    void createBody(b2World &world, b2BodyType type, int shape);
    void createSprite(string);

public:
    b2Body* body;
    Vector2f position;
    Vector2f size;
    float radius;
    Texture sprite_image;
    Sprite sprite;
    vector<b2Vec2> vertices;

    Mob(string, float, float, float, float, b2World &world);
    Mob(string, float, float, float, float, b2World &world, b2BodyType type);
    Mob(string, float locationX, float locationY, float radius, b2World &world, b2BodyType type);
    Mob(string file, float locationX, float locationY, vector<b2Vec2> ver, b2World &world, b2BodyType type);
    virtual ~Mob();
    Sprite &getSprite();
    virtual bool Update(windowTransform);
};

#endif // SPRITE_H
