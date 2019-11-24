#include "hubwindow.h"
#include "ui_hubwindow.h"
#include "mammals.h"
#include "volcano.h"
#include "meteorite.h"
#include <QThread>
#include <QTimer>

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

    simulation.createMob("../a8-an-educational-app-f18-LandonRoundy/DinoTitle.png", 0, 10, 15, 5);
    simulation.createMob("../a8-an-educational-app-f18-LandonRoundy/bricks.jpg", 5, 2, 4, 4, "", b2_staticBody);

    QTimer *timer;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HubWindow::wiggleTitle);
    timer->start(1000/60);

    connect(ui->metoriteButton, &QPushButton::pressed, this, &HubWindow::metoriteClicked);
    connect(ui->volcanoButton, &QPushButton::pressed, this, &HubWindow::volcanoClicked);
    connect(ui->mammalButton, &QPushButton::pressed, this, &HubWindow::mammalsClicked);

}

void HubWindow::wiggleTitle(){

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

sf::Sprite HubWindow::setSprite(std::string file, int x, int y){

}
