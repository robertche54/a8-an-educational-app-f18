#include "meteorslide2.h"
#include "ui_meteorslide2.h"

MeteorSlide2::MeteorSlide2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeteorSlide2)
{
    ui->setupUi(this);
    QString string1 = "Welcome to the ground impact page. Press 'Next' to continue!";
    QString string2 = "The ground impact, like, seriously messed the dinos up.";
    QString string3 = "Well, the ground didn't impact anything. . .";
    QString string4 = "It was actually the meteorite that impacted the ground that did it.";
    infoVec.push_back(string1);
    infoVec.push_back(string2);
    infoVec.push_back(string3);
    infoVec.push_back(string4);

    ui->TextLabel->setText(infoVec.front());
}

MeteorSlide2::~MeteorSlide2()
{
    delete ui;
}

void MeteorSlide2::on_NextButton_clicked()
{
    if(infoIndex < infoVec.size() - 1)
    {
        infoIndex++;
        ui->TextLabel->setText(infoVec.at(infoIndex));
    }
}

void MeteorSlide2::on_BackButton_clicked()
{
    if(infoIndex > 0)
    {
        infoIndex--;
        ui->TextLabel->setText(infoVec.at(infoIndex));
    }
}
