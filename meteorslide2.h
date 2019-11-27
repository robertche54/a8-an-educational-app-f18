#ifndef METEORSLIDE2_H
#define METEORSLIDE2_H

#include <QDialog>
#include <vector>
#include "simulation.h"
#include <QTimer>

using namespace std;

namespace Ui {
class MeteorSlide2;
}

class MeteorSlide2 : public QDialog
{
    Q_OBJECT
public:
    explicit MeteorSlide2(QWidget *parent = nullptr);
    ~MeteorSlide2();
    void addElements();
private slots:
    void on_NextButton_clicked();
    void on_BackButton_clicked();
    void update();
    void changeBackground();
    void on_startButton_clicked();
    void selectDinoCount(int);
private:
    Ui::MeteorSlide2 *ui;
    int infoIndex = 0;
    int backgroundIndex = 0;
    QTimer* backGroundTimer;
    Simulation sim;
    vector<QString> infoVec{ "Welcome to the ground impact page. Press 'Next' to continue!",
                           "The ground impact, like, seriously messed the dinos up.",
                           "Well, the ground didn't impact anything. . .",
                           "It was actually the meteorite that impacted the ground that did it."};

};

#endif // METEORSLIDE2_H
