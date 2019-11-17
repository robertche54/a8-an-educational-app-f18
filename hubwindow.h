#ifndef HUBWINDOW_H
#define HUBWINDOW_H

#include <QMainWindow>
#include "meteorite.h"
#include "mammals.h"
#include "volcano.h"

namespace Ui { class HubWindow; }

class HubWindow : public QMainWindow
{
    Q_OBJECT

public:
    HubWindow(QWidget *parent = nullptr);
    ~HubWindow();

public slots:
    void metoriteClicked();
    void volcanoClicked();
    void mammalsClicked();

signals:

private:
    Ui::HubWindow *ui;
    Meteorite meteoritePopup;
    Volcano volcanoPopup;
    Mammals mammalsPopup;
};
#endif // HUBWINDOW_H
