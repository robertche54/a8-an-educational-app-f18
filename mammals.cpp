#include "mammals.h"
#include "ui_mammals.h"

Mammals::Mammals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mammals)
{
    ui->setupUi(this);
}

Mammals::~Mammals()
{
    delete ui;
}

void Mammals::closeEvent(QCloseEvent *) {
    emit returnFocus();
}
