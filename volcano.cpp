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

//    ui->explodeButton->setIcon(QIcon("../A9/unknown.png"));
//    ui->explodeButton->setIconSize(QSize(ui->explodeButton->size()));

    QPixmap pixmap("../A9/volcanoSky.jpeg");
    pixmap = pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
    ui->backgroundLabel->setPixmap(pixmap);

    QPixmap volcanoCover("../A9/volcano.jpeg");
    volcanoCover = volcanoCover.scaled(ui->volcanoLabel->size(), Qt::IgnoreAspectRatio);
    ui->volcanoLabel->setPixmap(volcanoCover);

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
    float powerselected;

    // value/index corrosponds with the volanco's explosivity index
    if(ui->customCheck->isChecked()) {
        powerselected = 50 + float(pow(3, ui->customPower->value()));
    }
    else {

        powerselected = 50 + float(pow(3, ui->powerSelector->currentIndex()));
    }
    simulation.createExplosion(brick->body->GetPosition(), powerselected, 120);
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
    groundBodyDef.position.Set(0,-20); //middle, bottom

    b2EdgeShape groundShape;
    groundShape.Set(b2Vec2(-100,0), b2Vec2(100,0));
    groundFixtureDef.shape = &groundShape;
    groundBody = simulation.world.CreateBody(&groundBodyDef);
    groundBody->CreateFixture(&groundFixtureDef); //add a fixture to the body

    simulation.setGravity(0.0f, -1000.0f);
    simulation.tf.setWindowSize(600, 500);
    simulation.tf.setBox2dWindow(b2Vec2(-20,20),b2Vec2(20, -20));
    simulation.createMob("../A9/lava2.png", 0.0f, -19.0f, 1.0f, 1.0f, "brick", b2_dynamicBody);

    for(float x = -8; x < 8; x += .8f) {
        for(float y = -14; y < 0; y += .8f) {
            simulation.createMob("../A9/Lava.png", x, y, .5f, b2_dynamicBody);
        }
    }
    //creation of volcano test
    //simulation.createMob("../A9/otherimage.png", -10, 10, 2.0f, b2_dynamicBody);
    //simulation.createMob("../A9/lava2.png", -10, 10, 2.0f, b2_dynamicBody);

        vector<b2Vec2> leftVolcano;
        vector<b2Vec2> rightVolcano;

        b2Vec2 vert1(-10, -10);
        leftVolcano.push_back(vert1);
        b2Vec2 vert2(11, -10);
        leftVolcano.push_back(vert2);
        b2Vec2 vert3(9, 9);
        leftVolcano.push_back(vert3);

        b2Vec2 cert1(-9, 9);
        rightVolcano.push_back(cert1);
        b2Vec2 cert2(-11, -10);
        rightVolcano.push_back(cert2);
        b2Vec2 cert3(10, -10);
        rightVolcano.push_back(cert3);

      simulation.createMob("../A9/volcanoleft.png", -16, -12, leftVolcano, b2_staticBody);
      simulation.createMob("../A9/volcanoright.png", 16, -12, rightVolcano, b2_staticBody);
}
