#include "hubwindow.h"
#include "ui_hubwindow.h"
#include <QImage>

HubWindow::HubWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HubWindow)
{
    ui->setupUi(this);

    texture.create(320,180);
    sprite_texture.loadFromFile("/home/jonwarner/CS3505/A9/DinoTitle.png");
    sprite.setTexture(sprite_texture);

    sprite.setOrigin(ui->label->x(),ui->label->y());
    sprite.setPosition(ui->label->x(),ui->label->y());
    texture.draw(sprite);
    texture.display();

    sf::Texture rt = texture.getTexture();
    sf::Image irt = rt.copyToImage();
    const uint8_t *pp = irt.getPixelsPtr();
    QImage q(pp, 320, 180,QImage::Format_ARGB32);
    q = q.rgbSwapped();
    ui->label->setPixmap(QPixmap::fromImage(q));
}

HubWindow::~HubWindow()
{
    delete ui;
}



