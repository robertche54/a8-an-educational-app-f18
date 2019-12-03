#ifndef HUBWINDOW_H
#define HUBWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <SFML/Graphics.hpp>

#include <string>

#include "meteorite.h"
#include "mammals.h"
#include "volcano.h"
#include "simulation.h"

namespace Ui { class HubWindow; }
class HubWindow : public QMainWindow
{
    Q_OBJECT

public:
    HubWindow(QWidget *parent = nullptr);
    ~HubWindow();

public slots:
    void metoriteClicked();
    void volcanoClicked();
    void mammalsClicked();
    void recieveFocus() { simulation.toggleRunning(); }
    void togglePhysics() { simulation.toggleRunning(); }

signals:

private:
    Ui::HubWindow *ui;
    Meteorite meteoritePopup;
    Volcano volcanoPopup;
    Mammals mammalsPopup;
    Simulation simulation;

    void paintEvent(QPaintEvent*);
};
#endif // HUBWINDOW_H
