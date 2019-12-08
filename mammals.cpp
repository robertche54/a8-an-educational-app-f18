#include "mammals.h"
#include "ui_mammals.h"
#include <stdio.h>

function<float(float)> generateGrowthFunction(float minSize, float maxSize, float growthRate) {
    auto function = [minSize,maxSize,growthRate] (float a) -> float {
        return max(0.0f,maxSize - (growthRate*(maxSize - minSize))/(growthRate-1+a));
    };
    return function;
};


static function<float(float)> plantFunctor = [] (float a) -> float {return a==0 ? 0 : 1;};
static function<float(float)> mammalFunctor = generateGrowthFunction(1.35f, 10, 9);
static function<float(float)> dinoFunctor = generateGrowthFunction(1.3f, 30, 100);

Mammals::Mammals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mammals)
{
    ui->setupUi(this);

    QPixmap map("../A9/forest.jpg");
    ui->bg->setPixmap(map);

    simulation.setGravity(0,0);
    handler = new CreatureCollisionHandler();
    simulation.setContactListener(handler);
    simulation.tf.setBox2dWindow(b2Vec2(-20,20), b2Vec2(20,-20));
    QTimer *timer;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Mammals::physicsUpdate);
    timer->start(1000/60);
    connect(ui->pushButton, &QPushButton::pressed, this, &Mammals::runSimulation);
}
void Mammals::populateWorld(float xRange, float yRange, int plants, int mammals, int dinos) {
    srand(unsigned(int(time(nullptr))));
    while (plants-- > 0) {
        float x = xRange*(random()%20000 - 10000)/10000;
        float y = yRange*(random()%20000 - 10000)/10000;
        addPlant(x,y);
    }
    while (mammals-- > 0) {
        float x = xRange*(random()%20000 - 10000)/10000;
        float y = yRange*(random()%20000 - 10000)/10000;
        addMammal(x,y);
    }
    while (dinos-- > 0) {
        float x = xRange*(random()%20000 - 10000)/10000;
        float y = yRange*(random()%20000 - 10000)/10000;
        addDino(x,y);
    }
}
void Mammals::clearWorld() {
    for (Mob* mob : simulation.genericMobs) {
        dynamic_cast<Creature *>(mob)->SetScore(0);
        dynamic_cast<Creature *>(mob)->SetRadius(0);
    }
}
void Mammals::addMammal(float x, float y) {
    simulation.addMob(new Creature("../A9/mammal.png", x, y, max(1.0f,float(random()%4+2)/3.0f), simulation.world, &mammalFunctor));
}
void Mammals::addDino(float x, float y) {
    simulation.addMob(new Creature("../A9/dinoCreature.png", x, y, max(1.0f,float(random()%8+1)/3.0f), simulation.world, &dinoFunctor));
}
void Mammals::addPlant(float x, float y) {
    simulation.addMob(new Creature("../A9/cabbage.png", x, y, max(1.0f,float(random()%3+2)/3.0f), simulation.world, &plantFunctor));
}


void Mammals::physicsUpdate() {

    QImage newImage = simulation.step();
    ui->simulationLabel->setPixmap(QPixmap::fromImage(newImage));
}


void Mammals::runSimulation() {
    clearWorld();
    simulation.step();
    populateWorld(30,30,ui->PlantsSlider->value(), ui->MammalsSlider->value(), ui->DinosaursSlider->value());
}
Mammals::~Mammals()
{
    delete ui;
}

void Mammals::mousePressEvent(QMouseEvent *event)
{
    // QT coordinates need to be converted to box2D coordinates
    //simulation.createSingularity(event->x(), event->y());
//    simulation.createSingularity(simulation.tf.windowToWorldCoordinates(
//                    event->x() + ui->simulationLabel->x(), event->y() + ui->simulationLabel->y()));
}

void Mammals::paintEvent(QPaintEvent*)
{
    //QImage newImage = simulation.step();
    //ui->worldLabel->setPixmap(QPixmap::fromImage(newImage));
}

void Mammals::closeEvent(QCloseEvent *) {
    emit returnFocus();
}
