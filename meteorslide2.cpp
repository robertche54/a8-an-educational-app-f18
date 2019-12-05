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

    addWorldDefinitions();
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}

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



/**
 * Starts the timer for the world stepping and the background to chang
 * as the meteorite impacts the earth.
 * @brief MeteorSlide2::on_startButton_clicked
 */
void MeteorSlide2::on_startButton_clicked(){
    sim->isRunning = true;
    sim->setGravity(0,-9.81f);

    // Add meteor mob
    sim->createMob("../A9/meteorite.png",45,50,10,10,"meteor", b2_dynamicBody);
    Mob* meteor = sim->namedMobs.at("meteor");
    sim->applyImpulse(meteor,235,150);

    // Steping timer to call update
    worldTimer = new QTimer(this);
    connect(worldTimer, &QTimer::timeout, this, &MeteorSlide2::update);
    worldTimer->start(1000/60);

    backGroundTimer = new QTimer();
    connect(backGroundTimer, &QTimer::timeout, this, &MeteorSlide2::changeBackground);
    backGroundTimer->start(400);
}


/**
 * Clears the simulation and sets it to its defualt appearance.
 * @brief MeteorSlide2::on_reset_clicked
 */
void MeteorSlide2::on_reset_clicked(){
    worldTimer->stop();
    sim = new Simulation();
    dinos.clear();
    TRexActive = dino2Active = pterActive = screamingDinoActive = spikeyActive = rockActive = treeActive = false;
    addWorldDefinitions();
    ui->backLabel->setPixmap(QPixmap("../A9/dinoscene0.jpg"));
    backgroundIndex=0;
}



/**
 * Adds in a TRex if it does not already exist in the
 * simulation. Removes it otherwise
 * @brief MeteorSlide2::on_TRexButton_clicked
 */
void MeteorSlide2::on_TRexButton_clicked()
{
    if(TRexActive){
        Mob* temp = dinos["TRex"];
        dinos.erase("TRex");
        sim->world.DestroyBody(temp->body);
    }else{
        dinos.insert(pair<string,Mob*>("TRex",new Mob("../A9/landDinos/TRex.png",-3,-5,2,2,sim->world)));
        sim->addMob(dinos["TRex"]);
    }
    TRexActive = TRexActive ? false : true;
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}

/**
 * Adds in a basic dino on click if it is not already present.
 * Removes it otherwise.
 * @brief MeteorSlide2::on_dino2Button_clicked
 */
void MeteorSlide2::on_dino2Button_clicked()
{
    if(dino2Active){
        Mob* temp = dinos["dino2"];
        dinos.erase("dino2");
        sim->world.DestroyBody(temp->body);
    }else{
        dinos.insert(pair<string,Mob*>("dino2",new Mob("../A9/landDinos/dino2.png",-8,-2,2,2,sim->world)));
        sim->addMob(dinos["dino2"]);
    }
    dino2Active = dino2Active ? false : true;
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}

/**
 * Adds a pteranodon if not present in the simulation.
 * Removes it otherwise.
 * @brief MeteorSlide2::on_pteranButton_clicked
 */
void MeteorSlide2::on_pteranButton_clicked()
{
    if(pterActive){
        Mob* temp = dinos["pteranodon"];
        dinos.erase("pteranodon");
        sim->world.DestroyBody(temp->body);
    }else{
       dinos.insert(pair<string,Mob*>("pteranodon",new Mob("../A9/landDinos/pteranodon.png",2, 6, 2, 2,sim->world)));
       sim->addMob(dinos["pteranodon"]);
    }
    pterActive = pterActive ? false : true;
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}

/**
 * Adds a rock to the simulation.
 * Removes it from simulation otherwise.
 * @brief MeteorSlide2::on_rockButton_clicked
 */
void MeteorSlide2::on_rockButton_clicked()
{
    if(rockActive){
        Mob* temp = dinos["rock"];
        dinos.erase("rock");
        sim->world.DestroyBody(temp->body);
    }else{
        dinos.insert(pair<string,Mob*>("rock",new Mob("../A9/landDinos/rock.png",2,-9,4,4, sim->world)));
        sim->addMob(dinos["rock"]);
    }
    rockActive = rockActive ? false : true;
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}


/**
 * Adds in a screaming dinosuar if not already present.
 * Removes it otherwise.
 * @brief MeteorSlide2::on_screamingDino_clicked
 */
void MeteorSlide2::on_screamingDino_clicked()
{
    if(screamingDinoActive){
        Mob* temp = dinos["screamingDino"];
        dinos.erase("screamingDino");
        sim->world.DestroyBody(temp->body);
    }else{
        dinos.insert(pair<string,Mob*>("screamingDino",new Mob("../A9/landDinos/screamingDino.png", -8, -4, 3, 3, sim->world)));
        sim->addMob(dinos["screamingDino"]);
    }
    screamingDinoActive = screamingDinoActive ? false : true;
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}


/**
 * Adds a spikey dino if not present in the simulation.
 * Removes the dino otherwise.
 * @brief MeteorSlide2::on_spikeyButton_clicked
 */
void MeteorSlide2::on_spikeyButton_clicked()
{
    if(spikeyActive){
        Mob* temp = dinos["spikey"];
        dinos.erase("spikey");
        sim->world.DestroyBody(temp->body);
    }else{
        dinos.insert(pair<string,Mob*>("spikey",new Mob("../A9/landDinos/spikey.png", -4,-2,2,1, sim->world)));
        sim->addMob(dinos["spikey"]);
    }
    spikeyActive = spikeyActive ? false : true;
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}


/**
 * Adds a tree into the simulation.
 * Removes it otherwise.
 * @brief MeteorSlide2::on_treeButton_clicked
 */
void MeteorSlide2::on_treeButton_clicked()
{
    if(treeActive){
        Mob* temp = dinos["tree"];
        dinos.erase("tree");
        sim->world.DestroyBody(temp->body);
    }else{
        dinos.insert(pair<string,Mob*>("tree",new Mob("../A9/landDinos/tree.png",8,-8,10,10,sim->world)));
        sim->addMob(dinos["tree"]);
    }
    treeActive = treeActive ? false : true;
    ui->AnimationLabel->setPixmap(QPixmap::fromImage(sim->step()));
}
