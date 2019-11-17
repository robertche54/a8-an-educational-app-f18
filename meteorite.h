#ifndef METEORITE_H
#define METEORITE_H

#include <QDialog>

namespace Ui {
class Meteorite;
}

class Meteorite : public QDialog
{
    Q_OBJECT

public:
    explicit Meteorite(QWidget *parent = nullptr);
    ~Meteorite();

private:
    Ui::Meteorite *ui;
};

#endif // METEORITE_H
