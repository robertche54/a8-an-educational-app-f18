#ifndef METEORSLIDE2_H
#define METEORSLIDE2_H

#include <QDialog>

namespace Ui {
class MeteorSlide2;
}

class MeteorSlide2 : public QDialog
{
    Q_OBJECT

public:
    explicit MeteorSlide2(QWidget *parent = nullptr);
    ~MeteorSlide2();

private:
    Ui::MeteorSlide2 *ui;
};

#endif // METEORSLIDE2_H
