#include "meteorslide1.h"
#include "ui_meteorslide1.h"
#include <iostream>

MeteorSlide1::MeteorSlide1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeteorSlide1)
{
    ui->setupUi(this);
    ui->TextLabel->setStyleSheet("QLabel { color : white; }");
    QString string1 = "According to abundant geological evidence, an asteroid roughly 10 km (6 miles) across hit Earth about 65 million years ago.";
    QString string2 = "This impact made a huge explosion and a crater about 180 km (roughly 110 miles) across.";
    QString string3 = "During the impact, the kinetic energy in the asteroid blew debris of dust, soil, and rocks into the atmosphere. There were likely large tsunamis which were swept across the Earth’s surface.";
    QString string4 = "Sea creatures, however, would have been buffered from the blazing effects of the collision in the first hours, but plankton on the surface died out over the weeks of darkness from the debris shrouding the sun’s light.";
    QString string5 = "This decrease in plankton decimated the food supply for small fish, which affected the bigger fish, and so on.";
    QString string6 = "Additionally, the sulfur-rich debris from the collision resulted in acidic rain that severely harmed marine life and resulted in the extinction of many marine species.";
    QString string7 = "While other theories have challenged the reason for prehistoric marine life extinction, recent evidence shows that it was, in fact, caused by the meteorite collision and the flash acidification of the ocean.";
    //QString string8 = "Resources:\nhttps://www.psi.edu/epo/ktimpact/ktimpact.html\nhttps://www.britannica.com/science/K-T-extinction\nhttps://www.pnas.org/content/112/21/6556\nhttps://www.nytimes.com/2019/10/21/science/chicxulub-asteroid-ocean-acid.html";

    infoVec.push_back(string1);
    infoVec.push_back(string2);
    infoVec.push_back(string3);
    infoVec.push_back(string4);    
    infoVec.push_back(string5);
    infoVec.push_back(string6);
    infoVec.push_back(string7);
    //infoVec.push_back(string8);

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

    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            simulation.createMob("../A9/WaterDroplet.png",-200.0 + i,-5 + j,1.0,1.0,"Wave" + to_string(i) + to_string(j), b2_dynamicBody);
            Mob *wave = simulation.namedMobs.at("Wave" + to_string(i) + to_string(j));
            wave->body->SetLinearVelocity(b2Vec2(500.0f, 0.0f));
            wave->body->SetAngularVelocity(100);
        }
    }

    simulation.createMob("../A9/coelacanth.png", 2,7,2,2);
    simulation.createMob("../A9/mosasaurus.png", -5,3,9,5, "mosasaur", b2_dynamicBody);
    Mob *mosasaur = simulation.namedMobs.at("mosasaur");
    mosasaur->body->SetLinearVelocity(b2Vec2(10.0f, 0.0f));
    simulation.createMob("../A9/coelacanth.png", 4,3,3,2, "fish", b2_dynamicBody);
    Mob *fish = simulation.namedMobs.at("fish");
    fish->body->SetLinearVelocity(b2Vec2(10.0f, 0.0f));
    simulation.createMob("../A9/seaweed.png", 8,-5,3,11);
    simulation.createMob("../A9/seaweed.png", -9,-7,3,8);

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
