#include "meteorslide2.h"
#include "ui_meteorslide2.h"
#include "Box2D/Box2D.h"

MeteorSlide2::MeteorSlide2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeteorSlide2)
{
    sim = new Simulation();
    ui->setupUi(this);
    ui->TextLabel->setText(infoVec.front());
    ui->backLabel->setPixmap(QPixmap("../A9/dinoscene0.jpg"));

    sim->setGravity(0,-9.81f);
    addElements();
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}

MeteorSlide2::~MeteorSlide2()
{
    delete ui;
}

void MeteorSlide2::on_NextButton_clicked()
{
    if(static_cast<ulong>(infoIndex) < infoVec.size() - 1)
    {
        infoIndex++;
        ui->TextLabel->setText(infoVec.at(static_cast<ulong>(infoIndex)));
    }
}

void MeteorSlide2::on_BackButton_clicked()
{
    if(infoIndex > 0)
    {
        infoIndex--;
        ui->TextLabel->setText(infoVec.at(static_cast<ulong>(infoIndex)));
    }
}

void MeteorSlide2::update(){
     ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
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
    b2Body* staticBody = sim->world.CreateBody(&myBodyDef);
    staticBody->CreateFixture(&myFixtureDef); //add a fixture to the body

    // Bouncy ground for collision
    b2BodyDef tramp;
    tramp.type = b2_dynamicBody;
    tramp.position.Set(0,-15);

    b2FixtureDef trampFixDef;
    trampFixDef.restitution = 2.0f;
    trampFixDef.friction = 0.0f;

    b2PolygonShape shape;
    shape.SetAsBox(200,0.5);
    trampFixDef.shape = &shape;

    b2Body* trampoline = sim->world.CreateBody(&tramp);
    trampoline->CreateFixture(&trampFixDef);

    // Meteor mob
    sim->createMob("../A9/meteorite.png",45,50,10,10,"meteor", b2_dynamicBody);
    Mob* meteor = sim->namedMobs.at("meteor");
    sim->applyImpulse(meteor,235,150);

    //Dino mobs
    Mob* trex = new Mob("../A9/landDinos/TRex.png",-3,-5,2,2,sim->world);
    sim->addMob(trex, "trex");
    dinos.push_back(trex);
    dinos.push_back(new Mob("../A9/landDinos/spikey.png", -8,-1,2,1, sim->world));
    dinos.push_back(new Mob("../A9/landDinos/screamingDino.png", -8, -4, 3, 3, sim->world));
    dinos.push_back(new Mob("../A9/landDinos/pteranodon.png",2, 6, 2, 2,sim->world));
    dinos.push_back(new Mob("../A9/landDinos/dino2.png",-4,-6,2,2,sim->world));
    dinos.push_back(new Mob("../A9/landDinos/rock.png",2,-9,4,4, sim->world));
    dinos.push_back(new Mob("../A9/landDinos/tree.png",8,-8,10,10,sim->world));

    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}


/**
 * Updates the background to mirror the movement
 * of the meteorite
 * @brief MeteorSlide2::changeBackground
 */
void MeteorSlide2::changeBackground(){
    switch(++backgroundIndex){
        case 1:
            ui->backLabel->setPixmap(QPixmap("../A9/dinoscene1.jpg"));
            break;
        case 2:
            ui->backLabel->setPixmap(QPixmap("../A9/dinoscene2.jpg"));
            break;
        case 3:
            ui->backLabel->setPixmap(QPixmap("../A9/dinoscene3.jpg"));
            break;
        case 4:
            ui->backLabel->setPixmap(QPixmap("../A9/dinoscene4.jpg"));
            break;
        default:
            backGroundTimer->stop();
            break;
    }
}


void MeteorSlide2::on_startButton_clicked(){
    sim->isRunning = true;

    // Steping timer to call update
    worldTimer = new QTimer(this);
    connect(worldTimer, &QTimer::timeout, this, &MeteorSlide2::update);
    worldTimer->start(1000/60);

    backGroundTimer = new QTimer();
    connect(backGroundTimer, &QTimer::timeout, this, &MeteorSlide2::changeBackground);
    backGroundTimer->start(400);
}

void MeteorSlide2::selectDinoCount(int count){
    for(uint i = 0; i < static_cast<uint>(count); i++){
        string s("%s",i);
        sim->addMob(dinos[i],s);
    }
}

void MeteorSlide2::on_reset_clicked(){
    worldTimer->stop();
    sim = new Simulation();
    dinos.clear();
    addElements();
    ui->backLabel->setPixmap(QPixmap("../A9/dinoscene0.jpg"));
    backgroundIndex=0;
    ui->dinoSelect->setValue(1);
}

void MeteorSlide2::on_dinoSelect_valueChanged(int count){
    for(uint i = 0; i < static_cast<uint>(count); i++){
        string s("%s",i);
        sim->addMob(dinos[i],s);
    }
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}
