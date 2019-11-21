#include "simulation.h"

Simulation::Simulation() {
    canvas.create(330, 250);
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

void Simulation::createMob(string filePath, int x, int y) {
    Mob* newMob = new Mob(filePath, x, y, world);
    genericMobs.push_back(newMob);
}

void Simulation::createMob(string filePath, int x, int y, string name) {
    Mob* newMob = new Mob(filePath, x, y, world);
    namedMobs.insert(pair<string, Mob*>(name, newMob));
}

QImage Simulation::step() {
    canvas.clear();

    world.Step(1 / 60.0f, 8, 3);

    for(pair<string, Mob*> namedMob : namedMobs) {
        namedMob.second->Update();
        canvas.draw(namedMob.second->getSprite());
    }

    for(Mob* mob : genericMobs) {
        mob->Update();
        canvas.draw(mob->getSprite());
    }

    canvas.display();

    Texture canvasTexture = canvas.getTexture();
    Image canvasImage = canvasTexture.copyToImage();
    const uint8_t *canvasPixelsPtr = canvasImage.getPixelsPtr();
    QImage canvasQImage(canvasPixelsPtr, 330, 250,QImage::Format_ARGB32);
    canvasQImage = canvasQImage.rgbSwapped();

    return canvasQImage;
}

void Simulation::createExplosion(Mob* sourceMob) {

}
