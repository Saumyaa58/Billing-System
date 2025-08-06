#ifndef BILLINGSCREEN_H
#define BILLINGSCREEN_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "receiptscreen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BillingScreen; }
QT_END_NAMESPACE

class BillingScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit BillingScreen(QWidget *parent = nullptr);
    ~BillingScreen();

private slots:
    void on_btnAddToBill_clicked();
    void on_btnGenerateBill_clicked();
    void on_btnClearBill_clicked();

private:
    Ui::BillingScreen *ui;
    ReceiptScreen *receiptScreen;
    void updateTotals();
};

#endif // BILLINGSCREEN_H
