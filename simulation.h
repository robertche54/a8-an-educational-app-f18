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
    queue<vector<b2Body*>> rayQueue;
    b2Vec2 singularity = b2Vec2(0, 0);

    const float degreeToRad = float(M_PI/180);

public:
    bool isRunning = true;
    vector<Mob*> genericMobs;
    map<string, Mob*> namedMobs;
    b2World world = b2World(gravity);
    windowTransform tf;

    Simulation();
    ~Simulation();
    QImage step();

    void setContactListener(b2ContactListener*);
    void setGravity(float, float);

    void toggleRunning() { isRunning = !isRunning; }
    void createSingularity(float x, float y) { singularity.Set(x, y); }
    void createSingularity(b2Vec2 pos) { singularity = pos; }

    void createMob(string, float, float, float, float);
    void createMob(string filePath, float posX, float posY, float sizeX, float sizeY, b2BodyType type);
    void createMob(string, float, float, float, float, string, b2BodyType);
    void createMob(string, float, float, float, string, b2BodyType);
    void createMob(string, float, float, float, b2BodyType);
    void createMob(string, float, float, vector<b2Vec2>, string, b2BodyType);
    void createMob(string, float, float, vector<b2Vec2>, b2BodyType);

    void createExplosion(b2Vec2 position, float blastPower = 20, int numRays = 50);
    void addMob(Mob*, string name = "");

    void applyImpulse(Mob*, double, float);
    void applyRadialGravity(Mob*, b2Vec2);

    void clearSimulation();

public slots:
    void removeRays();
};

#endif // SIMULATION_H
