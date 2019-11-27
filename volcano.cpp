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

    simulation.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/DinoTitle.png", 0, 5, 15, 5, "title", b2_dynamicBody);
    simulation.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/bricks.jpg", 5, 1, 2, 2, "brick", b2_staticBody);

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

    if(ui->customCheck->isChecked()) {
        Mob* title = simulation.namedMobs.at("title");
        simulation.applyImpulse(title, 90, 20);
    }
    else {
        Mob* brick = simulation.namedMobs.at("brick");
        simulation.createExplosion(brick->body->GetPosition(), 50, 120);
    }
}
