#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuWindow;
}
QT_END_NAMESPACE

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();
     void ensureProductFileExists();
     void on_addbutton_clicked();
     void on_updatebutton_clicked();
     void on_deletebutton_clicked();
     void on_viewbutton_2_clicked();
     void handleLogout();
    void on_createbutton_clicked();
private:
    Ui::MenuWindow *ui;
};
#endif// MENUWINDOW_H
