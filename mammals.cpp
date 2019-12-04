#include "mammals.h"
#include "ui_mammals.h"
#include <QTimer>

auto plantFunctor = [] (float a) -> float {return a==0 ? 0 : 1;};
auto mammalFunctor = [] (float a) -> float {return sqrt(max(0.0f,30 - (5*21)/(4+a)));};
auto dinoFunctor = [] (float a) -> float {return sqrt(max(0.0f,100 - (10*96)/(9+a)));};

Mammals::Mammals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mammals)
{
    ui->setupUi(this);
    simulation.setGravity(0,0);
    handler = new CreatureCollisionHandler();
    simulation.setContactListener(handler);
    populateWorld(10,10,5,2,2);
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
        addMammal(x,y);
    }
    while (dinos-- > 0) {
        float x = xRange*(random()%20000 - 10000)/10000;
        float y = yRange*(random()%20000 - 10000)/10000;
        addDino(x,y);
    }
}
void Mammals::addMammal(float x, float y) {
    simulation.addMob(new Creature("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/mammal.png", x, y, float(random()%8+2)/3.0f, simulation.world, mammalFunctor));
}
void Mammals::addDino(float x, float y) {
    simulation.addMob(new Creature("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/otherimage.png", x, y, float(random()%8+2)/3.0f, simulation.world, dinoFunctor));
}
void Mammals::addPlant(float x, float y) {
    simulation.addMob(new Creature("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/cabbage.png", x, y, float(random()%3+2)/3.0f, simulation.world, plantFunctor));
}


void Mammals::physicsUpdate() {

    QImage newImage = simulation.step();
    ui->simulationLabel->setPixmap(QPixmap::fromImage(newImage));
}

Mammals::~Mammals()
{
    delete ui;
}

void Mammals::mousePressEvent(QMouseEvent *event)
{
    // QT coordinates need to be converted to box2D coordinates
    //simulation.createSingularity(event->x(), event->y());
}

void Mammals::paintEvent(QPaintEvent*)
{
    //QImage newImage = simulation.step();
    //ui->worldLabel->setPixmap(QPixmap::fromImage(newImage));
}

void Mammals::closeEvent(QCloseEvent *) {
    emit returnFocus();
}
