#ifndef MAMMALS_H
#define MAMMALS_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class Mammals;
}

class Mammals : public QDialog
{
    Q_OBJECT

public:
    explicit Mammals(QWidget *parent = nullptr);
    ~Mammals();

signals:
    void returnFocus();

private:
    Ui::Mammals *ui;

    void closeEvent(QCloseEvent *);
};

#endif // MAMMALS_H
