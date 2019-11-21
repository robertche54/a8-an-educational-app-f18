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
    b2World world = b2World(gravity);
    vector<Mob*> genericMobs;

public:
    map<string, Mob*> namedMobs;

    Simulation();
    ~Simulation();
    void setGravity(float, float);
    void createMob(string, int, int);
    void createMob(string, int, int, string);
    QImage step();
    void createExplosion(Mob*);
};

#endif // SIMULATION_H
