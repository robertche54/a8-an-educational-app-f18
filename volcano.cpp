#include "volcano.h"
#include "ui_volcano.h"

Volcano::Volcano(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Volcano)
{
    ui->setupUi(this);
}

Volcano::~Volcano()
{
    delete ui;
}

void Volcano::explodeClicked() {

}
