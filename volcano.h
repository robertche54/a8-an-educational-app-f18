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

signals :
    void returnFocus();

private:
    Ui::Volcano *ui;
    Simulation simulation;

    void closeEvent(QCloseEvent*);
    void paintEvent(QPaintEvent*);
};

#endif // VOLCANO_H
