#ifndef VOLCANO_H
#define VOLCANO_H

#include <QDialog>

namespace Ui {
class Volcano;
}

class Volcano : public QDialog
{
    Q_OBJECT

public:
    explicit Volcano(QWidget *parent = nullptr);
    ~Volcano();

private:
    Ui::Volcano *ui;
};

#endif // VOLCANO_H
