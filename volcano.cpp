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
    //ui->backgroundLabel->setText()
    //ui->backgroungLabe->setText(infoVec.front());
//    QPixmap pixmap("../A9/volcanoleft.png");
//    ui->backgroundLabel->setPixmap(pixmap);

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
    /*
    if (earthQuake) {
        simulation.tf.setWindowSize(windowW, windowH);

        if (windowH == 200) {
            windowH -= 20;
        }
        else {
            windowH += 20;
        }

        for (pair<string, Mob*> namedMob : simulation.namedMobs) {
            simulation.applyImpulse(namedMob.second, 90, 50);
        }

        for (Mob* mob : simulation.genericMobs) {
            simulation.applyImpulse(mob, 90, 50);
        }
        earthQuake = false;
    }
    */

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
//        int powerselected;
//        switch(ui->powerSelector->currentIndex()) {

//        // index corrosponds with the volanco's explosivity index
//        case 0: powerselected = 200;
//            break;

//        case 1: powerselected = 400;
//            break;

//        case 2: powerselected = 800;
//            break;

//        case 3: powerselected = 1600;
//            break;

//        case 4: powerselected = 3200;
//            break;

//        case 5: powerselected = 6400;
//            break;

//        case 6: powerselected = 12800;
//            break;

//        case 7: powerselected = 25600;
//            break;

//        case 8: powerselected = 51200;
//            break;

//        default: powerselected = 0;
//            break;
        }

//        simulation.createExplosion(brick->body->GetPosition(), powerselected, 120);
//    }
}

void Volcano::clearSimulation() {

    simulation.clearSimulation();
    simulation.world.DestroyBody(groundBody);
    initializeSimulation();
}

void Volcano::initializeSimulation() {
    simulation.isRunning = true;

   b2BodyDef groundBodyDef;
//    b2BodyDef leftWallBodyDef;
//    b2BodyDef rightWallBodyDef;
   b2FixtureDef groundFixtureDef;
//    b2FixtureDef leftWallFixtureDef;
//    b2FixtureDef rightWallFixtureDef;

//    leftWallBodyDef.type = b2_staticBody;

//    b2Vec2 leftVerticies[3];
//    leftVerticies[0] = b2Vec2(10, -20);
//    leftVerticies[1] = b2Vec2(-30, -40);
//    leftVerticies[2] = b2Vec2(10, -40);

//    b2PolygonShape leftWallShape;
//    leftWallShape.Set(leftVerticies, 3);

//    leftWallFixtureDef.shape = &leftWallShape;
//    leftWallBodyDef.position.Set(0, 0);

//    leftWallBody = simulation.world.CreateBody(&leftWallBodyDef);
//    leftWallBody->CreateFixture(&leftWallFixtureDef);

//    rightWallBodyDef.type = b2_staticBody;

//    b2Vec2 rightVerticies[3];
//    rightVerticies[0] = b2Vec2(30, -20);
//    rightVerticies[1] = b2Vec2(60, -40);
//    rightVerticies[2] = b2Vec2(30, -40);

//    b2PolygonShape rightWallShape;
//    rightWallShape.Set(rightVerticies, 3);

//    rightWallFixtureDef.shape = &rightWallShape;
//    rightWallBodyDef.position.Set(0, 0);

//    rightWallBody = simulation.world.CreateBody(&rightWallBodyDef);
//    rightWallBody->CreateFixture(&rightWallFixtureDef);

    /*
    for (int i = 10; i < 40; i += 20) {
        wallBodyDef.position.Set(i, -40);

        vertecies[0] = b2Vec2(i, -40);
        vertecies[1] = b2Vec2(i * 20, -40);
        vertecies[2] = b2Vec2(i, 0);
        wallShape.Set(vertecies, 3);

        wallFixtureDef.shape = &wallShape;

        if (i == -1) {
            leftWallBody = simulation.world.CreateBody(&wallBodyDef);
            leftWallBody->CreateFixture(&wallFixtureDef);
        }
        else {
            rightWallBody = simulation.world.CreateBody(&wallBodyDef);
            rightWallBody->CreateFixture(&wallFixtureDef);
        }
    }
    */

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
            simulation.createMob("../A9/lava2.png", x, y, .8f, .8f);
        }
    }
    //creation of volcano test
    //simulation.createMob("../A9/otherimage.png", -10, 10, 2.0f, b2_dynamicBody);
    simulation.createMob("../A9/lava2.png", -10, 10, 2.0f, b2_dynamicBody);

        vector<b2Vec2> leftVolcano;
        vector<b2Vec2> rightVolcano;

        b2Vec2 vert1(-10, -10);
        leftVolcano.push_back(vert1);
        b2Vec2 vert2(10, -10);
        leftVolcano.push_back(vert2);
        b2Vec2 vert3(10, 10);
        leftVolcano.push_back(vert3);

        b2Vec2 cert1(-10, 10);
        rightVolcano.push_back(cert1);
        b2Vec2 cert2(-10, -10);
        rightVolcano.push_back(cert2);
        b2Vec2 cert3(10, -10);
        rightVolcano.push_back(cert3);



      simulation.createMob("../A9/volcanoleft.png", -16, -12, leftVolcano, b2_staticBody);
      simulation.createMob("../A9/volcanoright.png", 16, -12, rightVolcano, b2_staticBody);
}
