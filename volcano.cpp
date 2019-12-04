#include <QStringList>
#include <QString>
#include "volcano.h"
#include "ui_volcano.h"

Volcano::Volcano(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Volcano)
{
    ui->setupUi(this);

    QStringList volcanoList = (QStringList()<<"0: Kilauea (1977)"<<"1: Nyiragongo (2002)"<<"2: Unzen (1792)"
                               <<"3: Nevado del Ruiz (1985)"<<"4: Laki (1783)"<<"5: St. Helens (1980)"
                               <<"6: Krakatoa (1883)"<<"7: Tambora (1815)"<<"8: Yellowstone (630,000 BC)");

    ui->powerSelector->addItems(volcanoList);

    connect(ui->explodeButton, &QPushButton::pressed, this, &Volcano::explodeClicked);
    connect(ui->resetButton, &QPushButton::pressed, this, &Volcano::clearSimulation);
}

Volcano::~Volcano()
{
    delete ui;
}

void Volcano::showEvent(QShowEvent *) {
    initializeSimulation();
}

void Volcano::closeEvent(QCloseEvent*) {
    simulation.clearSimulation();
    simulation.world.DestroyBody(groundBody);
    emit returnFocus();
}

void Volcano::paintEvent(QPaintEvent*)
{

    QImage newImage = simulation.step();
    ui->simulationLabel->setPixmap(QPixmap::fromImage(newImage));
}

void Volcano::explodeClicked() {
    Mob* brick = simulation.namedMobs.at("brick");

    if(ui->customCheck->isChecked()) {
        int powerselected = ui->customPower->value() * 100;

        simulation.applyImpulse(brick, 90, powerselected);
    }
    else {
        int powerselected;
        switch(ui->powerSelector->currentIndex()) {

        // index corrosponds with the volanco's explosivity index
        case 0: powerselected = 100;
            break;

        case 1: powerselected = 200;
            break;

        case 2: powerselected = 300;
            break;

        case 3: powerselected = 400;
            break;

        case 4: powerselected = 500;
            break;

        case 5: powerselected = 600;
            break;

        case 6: powerselected = 700;
            break;

        case 7: powerselected = 800;
            break;

        case 8: powerselected = 900;
            break;

        default: powerselected = 0;
            break;
        }

        simulation.createExplosion(brick->body->GetPosition(), powerselected, 120);
    }
}

void Volcano::clearSimulation() {

    simulation.clearSimulation();
    simulation.world.DestroyBody(groundBody);
    initializeSimulation();
}

void Volcano::initializeSimulation() {
    simulation.isRunning = true;

    b2BodyDef groundBodyDef;
    b2FixtureDef groundFixtureDef;

    groundBodyDef.type = b2_staticBody; //change body type
    groundBodyDef.position.Set(0,-40); //middle, bottom

    b2EdgeShape groundShape;
    groundShape.Set(b2Vec2(-100,0), b2Vec2(100,0));
    groundFixtureDef.shape = &groundShape;
    groundBody = simulation.world.CreateBody(&groundBodyDef);
    groundBody->CreateFixture(&groundFixtureDef); //add a fixture to the body

    simulation.setGravity(0.0f, -200.0f);
    simulation.tf.setWindowSize(200, 200);
    simulation.createMob("../A9/bricks.jpg", 0.0f, -20.0f, 3.0f, 3.0f, "brick", b2_dynamicBody);

    for(float x = -10; x < 10; x += 1.0f) {
        for(float y = -10; y < 10; y += 1.0f) {
            simulation.createMob("../A9/otherimage.png", x, y, 1.0f, 1.0f);
        }
    }
}
