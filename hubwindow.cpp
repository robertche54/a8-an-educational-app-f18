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
{
    ui->setupUi(this); 

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(500.0f, 400.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(5000.0f, 15.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);


    b2EdgeShape leftEdge;
    leftEdge.Set(b2Vec2(0.0f,-1000.0f), b2Vec2(0.0f,1000.0f));

    canvas.create(500, 500);
    Mob* titleSprite = new Mob("../A9/DinoTitle.png",ui->titleLabel->x(),ui->titleLabel->y(),world);
    mobs.push_back(titleSprite);
//    titleSprite->body->SetAngularVelocity(0.5);

    QTimer *timer;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HubWindow::wiggleTitle);
    timer->start(1);

    connect(ui->metoriteButton, &QPushButton::pressed, this, &HubWindow::metoriteClicked);
    connect(ui->volcanoButton, &QPushButton::pressed, this, &HubWindow::volcanoClicked);
    connect(ui->mammalButton, &QPushButton::pressed, this, &HubWindow::mammalsClicked);

}

void HubWindow::wiggleTitle(){
    canvas.clear();

    world.Step(1 / 60.0f, 8, 3);

    for(Mob* s : mobs) {
        s->Update();
        canvas.draw(s->getSprite());
    }

    canvas.display();

    sf::Texture rt = canvas.getTexture();
    sf::Image irt = rt.copyToImage();
    const uint8_t *pp = irt.getPixelsPtr();
    QImage q(pp, 500, 500,QImage::Format_ARGB32);
    q = q.rgbSwapped();
    ui->titleLabel->setPixmap(QPixmap::fromImage(q));
}

HubWindow::~HubWindow()
{
    for (Mob* s : mobs) {
        //delete s;
    }

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
