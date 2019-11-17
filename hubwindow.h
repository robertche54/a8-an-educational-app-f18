#ifndef HUBWINDOW_H
#define HUBWINDOW_H

#include <QMainWindow>
#include <SFML/Graphics.hpp>
#include <string>
#include <QImage>
#include "meteorite.h"
#include "mammals.h"
#include "volcano.h"

namespace Ui { class HubWindow; }

class HubWindow : public QMainWindow
{
    Q_OBJECT

public:
    HubWindow(QWidget *parent = nullptr);
    ~HubWindow();
    sf::Sprite getSprite(std::string, int, int);
public slots:
    void metoriteClicked();
    void volcanoClicked();
    void mammalsClicked();

signals:
private:
    Ui::HubWindow *ui;
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    sf::Sprite sprite;
    Meteorite meteoritePopup;
    Volcano volcanoPopup;
    Mammals mammalsPopup;
};
#endif // HUBWINDOW_H
