#ifndef HUBWINDOW_H
#define HUBWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class HubWindow; }
QT_END_NAMESPACE

class HubWindow : public QMainWindow
{
    Q_OBJECT

public:
    HubWindow(QWidget *parent = nullptr);
    ~HubWindow();

private:
    Ui::HubWindow *ui;
};
#endif // HUBWINDOW_H
