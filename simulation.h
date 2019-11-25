#ifndef SIMULATION_H
#define SIMULATION_H

#include <map>
#include "mob.h"

using namespace std;

class Simulation
{

private:
    sf::RenderTexture canvas;
    b2Vec2 gravity = b2Vec2(0.0, -9.81f);
    vector<Mob*> genericMobs;

public:
    map<string, Mob*> namedMobs;
    b2World world = b2World(gravity);
    windowTransform tf;

    Simulation();
    ~Simulation();
    void setGravity(float, float);
    void createMob(string, float, float, float, float);
    void createMob(string, float, float, float, float, string);
    QImage step();
    void createExplosion(Mob*);
};

#endif // SIMULATION_H
