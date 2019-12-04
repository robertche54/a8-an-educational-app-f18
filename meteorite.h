#ifndef METEORITE_H
#define METEORITE_H

#include <QDialog>
#include <QCloseEvent>
#include "meteorslide1.h"
#include "meteorslide2.h"

namespace Ui {
class Meteorite;
}

class Meteorite : public QDialog
{
    Q_OBJECT

public:
    explicit Meteorite(QWidget *parent = nullptr);
    ~Meteorite();

signals:
    void returnFocus();

private slots:
    void on_OceanButton_clicked();
    void on_GroundButton_clicked();

private:
    Ui::Meteorite *ui;
    void closeEvent(QCloseEvent*);
};

#endif // METEORITE_H
