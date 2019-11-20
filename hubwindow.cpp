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

    canvas.create(320, 180);

//    b2Vec2 gravity(0.0, -9.81f);
//    b2World world(gravity);
//    Sprite titleSprite("../dino/DinoTitle.png",ui->titleLabel->x(),ui->titleLabel->y(),world);
//    sprites.push_back(titleSprite);

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

    // hard-code animation by creating sprite each time
    b2Vec2 gravity(0.0, -9.81f);
    b2World world(gravity);
    Sprite titleSprite("../A9/DinoTitle.png",ui->titleLabel->x(),ui->titleLabel->y(),world);
    titleSprite.getSprite().rotate(count);
    count++;
    canvas.draw(titleSprite.getSprite());
    // end hard-coded stuff


//   sprites[0].getSprite().rotate(1.0);
//   canvas.draw(sprites[0].getSprite());

    canvas.display();

    sf::Texture rt = canvas.getTexture();
    sf::Image irt = rt.copyToImage();
    const uint8_t *pp = irt.getPixelsPtr();
    QImage q(pp, 320, 180,QImage::Format_ARGB32);
    q = q.rgbSwapped();
    ui->titleLabel->setPixmap(QPixmap::fromImage(q));
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
