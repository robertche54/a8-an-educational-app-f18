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

    bool isRunning = true;

public:
    map<string, Mob*> namedMobs;
    b2World world = b2World(gravity);
    windowTransform tf;

    Simulation();
    ~Simulation();
    void setGravity(float, float);
    void createMob(string, int, int, int, int);
    void createMob(string, int, int, int, int, string, b2BodyType);
    void toggleRunning() { isRunning = !isRunning; }
    QImage step();
    void createExplosion(int x, int y, int numRays = 50);
};

#endif // SIMULATION_H
