#ifndef METEORSLIDE2_H
#define METEORSLIDE2_H

#include <QDialog>
#include <vector>
#include "simulation.h"
#include "ui_meteorslide2.h"
#include "Box2D/Box2D.h"

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
    void addWorldDefinitions();
private slots:
    void on_NextButton_clicked();
    void on_BackButton_clicked();
    void update();
    void changeBackground();
    void on_startButton_clicked();
    void on_reset_clicked();

    //Dino button slots
    void on_TRexButton_clicked();
    void on_dino2Button_clicked();
    void on_pteranButton_clicked();
    void on_rockButton_clicked();
    void on_screamingDino_clicked();
    void on_spikeyButton_clicked();
    void on_treeButton_clicked();

private:
    Ui::MeteorSlide2 *ui;
    int infoIndex = 0;
    int backgroundIndex = 0;
    QTimer* backGroundTimer;
    QTimer* worldTimer;
    Simulation* sim;
    map<string,Mob*> dinos;

    // Info Slides
    vector<QString> infoVec{
        "According to abundant geological evidence, an asteroid roughly "
            "10 km (6 miles) across hit Earth about 65 million years ago.",
        "This impact made a huge explosion and a crater about 180 km (roughly 110 miles) across.",
        "During the impact, the kinetic energy in the asteroid blew debris of dust, soil, and rocks not only into the atmosphere, "
            "but out into space, where it fell back into the top layer of the atmosphere.",
        "The debris blocked out the sun, disrupting photosynthesis in most plant species for several months. This, in turn, reduced "
            "the amount of available food and severely disrupted the food chain.",
        "Thus, the extinction of roughly 3/4 of species on earth incurred, including the dinosaurs. ",
        "Recent research has shown that for the first few hours after the impact, rocky debris would have fallen back into "
            "the high atmosphere, creating a storm of glowing fireballs in the sky.",
        "The radiant energy from these fireballs would have heated the surface to boiling temperatures for some minutes, and "
            "would have been enough to kill many animals and plants on the surface in dry regions."
     };

};

#endif // METEORSLIDE2_H
