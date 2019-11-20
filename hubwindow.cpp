#include "hubwindow.h"
#include "ui_hubwindow.h"
#include "mammals.h"
#include "volcano.h"
#include "meteorite.h"
#include <QThread>

HubWindow::HubWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HubWindow)
{
    ui->setupUi(this);
    b2Vec2 gravity(0.0, -9.81f);
    b2World world(gravity);
    Sprite titleSprite("../DinoDisasters/DinoTitle.png",320,180,ui->titleLabel->x(),ui->titleLabel->y(),world);
    sf::Texture rt = titleSprite.texture.getTexture();
    sf::Image irt = rt.copyToImage();
    const uint8_t *pp = irt.getPixelsPtr();
    QImage q(pp, 320, 180,QImage::Format_ARGB32);
    q = q.rgbSwapped();
    ui->titleLabel->setPixmap(QPixmap::fromImage(q));

    connect(ui->metoriteButton, &QPushButton::pressed, this, &HubWindow::metoriteClicked);
    connect(ui->volcanoButton, &QPushButton::pressed, this, &HubWindow::volcanoClicked);
    connect(ui->mammalButton, &QPushButton::pressed, this, &HubWindow::mammalsClicked);

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

void HubWindow::wiggleTitle(Sprite &titleSprite, int rotate){

}

