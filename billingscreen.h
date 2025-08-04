#ifndef BILLINGSCREEN_H
#define BILLINGSCREEN_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "receiptscreen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddToBill_clicked();
    void on_btnGenerateBill_clicked();
    void on_btnClearBill_clicked();

private:
    Ui::MainWindow *ui;
    ReceiptScreen *receiptScreen;
    void updateTotals();
};

#endif // BILLINGSCREEN_H
