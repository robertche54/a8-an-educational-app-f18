#ifndef METEORSLIDE1_H
#define METEORSLIDE1_H

#include <QDialog>

namespace Ui {
class MeteorSlide1;
}

class MeteorSlide1 : public QDialog
{
    Q_OBJECT

public:
    explicit MeteorSlide1(QWidget *parent = nullptr);
    ~MeteorSlide1();

private:
    Ui::MeteorSlide1 *ui;
};

#endif // METEORSLIDE1_H
