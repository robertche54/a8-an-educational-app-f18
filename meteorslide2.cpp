#include "meteorslide2.h"

/**
 * Creates a window with a meteorite impact event
 * @brief MeteorSlide2::MeteorSlide2
 * @param parent
 */
MeteorSlide2::MeteorSlide2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeteorSlide2)
{
    sim = new Simulation();
    ui->setupUi(this);
    ui->TextLabel->setText(infoVec.front());
    ui->backLabel->setPixmap(QPixmap("../A9/dinoscene0.jpg"));

    addWorldDefinitions();
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}

/**
 * Destructor
 * @brief MeteorSlide2::~MeteorSlide2
 */
MeteorSlide2::~MeteorSlide2()
{
    delete ui;
}


/**
 * Progresses the info slides
 * @brief MeteorSlide2::on_NextButton_clicked
 */
void MeteorSlide2::on_NextButton_clicked()
{
    if(static_cast<ulong>(infoIndex) < infoVec.size() - 1)
    {
        infoIndex++;
        ui->TextLabel->setText(infoVec.at(static_cast<ulong>(infoIndex)));
    }
}


/**
 * Moves to previous info slides
 * @brief MeteorSlide2::on_BackButton_clicked
 */
void MeteorSlide2::on_BackButton_clicked()
{
    if(infoIndex > 0)
    {
        infoIndex--;
        ui->TextLabel->setText(infoVec.at(static_cast<ulong>(infoIndex)));
    }
}


/**
 * Steps the simulation updating the postions of the elements in the simulation.
 * @brief MeteorSlide2::update
 */
void MeteorSlide2::update(){
     ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}


/**
 * Adds the ground bodies to the world for the simulation
 * @brief MeteorSlide2::addElements
 */
void MeteorSlide2::addWorldDefinitions(){
    // Creates ground
    b2BodyDef myBodyDef;
    b2FixtureDef myFixtureDef;

    myBodyDef.type = b2_staticBody; //change body type
    myBodyDef.position.Set(0,-13); //middle, bottom

    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(-100,0), b2Vec2(100,0));
    myFixtureDef.shape = &edgeShape;
    b2Body* staticBody = sim->world.CreateBody(&myBodyDef);
    staticBody->CreateFixture(&myFixtureDef); //add a fixture to the body

    // Bouncy ground for collision
    b2BodyDef tramp;
    tramp.type = b2_dynamicBody;
    tramp.position.Set(0,-12);

    b2FixtureDef trampFixDef;
    trampFixDef.restitution = 2.0f;
    trampFixDef.friction = 0.0f;

    b2PolygonShape shape;
    shape.SetAsBox(200,0.5);
    trampFixDef.shape = &shape;

    b2Body* trampoline = sim->world.CreateBody(&tramp);
    trampoline->CreateFixture(&trampFixDef);

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
            sim->createMob("../A9/landDinos/smoke.png",0,25,40,10,"smoke",b2_dynamicBody);
            break;
    }
}



/**
 * Starts the timer for the world stepping and the background to chang
 * as the meteorite impacts the earth.
 * @brief MeteorSlide2::on_startButton_clicked
 */
void MeteorSlide2::on_startButton_clicked(){
    sim->isRunning = true;
    sim->setGravity(0,-9.81f);

    // Add meteor mob
    sim->createMob("../A9/meteorite.png",22,100,30,30,"meteor", b2_dynamicBody);
    Mob* meteor = sim->namedMobs.at("meteor");
    sim->applyImpulse(meteor,265,300);

    for(uint i=0; i<128; i++){
        sim->createMob("../A9/Lava.png", i-64, -11, 1, 1,b2_dynamicBody);
    }

    // Steping timer to call update
    worldTimer = new QTimer(this);
    connect(worldTimer, &QTimer::timeout, this, &MeteorSlide2::update);
    worldTimer->start(1000/60);

    backGroundTimer = new QTimer();
    connect(backGroundTimer, &QTimer::timeout, this, &MeteorSlide2::changeBackground);
    backGroundTimer->start(600);
}


/**
 * Clears the simulation and sets it to its defualt appearance.
 * @brief MeteorSlide2::on_reset_clicked
 */
void MeteorSlide2::on_reset_clicked(){
    worldTimer->stop();
    sim = new Simulation();
    dinos.clear();
    addWorldDefinitions();
    ui->backLabel->setPixmap(QPixmap("../A9/dinoscene0.jpg"));
    backgroundIndex=0;
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}



/**
 * Adds in a TRex if it does not already exist in the
 * simulation. Removes it otherwise
 * @brief MeteorSlide2::on_TRexButton_clicked
 */
void MeteorSlide2::on_TRexButton_clicked()
{
    dinos.insert(pair<string,Mob*>("TRex",new Mob("../A9/landDinos/TRex.png",-3,-5,3,3,sim->world)));
    sim->addMob(dinos["TRex"]);
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}

/**
 * Adds in a basic dino on click if it is not already present.
 * Removes it otherwise.
 * @brief MeteorSlide2::on_dino2Button_clicked
 */
void MeteorSlide2::on_dino2Button_clicked()
{
    dinos.insert(pair<string,Mob*>("dino2",new Mob("../A9/landDinos/dino2.png",-10,-2,2,2,sim->world)));
    sim->addMob(dinos["dino2"]);
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}

/**
 * Adds a pteranodon if not present in the simulation.
 * Removes it otherwise.
 * @brief MeteorSlide2::on_pteranButton_clicked
 */
void MeteorSlide2::on_pteranButton_clicked()
{
    dinos.insert(pair<string,Mob*>("pteranodon",new Mob("../A9/landDinos/pteranodon.png",1, 6, 4, 4,sim->world)));
    sim->addMob(dinos["pteranodon"]);
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}

/**
 * Adds a rock to the simulation.
 * Removes it from simulation otherwise.
 * @brief MeteorSlide2::on_rockButton_clicked
 */
void MeteorSlide2::on_rockButton_clicked()
{
    dinos.insert(pair<string,Mob*>("rock",new Mob("../A9/landDinos/rock.png",0,-8,4,4, sim->world)));
    sim->addMob(dinos["rock"]);
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}


/**
 * Adds in a screaming dinosuar if not already present.
 * Removes it otherwise.
 * @brief MeteorSlide2::on_screamingDino_clicked
 */
void MeteorSlide2::on_screamingDino_clicked()
{
    dinos.insert(pair<string,Mob*>("screamingDino",new Mob("../A9/landDinos/screamingDino.png", -6, -6, 6, 6, sim->world)));
    sim->addMob(dinos["screamingDino"]);
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}


/**
 * Adds a spikey dino if not present in the simulation.
 * Removes the dino otherwise.
 * @brief MeteorSlide2::on_spikeyButton_clicked
 */
void MeteorSlide2::on_spikeyButton_clicked()
{
    dinos.insert(pair<string,Mob*>("spikey",new Mob("../A9/landDinos/spikey.png", -3,-2,2,1, sim->world)));
    sim->addMob(dinos["spikey"]);
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}


/**
 * Adds a tree into the simulation.
 * Removes it otherwise.
 * @brief MeteorSlide2::on_treeButton_clicked
 */
void MeteorSlide2::on_treeButton_clicked()
{
    dinos.insert(pair<string,Mob*>("tree",new Mob("../A9/landDinos/tree.png",9,-5,8,8,sim->world)));
    sim->addMob(dinos["tree"]);
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}
