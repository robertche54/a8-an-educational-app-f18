#include "hubwindow.h"
#include "ui_hubwindow.h"

HubWindow::HubWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HubWindow)
{

    ui->setupUi(this);

    QPixmap background ("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/dinoBackground.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette pal;
    pal.setBrush(QPalette::Background,background);
    this->setPalette(pal);

    b2BodyDef myBodyDef;
    b2FixtureDef myFixtureDef;

    myBodyDef.type = b2_staticBody; //change body type
    myBodyDef.position.Set(0,-10); //middle, bottom

    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(-100,0), b2Vec2(100,0));
    myFixtureDef.shape = &edgeShape;
    b2Body* staticBody = simulation.world.CreateBody(&myBodyDef);
    staticBody->CreateFixture(&myFixtureDef); //add a fixture to the body

    simulation.createMob("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/title2-01.png", 0, 5, 10, 5, "title", b2_dynamicBody);
 //   simulation.createMob("/bricks.jpg", 5, 1, 2, 2, "", b2_staticBody);

    // connecting ui buttons to open popups and toggle if physics is active
    connect(ui->metoriteButton, &QPushButton::pressed, this, &HubWindow::metoriteClicked);
    connect(ui->volcanoButton, &QPushButton::pressed, this, &HubWindow::volcanoClicked);
    connect(ui->mammalButton, &QPushButton::pressed, this, &HubWindow::mammalsClicked);
//    connect(ui->physicsButton, &QPushButton::pressed, this, &HubWindow::togglePhysics);

    // hubWindow enables physics when a popup has closed
    connect(&meteoritePopup, &Meteorite::returnFocus, this, &HubWindow::recieveFocus);
    connect(&volcanoPopup, &Volcano::returnFocus, this, &HubWindow::recieveFocus);
    connect(&mammalsPopup, &Mammals::returnFocus, this, &HubWindow::recieveFocus);

    // explosion and impulse examples, creating the explosion at "" and impulse on "title" works best
//    Mob* title = simulation.namedMobs.at("");
//    simulation.createExplosion(title->body->GetPosition(), 50, 50);
//    Mob* brick = simulation.namedMobs.at("");
//    simulation.createExplosion(brick->body->GetPosition(), 8, 120);
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
    if(simulation.isRunning) {
        simulation.toggleRunning();
    }
    meteoritePopup.exec();
}

void HubWindow::volcanoClicked() {
    if(simulation.isRunning) {
        simulation.toggleRunning();
    }
    volcanoPopup.exec();
}

void HubWindow::mammalsClicked() {
    if(simulation.isRunning) {
        simulation.toggleRunning();
    }
    mammalsPopup.exec();
}
