#include "hubwindow.h"
#include "ui_hubwindow.h"

HubWindow::HubWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HubWindow)
    , tf(b2Vec2(-10,10),b2Vec2(10,-10),320,180)
{

    ui->setupUi(this); 

    b2BodyDef myBodyDef;
    b2FixtureDef myFixtureDef;

    myBodyDef.type = b2_staticBody; //change body type
    myBodyDef.position.Set(0,-10); //middle, bottom

    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(-100,0), b2Vec2(100,0));
    myFixtureDef.shape = &edgeShape;
    b2Body* staticBody = simulation.world.CreateBody(&myBodyDef);
    staticBody->CreateFixture(&myFixtureDef); //add a fixture to the body

    simulation.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/DinoTitle.png", 0, 5, 15, 5, "title", b2_dynamicBody);
    simulation.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/bricks.jpg", 5, 1, 2, 2, "", b2_staticBody);

    connect(ui->metoriteButton, &QPushButton::pressed, this, &HubWindow::metoriteClicked);
    connect(ui->volcanoButton, &QPushButton::pressed, this, &HubWindow::volcanoClicked);
    connect(ui->mammalButton, &QPushButton::pressed, this, &HubWindow::mammalsClicked);
//    connect(ui->physicsButton, &QPushButton::pressed, this, &HubWindow::togglePhysics);

    // explosion and impulse examples, creating the explosion at "" and impulse on "title" works best
    Mob* title = simulation.namedMobs.at("");
    simulation.createExplosion(title->body->GetPosition(), 50, 50);
    //simulation.applyImpulse(title, 135, 12.0f);
}

void HubWindow::paintEvent(QPaintEvent*)
{

    QImage newImage = simulation.step();
    ui->titleLabel->setPixmap(QPixmap::fromImage(newImage));
}

HubWindow::~HubWindow()
{
    delete ui;
}

void HubWindow::metoriteClicked() {
    meteoritePopup.exec();
}

void HubWindow::volcanoClicked() {
    volcanoPopup.exec();
}

void HubWindow::mammalsClicked() {
    mammalsPopup.exec();
}
