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

    b2BodyDef myBodyDef;
    b2FixtureDef myFixtureDef;

    myBodyDef.type = b2_staticBody; //change body type
    myBodyDef.position.Set(0,-10); //middle, bottom

    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(-100,0), b2Vec2(100,0));
    myFixtureDef.shape = &edgeShape;
    b2Body* staticBody = simulation.world.CreateBody(&myBodyDef);
    staticBody->CreateFixture(&myFixtureDef); //add a fixture to the body

    simulation.setGravity(0.0f, -200.0f);
    simulation.tf.setWindowSize(200, 200);
    simulation.createMob("../A9/bricks.jpg", 0.0f, -9.0f, 3.0f, 3.0f, "brick", b2_dynamicBody);

    for(float x = -10; x < 10; x += 1.0f) {
        for(float y = -5; y < 10; y += 1.0f) {
            simulation.createMob("../A9/otherimage.png", x, y, 1.0f, 1.0f);
        }
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
        simulation.applyImpulse(brick, 90, 40);
    }
    else {
        simulation.createExplosion(brick->body->GetPosition(), 40, 120);
    }
}
