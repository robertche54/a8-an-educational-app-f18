#ifndef VOLCANO_H
#define VOLCANO_H

#include <QDialog>
#include <QCloseEvent>
#include "simulation.h"

namespace Ui {
class Volcano;
}

class Volcano : public QDialog
{
    Q_OBJECT

public:
    explicit Volcano(QWidget *parent = nullptr);
    ~Volcano();

public slots:
    void explodeClicked();
    void clearSimulation();

signals :
    void returnFocus();

private:
    Ui::Volcano *ui;
    Simulation simulation;
    b2Body* groundBody;
    b2Body* leftWallBody;
    b2Body* rightWallBody;
    bool earthQuake = true;
    int windowH = 200;
    int windowW = 200;

    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent*);
    void paintEvent(QPaintEvent*);
    void initializeSimulation();
};

#endif // VOLCANO_H
