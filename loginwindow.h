#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class loginwindow; }
QT_END_NAMESPACE

class loginwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = nullptr);
    ~loginwindow();
private slots:
    void handleLogin();
    void handleSignup();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::loginwindow *ui;
};

#endif
