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
    slide1Popup.exec();
}

void Meteorite::on_GroundButton_clicked()
{
    slide2Popup.exec();
}
