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
    Simulation sim;
private slots:
    void on_NextButton_clicked();

    void on_BackButton_clicked();
    void update();

private:
    Ui::MeteorSlide2 *ui;
    vector<QString> infoVec;
    int infoIndex = 0;
};

#endif // METEORSLIDE2_H
