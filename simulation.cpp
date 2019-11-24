#include "simulation.h"

Simulation::Simulation() : tf(b2Vec2(-10,10),b2Vec2(10,-10),320,180) {
    canvas.create(320, 180);
}

Simulation::~Simulation() {
    for (pair<string, Mob*> namedMob : namedMobs) {
        delete namedMob.second;
    }

    for (Mob* mob : genericMobs) {
        delete mob;
    }
}

void Simulation::setGravity(float x, float y) {
    world.SetGravity(b2Vec2(x, y));
}

void Simulation::createMob(string filePath, int posX, int posY, int sizeX, int sizeY) {
    Mob* newMob = new Mob(filePath, posX, posY, sizeX, sizeY, world);
    genericMobs.push_back(newMob);
}

void Simulation::createMob(string filePath, int posX, int posY, int sizeX,
                           int sizeY, string name, b2BodyType type) {
    Mob* newMob = new Mob(filePath, posX, posY, sizeX, sizeY, world, type);
    namedMobs.insert(pair<string, Mob*>(name, newMob));
}

QImage Simulation::step() {
    canvas.clear();

    if(isRunning)
        world.Step(1 / 240.0f, 8, 3);

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
    QImage canvasQImage(canvasPixelsPtr, 320, 180,QImage::Format_ARGB32);
    canvasQImage = canvasQImage.rgbSwapped();

    return canvasQImage;
}

void Simulation::createExplosion(int x, int y, int blastPower, int numRays) {

    vector<b2Body*> rays;

    // Cleans up rays after they run out of momentum (after 5 seconds)
    QTimer::singleShot(500, this, SLOT([] () => {
        for(b2Body* ray : rays)
            ray->GetWorld()->DestroyBody(ray);
    }));

    // Simulates the effect of an explosion by creating a number of
    // particle rays that emit off a point
    for(int i = 0; i < numRays; i++)
    {
        // Converts degrees into radians (which is what Box2D uses)
        float angle = static_cast<float>(((i/numRays) * i * M_PI ) / 180);
        b2Vec2 rayDir( sinf(angle), cosf(angle) );

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.fixedRotation = true;
        bd.bullet = true; // Treats the rays as bullets (so they dont tunnel)
        bd.linearDamping = 10; // Apply resistance due to air
        bd.gravityScale = 0; // Make sure rays are not effected by gravity
        bd.position = b2Vec2(x, y);
        bd.linearVelocity = blastPower * rayDir;
        b2Body* body = world.CreateBody(&bd);

        rays.push_back(body);

        b2CircleShape circleShape;
        circleShape.m_radius = 0.05f;

        b2FixtureDef fd;
        fd.shape = &circleShape;
        fd.density = 60/numRays;
        fd.friction = 0;
        fd.restitution = 0.99f; // High reflection
        fd.filter.groupIndex = -1; // Make rays not collide with each other
        body->CreateFixture( &fd );
    }
}
