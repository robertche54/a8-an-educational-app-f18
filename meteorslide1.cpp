#include "meteorslide1.h"
#include "ui_meteorslide1.h"

MeteorSlide1::MeteorSlide1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeteorSlide1)
{
    ui->setupUi(this);
}

MeteorSlide1::~MeteorSlide1()
{
    delete ui;
}
