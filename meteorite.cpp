#include "meteorite.h"
#include "ui_meteorite.h"

Meteorite::Meteorite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Meteorite)
{
    ui->setupUi(this);

    QPixmap background ("/home/spencer/CS3505/A9/a8-an-educational-app-f18-LandonRoundy/Earth.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette pal;
    pal.setBrush(QPalette::Background,background);
    this->setPalette(pal);
}

Meteorite::~Meteorite()
{
    delete ui;
}

void Meteorite::on_OceanButton_clicked()
{
    MeteorSlide1 slide1;
    slide1.exec();
}

void Meteorite::on_GroundButton_clicked()
{
    MeteorSlide2 slide2;
    slide2.exec();
}

void Meteorite::closeEvent(QCloseEvent*) {
    emit returnFocus();
}
