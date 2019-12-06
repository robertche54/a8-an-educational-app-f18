#include <QStringList>
#include <QString>
#include "volcano.h"
#include "ui_volcano.h"

Volcano::Volcano(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Volcano)
{
    ui->setupUi(this);

    QStringList volcanoList = (QStringList()<<"0: Kilauea (1977)"<<"1: Nyiragongo (2002)"<<"2: Unzen (1792)"
                               <<"3: Nevado del Ruiz (1985)"<<"4: Laki (1783)"<<"5: St. Helens (1980)"
                               <<"6: Krakatoa (1883)"<<"7: Tambora (1815)"<<"8: Yellowstone (630,000 BC)");

    QString part1 = "Across the many theories that include volcanos, the Deccan Traps in India are often pointed to as the culprit."
                    "These now-dormant volcanos were active roughly 400,000 years before the meteorite hit to roughly 600,000 years after the impact.";
    QString part2 = "These theories suggest that the greenhouse gasses and atmospheric particles released by volcanic activity had started to cause changes in the climate before the impact."
                    "These gasses and particles increased the average temperature around the globe, and the dinosaurs struggled to adapt.";
    QString part3 = "The meteorite finished the job by releasing an extreme amount of dust into the atmosphere, sending the Earth into a long nuclear winter."
                    "This sudden change in climate was too much for the dinosaurs, who were adapting to a warming climate.";
    //QString part4 = "Jeez this is getting long winded";
    infoVec.push_back(part1);
    infoVec.push_back(part2);
    infoVec.push_back(part3);
    //infoVec.push_back(part4);

    ui->powerSelector->addItems(volcanoList);

//    ui->explodeButton->setIcon(QIcon("../A9/unknown.png"));
//    ui->explodeButton->setIconSize(QSize(ui->explodeButton->size()));

    QPixmap pixmap("../A9/volcanoSky.jpeg");
    pixmap = pixmap.scaled(ui->backgroundLabel->size(), Qt::IgnoreAspectRatio);
    ui->backgroundLabel->setPixmap(pixmap);

    QPixmap volcanoCover("../A9/volcano.jpeg");
    volcanoCover = volcanoCover.scaled(ui->volcanoLabel->size(), Qt::IgnoreAspectRatio);
    ui->volcanoLabel->setPixmap(volcanoCover);

    connect(ui->explodeButton, &QPushButton::pressed, this, &Volcano::explodeClicked);
    connect(ui->resetButton, &QPushButton::pressed, this, &Volcano::clearSimulation);
    connect(ui->nextButton, &QPushButton::pressed, this, &Volcano::nextSlide);
    connect(ui->previousButton, &QPushButton::pressed, this, &Volcano::previousSlide);
}

Volcano::~Volcano()
{
    delete ui;
}

void Volcano::showEvent(QShowEvent *) {
    initializeSimulation();
}

void Volcano::closeEvent(QCloseEvent*) {
    simulation.clearSimulation();
    simulation.world.DestroyBody(groundBody);
    infoIndex = 0;
    emit returnFocus();
}

void Volcano::paintEvent(QPaintEvent*)
{
    QImage newImage = simulation.step();
    ui->simulationLabel->setPixmap(QPixmap::fromImage(newImage));
}

void Volcano::explodeClicked() {
    Mob* brick = simulation.namedMobs.at("brick");
    float powerselected;

    // value/index corrosponds with the volanco's explosivity index
    if(ui->customCheck->isChecked()) {
        powerselected = 50 + float(pow(3, ui->customPower->value()));
    }
    else {

        powerselected = 50 + float(pow(3, ui->powerSelector->currentIndex()));
    }
    simulation.createExplosion(brick->body->GetPosition(), powerselected, 120);
}

void Volcano::clearSimulation() {

    simulation.clearSimulation();
    simulation.world.DestroyBody(groundBody);
    initializeSimulation();
}

void Volcano::nextSlide() {
    if (infoIndex < infoVec.size() - 1) {
        ++infoIndex;
        ui->infoLabel->setText(infoVec.at(infoIndex));
    }
}

void Volcano::previousSlide() {
    if (infoIndex > 0) {
        --infoIndex;
        ui->infoLabel->setText(infoVec.at(infoIndex));
    }
}

void Volcano::initializeSimulation() {
   simulation.isRunning = true;
   ui->infoLabel->setText(infoVec.at(infoIndex));

   b2BodyDef groundBodyDef;

   b2FixtureDef groundFixtureDef;

    groundBodyDef.type = b2_staticBody; //change body type
    groundBodyDef.position.Set(0,-20); //middle, bottom

    b2EdgeShape groundShape;
    groundShape.Set(b2Vec2(-100,0), b2Vec2(100,0));
    groundFixtureDef.shape = &groundShape;
    groundBody = simulation.world.CreateBody(&groundBodyDef);
    groundBody->CreateFixture(&groundFixtureDef); //add a fixture to the body

    simulation.setGravity(0.0f, -1000.0f);
    simulation.tf.setWindowSize(600, 500);
    simulation.tf.setBox2dWindow(b2Vec2(-20,20),b2Vec2(20, -20));
    simulation.createMob("../A9/lava2.png", 0.0f, -19.0f, 1.0f, 1.0f, "brick", b2_dynamicBody);

    for(float x = -8; x < 8; x += .8f) {
        for(float y = -18; y < -7; y += .8f) {
            simulation.createMob("../A9/Lava.png", x, y, .5f, b2_dynamicBody);
        }
    }
    //creation of volcano test
    //simulation.createMob("../A9/otherimage.png", -10, 10, 2.0f, b2_dynamicBody);
    //simulation.createMob("../A9/lava2.png", -10, 10, 2.0f, b2_dynamicBody);

        vector<b2Vec2> leftVolcano;
        vector<b2Vec2> rightVolcano;

        b2Vec2 vert1(-10, -10);
        leftVolcano.push_back(vert1);
        b2Vec2 vert2(11, -10);
        leftVolcano.push_back(vert2);
        b2Vec2 vert3(9, 9);
        leftVolcano.push_back(vert3);

        b2Vec2 cert1(-9, 9);
        rightVolcano.push_back(cert1);
        b2Vec2 cert2(-11, -10);
        rightVolcano.push_back(cert2);
        b2Vec2 cert3(10, -10);
        rightVolcano.push_back(cert3);

      simulation.createMob("../A9/volcanoleft.png", -16, -12, leftVolcano, b2_staticBody);
      simulation.createMob("../A9/volcanoright.png", 16, -12, rightVolcano, b2_staticBody);
}
