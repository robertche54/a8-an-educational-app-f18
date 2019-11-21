#include "meteorslide2.h"
#include "ui_meteorslide2.h"

MeteorSlide2::MeteorSlide2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeteorSlide2)
{
    ui->setupUi(this);
}

MeteorSlide2::~MeteorSlide2()
{
    delete ui;
}
