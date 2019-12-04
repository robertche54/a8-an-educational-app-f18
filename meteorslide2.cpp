#include "meteorslide2.h"
#include "ui_meteorslide2.h"
#include "Box2D/Box2D.h"

MeteorSlide2::MeteorSlide2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeteorSlide2)
{
    ui->setupUi(this);
    ui->TextLabel->setText(infoVec.front());
    ui->backLabel->setPixmap(QPixmap("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/dinoscene0.jpg"));

    sim.setGravity(0,-9.81f);
    addElements();
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim.step()));
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


/**
 * Adds all the bodies to the world for the simulation
 * @brief MeteorSlide2::addElements
 */
void MeteorSlide2::addElements(){
    // Creates ground
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
    tramp.position.Set(0,-9);

    b2FixtureDef trampFixDef;
    trampFixDef.restitution = 2.0f;
    trampFixDef.friction = 0.0f;

    b2PolygonShape shape;
    shape.SetAsBox(200,0.5);
    trampFixDef.shape = &shape;

    b2Body* trampoline = sim.world.CreateBody(&tramp);
    trampoline->CreateFixture(&trampFixDef);


    // Meteor mob
    sim.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/meteorite.png",45,50,10,10,"meteor", b2_dynamicBody);
    Mob* meteor = sim.namedMobs.at("meteor");
    sim.applyImpulse(meteor,235,150);
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim.step()));

    //Dino mobs
    sim.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/TRex.png",-3,-5,2,2);
    sim.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/screamingDino.png", -8, -4, 3, 3);
    sim.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/pteranodon.png",4, 6, 2, 2);
}


/**
 * Updates the background to mirror the movement
 * of the meteorite
 * @brief MeteorSlide2::changeBackground
 */
void MeteorSlide2::changeBackground(){
    switch(++backgroundIndex){
        case 1:
            ui->backLabel->setPixmap(QPixmap("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/dinoscene1.jpg"));
            break;
        case 2:
            ui->backLabel->setPixmap(QPixmap("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/dinoscene2.jpg"));
            break;
        case 3:
            ui->backLabel->setPixmap(QPixmap("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/dinoscene3.jpg"));
            break;
        case 4:
            ui->backLabel->setPixmap(QPixmap("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/dinoscene4.jpg"));
            break;
        default:
            backGroundTimer->stop();
            break;
    }
}


void MeteorSlide2::on_startButton_clicked()
{
    // Steping timer to call update
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MeteorSlide2::update);
    timer->start(1000/60);

    backGroundTimer = new QTimer();
    connect(backGroundTimer, &QTimer::timeout, this, &MeteorSlide2::changeBackground);
    backGroundTimer->start(400);
}
