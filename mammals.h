#ifndef MAMMALS_H
#define MAMMALS_H

#include <QDialog>

namespace Ui {
class Mammals;
}

class Mammals : public QDialog
{
    Q_OBJECT

public:
    explicit Mammals(QWidget *parent = nullptr);
    ~Mammals();

private:
    Ui::Mammals *ui;
};

#endif // MAMMALS_H
