#include "meteorslide2.h"
#include "ui_meteorslide2.h"
#include "Box2D/Box2D.h"

MeteorSlide2::MeteorSlide2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeteorSlide2)
{
    ui->setupUi(this);
    QString string1 = "Welcome to the ground impact page. Press 'Next' to continue!";
    QString string2 = "The ground impact, like, seriously messed the dinos up.";
    QString string3 = "Well, the ground didn't impact anything. . .";
    QString string4 = "It was actually the meteorite that impacted the ground that did it.";
    infoVec.push_back(string1);
    infoVec.push_back(string2);
    infoVec.push_back(string3);
    infoVec.push_back(string4);

    ui->TextLabel->setText(infoVec.front());

    sim.setGravity(0,-1);

    // Creating the ground
    b2BodyDef myBodyDef;
    b2FixtureDef myFixtureDef;

    myBodyDef.type = b2_staticBody; //change body type
    myBodyDef.position.Set(0,-10); //middle, bottom

    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(-100,0), b2Vec2(100,0));
    myFixtureDef.shape = &edgeShape;
    b2Body* staticBody = sim.world.CreateBody(&myBodyDef);
    staticBody->CreateFixture(&myFixtureDef); //add a fixture to the body

    // Bouncy ground for collision
    b2BodyDef tramp;
    tramp.type = b2_dynamicBody;
    tramp.position.Set(0,-8);

    b2FixtureDef trampFixDef;
    trampFixDef.restitution = 0.99f;

    b2PolygonShape shape;
    shape.SetAsBox(5,1);
    trampFixDef.shape = &shape;

    b2Body* trampoline = sim.world.CreateBody(&tramp);
    trampoline->CreateFixture(&trampFixDef);


    // Meteor mob
    sim.createMob("../A9/meteorite.png",5,50,5,5,"meteor", b2_dynamicBody);
    Mob* meteor = sim.namedMobs.at("meteor");
    sim.applyImpulse(meteor,260,200);
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim.step()));

    // Dino mobs
    for(int i=0; i<5; i++){      
        sim.createMob("../A9/TRex.png",i-2,-5,2,2);
    }

    // Steping timer to call update
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MeteorSlide2::update);
    timer->start(1000/60);

}

MeteorSlide2::~MeteorSlide2()
{
    delete ui;
}

void MeteorSlide2::on_NextButton_clicked()
{
    if(infoIndex < infoVec.size() - 1)
    {
        infoIndex++;
        ui->TextLabel->setText(infoVec.at(infoIndex));
    }
}

void MeteorSlide2::on_BackButton_clicked()
{
    if(infoIndex > 0)
    {
        infoIndex--;
        ui->TextLabel->setText(infoVec.at(infoIndex));
    }
}

void MeteorSlide2::update(){
     ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim.step()));
}
