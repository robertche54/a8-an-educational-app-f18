#ifndef METEORSLIDE1_H
#define METEORSLIDE1_H

#include <QDialog>
#include <vector>

using namespace std;

namespace Ui {
class MeteorSlide1;
}

class MeteorSlide1 : public QDialog
{
    Q_OBJECT

public:
    explicit MeteorSlide1(QWidget *parent = nullptr);
    ~MeteorSlide1();

private slots:
    void on_NextButton_clicked();

    void on_BackButton_clicked();

private:
    Ui::MeteorSlide1 *ui;
    vector<QString> infoVec;
    int infoIndex = 0;
};

#endif // METEORSLIDE1_H
