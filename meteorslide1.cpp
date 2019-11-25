#include "meteorslide1.h"
#include "ui_meteorslide1.h"

MeteorSlide1::MeteorSlide1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeteorSlide1)
{
    ui->setupUi(this);
    QString string1 = "Welcome to the ocean impact page. Press 'Next' to continue!";
    QString string2 = "The ocean impact, like, seriously messed the dinos up.";
    QString string3 = "Well, the ocean didn't impact anything. . .";
    QString string4 = "It was actually the meteorite that impacted the ocean that did it.";
    infoVec.push_back(string1);
    infoVec.push_back(string2);
    infoVec.push_back(string3);
    infoVec.push_back(string4);

    ui->TextLabel->setText(infoVec.front());

}

MeteorSlide1::~MeteorSlide1()
{
    delete ui;
}

void MeteorSlide1::on_NextButton_clicked()
{
    if(infoIndex < infoVec.size() - 1)
    {
        infoIndex++;
        ui->TextLabel->setText(infoVec.at(infoIndex));
    }
}

void MeteorSlide1::on_BackButton_clicked()
{
    if(infoIndex > 0)
    {
        infoIndex--;
        ui->TextLabel->setText(infoVec.at(infoIndex));
    }
}
