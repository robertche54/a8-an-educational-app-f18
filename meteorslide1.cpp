#include "meteorslide1.h"
#include "ui_meteorslide1.h"
#include <iostream>

MeteorSlide1::MeteorSlide1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeteorSlide1)
{
    ui->setupUi(this);
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
    QPixmap pixmap("../A9/underwater.jpg");
    ui->label->setPixmap(pixmap);
    simulation.setGravity(0,-10);
    simulation.createMob("../A9/oceanwave.png",-80.0,0.0,6,40.0,"Wave", b2_dynamicBody);
    Mob *wave = simulation.namedMobs.at("Wave");

    wave->body->SetLinearVelocity(b2Vec2(250.0f, 0.0f));
    wave->body->SetFixedRotation(true);
    simulation.createMob("../A9/coelacanth.png", 2,5,3,3);
    simulation.createMob("../A9/mosasaurus.png", -3,2,10,6);
    simulation.createMob("../A9/coelacanth.png", 4,2,4,3);
    simulation.createMob("../A9/seaweed.png", 8,-5,4,12);
    simulation.createMob("../A9/seaweed.png", -9,-2,4,9);



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
