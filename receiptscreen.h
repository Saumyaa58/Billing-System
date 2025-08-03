#ifndef RECEIPTSCREEN_H
#define RECEIPTSCREEN_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QDateTime>

class ReceiptScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiptScreen(QWidget *parent = nullptr);
    ~ReceiptScreen();

    void setReceiptData(const QList<QStringList> &items,
                        const QString &subtotal,
                        const QString &discount,
                        const QString &total);

private slots:
    void printReceipt();
    void closeReceipt();

private:
    // UI Elements
    QLabel *headerLabel;
    QLabel *dateLabel;
    QFrame *topLine;
    QTableWidget *receiptTable;
    QFrame *bottomLine;
    QLabel *subtotalLabel;
    QLabel *discountLabel;
    QLabel *totalLabel;
    QLabel *taxInfoLabel;

    QPushButton *printButton;
    QPushButton *closeButton;

    // Layouts
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
};

#endif // RECEIPTSCREEN_H
