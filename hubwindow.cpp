#include "hubwindow.h"
#include "ui_hubwindow.h"

HubWindow::HubWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HubWindow)
{
    ui->setupUi(this);

    connect(ui->metoriteButton, &QPushButton::pressed, this, &HubWindow::metoriteClicked);
    connect(ui->volcanoButton, &QPushButton::pressed, this, &HubWindow::volcanoClicked);
    connect(ui->mammalButton, &QPushButton::pressed, this, &HubWindow::mammalsClicked);
}

HubWindow::~HubWindow()
{
    delete ui;
}

void HubWindow::metoriteClicked() {
    // EXECUTE METORITE WINDOW
}

void HubWindow::volcanoClicked() {
    // EXECUTE VOLCANO WINDOW
}

void HubWindow::mammalsClicked() {
    // EXECUTE MAMMAL WINDOW
}
