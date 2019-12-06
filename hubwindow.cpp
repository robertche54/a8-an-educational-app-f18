#include "hubwindow.h"
#include "ui_hubwindow.h"

HubWindow::HubWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HubWindow)
{

    ui->setupUi(this);

    QPixmap background ("../A9/dinoBackground.jpg");
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

    simulation.createMob("../A9/title2-01.png", 0, 10, 20, 10, "title", b2_dynamicBody);

    // connecting ui buttons to open popups and toggle if physics is active
    connect(ui->meteoriteButton, &QPushButton::pressed, this, &HubWindow::metoriteClicked);
    connect(ui->volcanoButton, &QPushButton::pressed, this, &HubWindow::volcanoClicked);
    connect(ui->mammalButton, &QPushButton::pressed, this, &HubWindow::mammalsClicked);
//    connect(ui->physicsButton, &QPushButton::pressed, this, &HubWindow::togglePhysics);

    // hubWindow enables physics when a popup has closed
    connect(&meteoritePopup, &Meteorite::returnFocus, this, &HubWindow::recieveFocus);
    connect(&volcanoPopup, &Volcano::returnFocus, this, &HubWindow::recieveFocus);
    connect(&mammalsPopup, &Mammals::returnFocus, this, &HubWindow::recieveFocus);

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
