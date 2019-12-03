#include "mammals.h"
#include "ui_mammals.h"
#include <QTimer>

auto plantFunctor = [] (float a) -> float {return a==0 ? 0 : 1;};
auto mammalFunctor = [] (float a) -> float {return sqrt(30 - (5*21)/(4+a));};
auto dinoFunctor = [] (float a) -> float {return sqrt(100 - (10*96)/(9+a));};

Mammals::Mammals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mammals)
{
    ui->setupUi(this);
    simulation.setGravity(0,0);
    handler = new CreatureCollisionHandler();
    simulation.setContactListener(handler);
    populateWorld(15,15,200,5,5);
    QTimer *timer;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Mammals::physicsUpdate);
    timer->start(1000/60);
}
void Mammals::populateWorld(float xRange, float yRange, int plants, int mammals, int dinos) {
    while (plants-- > 0) {
        float x = xRange*(random()%20000 - 10000)/10000;
        float y = yRange*(random()%20000 - 10000)/10000;
        addPlant(x,y);
    }
    while (mammals-- > 0) {
        float x = xRange*(random()%20000 - 10000)/10000;
        float y = yRange*(random()%20000 - 10000)/10000;
        //addMammal(x,y);
    }
    while (dinos-- > 0) {
        float x = xRange*(random()%20000 - 10000)/10000;
        float y = yRange*(random()%20000 - 10000)/10000;
        //addDino(x,y);
    }
}
void Mammals::addMammal(float x, float y) {
    simulation.addMob(new Creature("../A9/mammal.png", x, y, 1, simulation.world, mammalFunctor));
}
void Mammals::addDino(float x, float y) {
    simulation.addMob(new Creature("../A9/otherimage.png", x, y, 1, simulation.world, dinoFunctor));
}
void Mammals::addPlant(float x, float y) {
    simulation.addMob(new Creature("../A9/cabbage.png", x, y, 1, simulation.world, plantFunctor));
}


void Mammals::physicsUpdate() {

    QImage newImage = simulation.step();
    ui->worldLabel->setPixmap(QPixmap::fromImage(newImage));
}

Mammals::~Mammals()
{
    delete ui;
}

void Mammals::paintEvent(QPaintEvent*)
{
    //QImage newImage = simulation.step();
    //ui->worldLabel->setPixmap(QPixmap::fromImage(newImage));
}
