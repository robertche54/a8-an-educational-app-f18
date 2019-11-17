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
