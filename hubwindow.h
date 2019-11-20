#ifndef HUBWINDOW_H
#define HUBWINDOW_H

#include <QMainWindow>
#include <SFML/Graphics.hpp>
#include <string>
#include <QImage>
#include "meteorite.h"
#include "mammals.h"
#include "volcano.h"
#include "mob.h"
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
    sf::RenderTexture canvas;
    vector<Mob*> mobs;
    int count = 1;

    b2Vec2 gravity = b2Vec2(0.0, 9.81f);
    b2World world = b2World(gravity);
};
#endif // HUBWINDOW_H
