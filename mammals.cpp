#include "mammals.h"
#include "ui_mammals.h"

Mammals::Mammals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mammals)
{
    ui->setupUi(this);
    simulation.setGravity(0,0);
    handler = new CreatureCollisionHandler();
    simulation.setContactListener(handler);

    Creature* cabbage = new Creature("../A9/cabbage.png", 5, 5, 4, simulation.world);
    simulation.addMob(cabbage);
}

Mammals::~Mammals()
{
    delete ui;
}

void Mammals::paintEvent(QPaintEvent*)
{
    QImage newImage = simulation.step();
    ui->worldLabel->setPixmap(QPixmap::fromImage(newImage));
}
