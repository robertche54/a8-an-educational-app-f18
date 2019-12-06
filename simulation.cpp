#include "simulation.h"

Simulation::Simulation() : tf(b2Vec2(-10,10),b2Vec2(10,-10),600,500) {
    canvas.create(600, 500);
}

Simulation::~Simulation() {
    for (pair<string, Mob*> namedMob : namedMobs) {
        delete namedMob.second;
    }

    for (Mob* mob : genericMobs) {
        delete mob;
    }
}

void Simulation::setContactListener(b2ContactListener* listener)
{
    world.SetContactListener(listener);
}

/*
 * Setter for box2D gravity.
 */
void Simulation::setGravity(float x, float y) {
    world.SetGravity(b2Vec2(x, y));
}

/*
 * Creates a named Mob that CAN be accessed later.
 * For Mobs that are used to create explosions or have impulses applied to them.
 */
void Simulation::createMob(string filePath, float posX, float posY, float sizeX, float sizeY, string name, b2BodyType type) {
    Mob* newMob = new Mob(filePath, posX, posY, sizeX, sizeY, world, type);
    namedMobs.insert(pair<string, Mob*>(name, newMob));
}

/*
 * Creates a generic Mob that CANNOT be accessed later.
 * For Mobs that are part of the environment and are thrown around by other forces
 * like explosions and collisions with other Mobs.
 */
void Simulation::createMob(string filePath, float posX, float posY, float sizeX, float sizeY, b2BodyType type) {
    Mob* newMob = new Mob(filePath, posX, posY, sizeX, sizeY, world, type);
    genericMobs.push_back(newMob);
}

/*
 * Circle with Name
 */
void Simulation::createMob(string filePath, float posX, float posY, float radius, string name, b2BodyType type) {
    Mob* newMob = new Mob(filePath, posX, posY, radius, world, type);
    namedMobs.insert(pair<string, Mob*>(name, newMob));
}

/*
 * Circle generic
 */
void Simulation::createMob(string filePath, float posX, float posY, float radius, b2BodyType type) {
    Mob* newMob = new Mob(filePath, posX, posY, radius, world, type);
    genericMobs.push_back(newMob);
}

/*
 * polygon with Name
 */
void Simulation::createMob(string filePath, float posX, float posY, vector<b2Vec2> vertices, string name, b2BodyType type) {
    Mob* newMob = new Mob(filePath, posX, posY, vertices, world, type);
    namedMobs.insert(pair<string, Mob*>(name, newMob));
}

/*
 * polygon generic
 */
void Simulation::createMob(string filePath, float posX, float posY, vector<b2Vec2> vertices, b2BodyType type) {
    Mob* newMob = new Mob(filePath, posX, posY, vertices, world, type);
    genericMobs.push_back(newMob);
}

/*
 * Adds an existing Mob to the simulation.
 */
void Simulation::addMob(Mob* mob, string name)
{
    if(name.empty()) genericMobs.push_back(mob);
    else namedMobs.insert(pair<string, Mob*>(name, mob));
}

/*
 * Moves the box2D world forward 1 frame and returns the resulting sfml image for ui display
 */
QImage Simulation::step() {
    canvas.clear(Color(10,10,10,0)); // Makes the background transparent so we can put a background image behind

    if(isRunning) {
        world.Step(1 / 240.0f, 8, 3);

        if(singularity.x != 0.f && singularity.y != 0.f){
            for(pair<string, Mob*> namedMob : namedMobs) {
                applyRadialGravity(namedMob.second, singularity);
            }
            for(Mob* mob : genericMobs) {
                applyRadialGravity(mob, singularity);
            }
        }
    }

    /*
    Updates our named Mobs first because they can cause other Mobs to move
    PLEASE keep this out of the isRunning block so that if simulation is paused,
    the sprites are still being rendered.
    */
    for(pair<string, Mob*> namedMob : namedMobs) {
        namedMob.second->Update(tf);
        canvas.draw(namedMob.second->getSprite());
    }

    for(Mob* mob : genericMobs) {
        mob->Update(tf);
        canvas.draw(mob->getSprite());
    }

    canvas.display();

    Texture canvasTexture = canvas.getTexture();
    Image canvasImage = canvasTexture.copyToImage();
    const uint8_t *canvasPixelsPtr = canvasImage.getPixelsPtr();
    QImage canvasQImage(canvasPixelsPtr, 600, 500,QImage::Format_ARGB32);
    canvasQImage = canvasQImage.rgbSwapped();

    return canvasQImage;
}

/*
 * Creates an explosion at the specified position with each ray having a power of numRays/blastPower
 */
void Simulation::createExplosion(b2Vec2 position, float blastPower, int numRays) {

    vector<b2Body*> rays;

    // Cleans up rays after 1 second so they don't eat up space or colide anymore
    QTimer::singleShot(1000, this, SLOT(removeRays()));

    // Simulates the effect of an explosion by creating a number of
    // particle rays that emit off a point
    for(int i = 0; i < numRays; i++)
    {
        // Converts degrees into radians (which is what Box2D uses)
        float raySeperation = numRays/(360 * degreeToRad);
        float angle = i * raySeperation;
        b2Vec2 rayDir( sinf(angle), cosf(angle) );

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.fixedRotation = true;
        bd.bullet = true; // Treats the rays as bullets (so they dont move through other objects)
        bd.linearDamping = 10; // Apply resistance due to air
        bd.gravityScale = 0; // Make sure rays are not effected by gravity
        bd.position = position;
        bd.linearVelocity = (blastPower * 10) * rayDir; // Scales up power to make effect more noticeable
        b2Body* body = world.CreateBody(&bd);

        rays.push_back(body);

        b2CircleShape circleShape;
        circleShape.m_radius = 0.05f;

        b2FixtureDef fd;
        fd.shape = &circleShape;
        fd.density = 100;
        fd.friction = 0;
        fd.restitution = 0.99f; // High reflection
        fd.filter.groupIndex = -1; // Make rays not collide with each other
        body->CreateFixture( &fd );
    }

    rayQueue.push(rays); // Keeps track of the rays so they can be deleted later
}

/*
 * Applies an impulse to the specified object with magnitude power at degreeAngle from the horizontal
 */
void Simulation::applyImpulse(Mob* movedMob, double degreeAngle, float magnitude) {
    // cmath uses radians
    float radAngle = float(degreeAngle) * degreeToRad;

    // box2D wants 2D vectors, need to find X and Y components of the triangle
    float magX = magnitude * cos(radAngle);
    float magY = magnitude * sin(radAngle);

    // box2D calculates impulse effect based on an object's mass
    // makes magnitude parameter independent of mass
    float mass = movedMob->body->GetMass();
    b2Vec2 impulse = b2Vec2(magX * mass, magY * mass);
    b2Vec2 position = movedMob->body->GetPosition();

    movedMob->body->ApplyLinearImpulse(impulse, position, true);
}

/*
 * Applies an impulse on the specified Mob, moving it towards the source point
 */
void Simulation::applyRadialGravity(Mob* movedMob, b2Vec2 source)
{
    b2Vec2 distance = source - movedMob->body->GetPosition();
    movedMob->body->ApplyLinearImpulse(distance, movedMob->body->GetPosition(), true);
}

/*
 * Cleans up the rays made by the createExplosion method
 */
void Simulation::removeRays() {
    if(rayQueue.empty()) {
        return;
    }

    vector<b2Body*> rays = rayQueue.front();
    for(b2Body* ray : rays) {
        ray->GetWorld()->DestroyBody(ray);
    }
    rayQueue.pop();
}

/*
 * Removes everything from the box2D world that is managed by simulation
 */
void Simulation::clearSimulation() {
    isRunning = false;

    for (pair<string, Mob*> namedMob : namedMobs) {
        delete namedMob.second;
    }

    for (Mob* mob : genericMobs) {
        delete mob;
    }

    namedMobs.clear();
    genericMobs.clear();
}
