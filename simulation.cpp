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

void Simulation::setGravity(float x, float y) {
    world.SetGravity(b2Vec2(x, y));
}

/*
 * Creates a generic Mob that CANNOT be accessed later.
 * For Mobs that are part of the environment and are thrown around by other forces
 * like explosions and collisions with other Mobs.
 */
void Simulation::createMob(string filePath, float posX, float posY, float sizeX, float sizeY) {
    Mob* newMob = new Mob(filePath, posX, posY, sizeX, sizeY, world);
    genericMobs.push_back(newMob);
}

void Simulation::createMob(string filePath, float posX, float posY, float sizeX, float sizeY, b2BodyType type) {
    Mob* newMob = new Mob(filePath, posX, posY, sizeX, sizeY, world, type);
    genericMobs.push_back(newMob);
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




void Simulation::addMob(Mob* mob, string name)
{
    if(name.empty()) genericMobs.push_back(mob);
    else namedMobs.insert(pair<string, Mob*>(name, mob));
}

QImage Simulation::step() {
    canvas.clear(Color(10,10,10,0));

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

    // Updates our named Mobs first because they can cause other Mobs to move
    // PLEASE keep this out of the isRunning block so that if simulation is paused,
    // the sprites are still being rendered.
    for(pair<string, Mob*> namedMob : namedMobs) {
        namedMob.second->Update(tf);
        canvas.draw(namedMob.second->getSprite());
    }
    map<string, Mob*>::iterator mapit;
    for ( mapit = namedMobs.begin(); mapit != namedMobs.end(); ) {
        auto pair = *mapit;
        Mob *mob = pair.second;
        bool living = mob->Update(tf);
        if(!living) {
            delete mob;
            mapit = namedMobs.erase(mapit);
        }
        else {
            canvas.draw(mob->getSprite());
            ++mapit;
        }
    }

    vector<Mob*>::iterator it;
    for ( it = genericMobs.begin(); it != genericMobs.end(); ) {
        auto mob = *it;
        bool living = mob->Update(tf);
        if(!living) {
            delete * it;
            it = genericMobs.erase(it);
        }
        else {
            canvas.draw(mob->getSprite());
            ++it;
        }
    }

    canvas.display();

    Texture canvasTexture = canvas.getTexture();
    Image canvasImage = canvasTexture.copyToImage();
    const uint8_t *canvasPixelsPtr = canvasImage.getPixelsPtr();
    QImage canvasQImage(canvasPixelsPtr, 600, 500,QImage::Format_ARGB32);
    canvasQImage = canvasQImage.rgbSwapped();

    return canvasQImage;
}

void Simulation::createExplosion(b2Vec2 position, float blastPower, int numRays) {

    vector<b2Body*> rays;

    // Cleans up rays after they run out of momentum (after 5 seconds)
    QTimer::singleShot(5000, this, SLOT(removeRays()));

    // Simulates the effect of an explosion by creating a number of
    // particle rays that emit off a point
    for(int i = 0; i < numRays; i++)
    {
        // Converts degrees into radians (which is what Box2D uses)
        float raySeperation = numRays/(360 * degreeToRad);
        float angle = i * raySeperation;
        //float angle = static_cast<float>(((i/numRays) * i * M_PI ) / 180);
        b2Vec2 rayDir( sinf(angle), cosf(angle) );

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.fixedRotation = true;
        bd.bullet = true; // Treats the rays as bullets (so they dont tunnel)
        bd.linearDamping = 10; // Apply resistance due to air
        bd.gravityScale = 0; // Make sure rays are not effected by gravity
        bd.position = position;
        bd.linearVelocity = (blastPower * 10) * rayDir;
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

    rayQueue.push(rays);
}

void Simulation::applyImpulse(Mob* movedMob, double degreeAngle, float magnitude) {
    // cmath uses radians
    float radAngle = float(degreeAngle) * degreeToRad;

    // box2D wants 2D vectors
    float magX = magnitude * cos(radAngle);
    float magY = magnitude * sin(radAngle);

    // box2D calculates impulse based on an object's mass
    float mass = movedMob->body->GetMass();
    b2Vec2 impulse = b2Vec2(magX * mass, magY * mass);
    b2Vec2 position = movedMob->body->GetPosition();

    movedMob->body->ApplyLinearImpulse(impulse, position, true);
}

void Simulation::applyRadialGravity(Mob* movedMob, b2Vec2 source)
{
    b2Vec2 distance = source - movedMob->body->GetPosition();
    movedMob->body->ApplyLinearImpulse(distance, movedMob->body->GetPosition(), true);
}

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
