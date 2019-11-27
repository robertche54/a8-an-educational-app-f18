#include "mammals.h"
#include "ui_mammals.h"
#include <QTimer>

Mammals::Mammals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mammals)
{
    ui->setupUi(this);
    simulation.setGravity(0,0);
    handler = new CreatureCollisionHandler();
    simulation.setContactListener(handler);

    auto plantFunctor = [] (float a) -> float {return a==0 ? 0 : 1;};
    auto mammalFunctor = [] (float a) -> float {return sqrt(30 - (5*21)/(4+a));};
    auto dinoFunctor = [] (float a) -> float {return sqrt(100 - (10*96)/(9+a));};
    Creature* cabbage = new Creature("../A9/mammal.png", 5, 5, 1, simulation.world, mammalFunctor);
    simulation.addMob(cabbage);
    Creature* cabbage2 = new Creature("../A9/cabbage.png", -10, 5, 1, simulation.world, plantFunctor);
    simulation.addMob(cabbage2);
    //cabbage->body->ApplyTorque(30000,true);
    cabbage2->body->ApplyLinearImpulse(b2Vec2(5,0),cabbage2->body->GetWorldCenter(),true);

    //cabbage2->ScheduleRadiusChange(6);

    QTimer *timer;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Mammals::physicsUpdate);
    timer->start(1000/60);
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
