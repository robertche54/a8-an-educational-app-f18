#ifndef MAMMALS_H
#define MAMMALS_H

#include <QDialog>
#include <QCloseEvent>
#include <QTimer>

#include <simulation.h>
#include <creaturecollisionhandler.h>

namespace Ui { class Mammals; }

class Mammals : public QDialog
{
    Q_OBJECT

public:
    explicit Mammals(QWidget *parent = nullptr);
    ~Mammals();

signals:
    void returnFocus();

private:
    Ui::Mammals *ui;
    CreatureCollisionHandler* handler;
    Simulation simulation;

    void populateWorld(float xRange, float yRange, int plants, int mammals, int dinos);
    void clearWorld();
    void addMammal(float x, float y);
    void addDino(float x, float y);
    void addPlant(float x, float y);

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);

public slots:
    void physicsUpdate();
    void runSimulation();

    void closeEvent(QCloseEvent *);
};

#endif // MAMMALS_H
