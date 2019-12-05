#include "meteorslide1.h"
#include "ui_meteorslide1.h"
#include <iostream>

MeteorSlide1::MeteorSlide1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeteorSlide1)
{
    ui->setupUi(this);
    //ui->setStyleSheet("background-image: /home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/OceanImpactBackdrop.png");
    QString string1 = "Welcome to the ocean impact page. Press 'Next' to continue!";
    QString string2 = "The ocean impact, like, seriously messed the dinos up.";
    QString string3 = "Well, the ocean didn't impact anything. . .";
    QString string4 = "It was actually the meteorite that impacted the ocean that did it.";
    infoVec.push_back(string1);
    infoVec.push_back(string2);
    infoVec.push_back(string3);
    infoVec.push_back(string4);

    b2BodyDef myBodyDef;
    b2FixtureDef myFixtureDef;

    myBodyDef.type = b2_staticBody; //change body type
    myBodyDef.position.Set(0,-10);

    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(-100,0), b2Vec2(100,0));
    myFixtureDef.shape = &edgeShape;
    b2Body* staticBody = simulation.world.CreateBody(&myBodyDef);
    staticBody->CreateFixture(&myFixtureDef);

    ui->TextLabel->setText(infoVec.front());
    QPixmap pixmap("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/underwater.jpg");
    ui->label->setPixmap(pixmap);
    simulation.setGravity(0,-10);

    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            simulation.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/WaterDroplet.png",-200.0 + i,-5 + j,1.0,1.0,"Wave" + to_string(i) + to_string(j), b2_dynamicBody);
            Mob *wave = simulation.namedMobs.at("Wave" + to_string(i) + to_string(j));
            wave->body->SetLinearVelocity(b2Vec2(500.0f, 0.0f));
            wave->body->SetAngularVelocity(100);
        }
    }

    simulation.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/coelacanth.png", 2,7,2,2);
    simulation.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/mosasaurus.png", -5,3,9,5, "mosasaur", b2_dynamicBody);
    Mob *mosasaur = simulation.namedMobs.at("mosasaur");
    mosasaur->body->SetLinearVelocity(b2Vec2(10.0f, 0.0f));
    simulation.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/coelacanth.png", 4,3,3,2, "fish", b2_dynamicBody);
    Mob *fish = simulation.namedMobs.at("fish");
    fish->body->SetLinearVelocity(b2Vec2(10.0f, 0.0f));
    simulation.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/seaweed.png", 8,-5,3,11);
    simulation.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/seaweed.png", -9,-7,3,8);

    ui->AnimationLabel->setPixmap(QPixmap::fromImage(simulation.step()));
}

MeteorSlide1::~MeteorSlide1()
{
    delete ui;
}

void MeteorSlide1::on_NextButton_clicked()
{
    if(infoIndex < infoVec.size() - 1)
    {
        infoIndex++;
        ui->TextLabel->setText(infoVec.at(infoIndex));
    }
}

void MeteorSlide1::runAnimation(){

    QImage newImage = simulation.step();
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(newImage));
}

void MeteorSlide1::on_BackButton_clicked()
{
    if(infoIndex > 0)
    {
        infoIndex--;
        ui->TextLabel->setText(infoVec.at(infoIndex));
    }
}

void MeteorSlide1::on_Start_clicked()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MeteorSlide1::runAnimation);
    timer->start(1000/60);
}
