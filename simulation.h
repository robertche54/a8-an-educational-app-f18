#ifndef SIMULATION_H
#define SIMULATION_H

#include <QTimer>
#include <QVector>
#include <map>
#include <cmath>
#include <queue>

#include "mob.h"

using namespace std;

class Simulation : QObject
{
    Q_OBJECT

private:
    sf::RenderTexture canvas;
    b2Vec2 gravity = b2Vec2(0.0, -9.81f);
    vector<Mob*> genericMobs;
    queue<vector<b2Body*>> rayQueue;

    bool isRunning = true;
    const float degreeToRad = float(M_PI/180);

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
    void createExplosion(b2Vec2 position, int blastPower = 20, int numRays = 50);
    void applyImpulse(Mob*, double, float);

public slots:
    void removeRays();
};

#endif // SIMULATION_H
