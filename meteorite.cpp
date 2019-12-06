#include "meteorite.h"
#include "ui_meteorite.h"

Meteorite::Meteorite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Meteorite)
{
    ui->setupUi(this);
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
