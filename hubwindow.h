#ifndef HUBWINDOW_H
#define HUBWINDOW_H

#include <QMainWindow>
#include <SFML/Graphics.hpp>
#include <string>
#include <QImage>
#include "meteorite.h"
#include "mammals.h"
#include "volcano.h"
#include "simulation.h"
#include <QTimer>

namespace Ui { class HubWindow; }
class HubWindow : public QMainWindow
{
    Q_OBJECT

public:
    HubWindow(QWidget *parent = nullptr);
    ~HubWindow();
    sf::Sprite setSprite(std::string, int, int);

public slots:
    void metoriteClicked();
    void volcanoClicked();
    void mammalsClicked();
    void wiggleTitle();

signals:

private:
    Ui::HubWindow *ui;
    Meteorite meteoritePopup;
    Volcano volcanoPopup;
    Mammals mammalsPopup;
    Simulation simulation;
    windowTransform tf;
};
#endif // HUBWINDOW_H
