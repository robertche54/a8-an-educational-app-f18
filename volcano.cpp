#include "volcano.h"
#include "ui_volcano.h"

Volcano::Volcano(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Volcano)
{
    ui->setupUi(this);

    b2BodyDef myBodyDef;
    b2FixtureDef myFixtureDef;

    myBodyDef.type = b2_staticBody; //change body type
    myBodyDef.position.Set(0,-10); //middle, bottom

    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(-100,0), b2Vec2(100,0));
    myFixtureDef.shape = &edgeShape;
    b2Body* staticBody = simulation.world.CreateBody(&myBodyDef);
    staticBody->CreateFixture(&myFixtureDef); //add a fixture to the body

    simulation.createMob("../A9/bricks.jpg", 0, -9, 2, 2, "brick", b2_dynamicBody);

    for(int i = -5; i < 5; i++) {
        simulation.createMob("../A9/otherimage.png", i, -7, 1, 1);
    }

    connect(ui->explodeButton, &QPushButton::pressed, this, &Volcano::explodeClicked);
}

Volcano::~Volcano()
{
    delete ui;
}

void Volcano::closeEvent(QCloseEvent*) {
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
        simulation.applyImpulse(brick, 90, 20);
    }
    else {
        simulation.createExplosion(brick->body->GetPosition(), 50, 120);
    }
}
