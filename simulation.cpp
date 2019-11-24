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
        world.Step(1 / 60.0f, 8, 3);

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

void Simulation::createExplosion(Mob* sourceMob) {

}
