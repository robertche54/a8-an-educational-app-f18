#include "hubwindow.h"
#include "ui_hubwindow.h"

HubWindow::HubWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HubWindow)
{
    ui->setupUi(this);

    texture.create(320,180);
    sprite_texture.loadFromFile("/home/jonwarner/CS3505/A9/DinoTitle.png");
    sprite.setTexture(sprite_texture);

    sprite.setOrigin(ui->titleLabel->x(),ui->titleLabel->y());
    sprite.setPosition(ui->titleLabel->x(),ui->titleLabel->y());
    texture.draw(sprite);
    texture.display();

    sf::Texture rt = texture.getTexture();
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
    // EXECUTE METORITE WINDOW
}

void HubWindow::volcanoClicked() {
    // EXECUTE VOLCANO WINDOW
}

void HubWindow::mammalsClicked() {
    // EXECUTE MAMMAL WINDOW
}

sf::Sprite HubWindow::getSprite(std::string file, int x, int y){

}

