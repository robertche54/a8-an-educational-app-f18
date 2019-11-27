#ifndef MAMMALS_H
#define MAMMALS_H

#include <QDialog>

#include <simulation.h>
#include <creaturecollisionhandler.h>

namespace Ui { class Mammals; }

class Mammals : public QDialog
{
    Q_OBJECT

public:
    explicit Mammals(QWidget *parent = nullptr);
    ~Mammals();

private:
    Ui::Mammals *ui;
    CreatureCollisionHandler* handler;
    Simulation simulation;

    void paintEvent(QPaintEvent*);
public slots:
    void physicsUpdate();
};

#endif // MAMMALS_H
