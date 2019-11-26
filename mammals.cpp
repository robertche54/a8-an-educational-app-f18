#include "mammals.h"
#include "ui_mammals.h"

Mammals::Mammals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mammals)
{
    ui->setupUi(this);
    handler = new CreatureCollisionHandler();
    simulation.setContactListener(handler);
}

Mammals::~Mammals()
{
    delete ui;
}
