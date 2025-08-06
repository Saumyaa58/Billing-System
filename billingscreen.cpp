#include "billingscreen.h"
#include "ui_billingscreen.h"
#include <QMessageBox>
#include <QDateTime>
#include <QDoubleValidator>

    BillingScreen::BillingScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BillingScreen)
    , receiptScreen(nullptr)
{
    ui->setupUi(this);

    // Set current date/time
    if (ui->labelDateTime) {
        ui->labelDateTime->setText(QDateTime::currentDateTime().toString("dd.MMM.yyyy hh:mm"));
    }

    // Validators
    QDoubleValidator *priceValidator = new QDoubleValidator(0, 9999, 2, this);
    priceValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEditPrice->setValidator(priceValidator);

    QDoubleValidator *discountValidator = new QDoubleValidator(0, 100, 2, this);
    discountValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEditDiscount->setValidator(discountValidator);

    // Initialize totals
    if (ui->labelSubtotalValue) ui->labelSubtotalValue->setText("0.00");
    if (ui->labelDiscountValue) ui->labelDiscountValue->setText("0.00");
    if (ui->labelTotalValue) ui->labelTotalValue->setText("0.00");

    // Setup table headers
    ui->tableBill->setColumnCount(5);
    QStringList headers = {"Product", "Qty", "Price", "Total", "Discount"};
    ui->tableBill->setHorizontalHeaderLabels(headers);

    ui->lineEditProduct->setFocus();
}

BillingScreen::~BillingScreen()
{
    delete ui;
}

void BillingScreen::on_btnAddToBill_clicked()
{
    QLineEdit* productInput = findChild<QLineEdit*>("lineEditProduct");
    QSpinBox* quantityInput = findChild<QSpinBox*>("spinBoxQuantity");
    QLineEdit* priceInput = findChild<QLineEdit*>("lineEditPrice");
    QLineEdit* discountInput = findChild<QLineEdit*>("lineEditDiscount");
    QTableWidget* billTable = findChild<QTableWidget*>("tableBill");

    if (!productInput || !quantityInput || !priceInput || !discountInput || !billTable) {
        QMessageBox::critical(this, "UI Error", "Required UI elements not found!");
        return;
    }

    QString product = productInput->text().trimmed();
    int quantity = quantityInput->value();
    double price = priceInput->text().toDouble();
    double discountRate = discountInput->text().toDouble();

    if (product.isEmpty()) {
        QMessageBox::warning(this, "Missing Product", "Please enter a product name");
        return;
    }

    if (price <= 0) {
        QMessageBox::warning(this, "Invalid Price", "Please enter a valid price");
        return;
    }

    double total = quantity * price;
    double discountAmount = total * discountRate / 100.0;

    int row = billTable->rowCount();
    billTable->insertRow(row);

    QTableWidgetItem *productItem = new QTableWidgetItem(product);
    QTableWidgetItem *qtyItem = new QTableWidgetItem(QString::number(quantity));
    QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(price, 'f', 2));
    QTableWidgetItem *totalItem = new QTableWidgetItem(QString::number(total, 'f', 2));
    QTableWidgetItem *discountItem = new QTableWidgetItem(QString::number(discountAmount, 'f', 2));

    // Align right for numbers
    qtyItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    priceItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    totalItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    discountItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

    billTable->setItem(row, 0, productItem);
    billTable->setItem(row, 1, qtyItem);
    billTable->setItem(row, 2, priceItem);
    billTable->setItem(row, 3, totalItem);
    billTable->setItem(row, 4, discountItem);

    // Clear inputs
    productInput->clear();
    quantityInput->setValue(1);
    priceInput->clear();
    discountInput->clear();
    productInput->setFocus();

    updateTotals();
}

void BillingScreen::updateTotals()
{
    QTableWidget* billTable = findChild<QTableWidget*>("tableBill");
    QLabel* subtotalLabel = findChild<QLabel*>("labelSubtotalValue");
    QLabel* discountLabel = findChild<QLabel*>("labelDiscountValue");
    QLabel* totalLabel = findChild<QLabel*>("labelTotalValue");

    if (!billTable || !subtotalLabel || !discountLabel || !totalLabel) {
        return;
    }

    double subtotal = 0.0;
    double totalDiscount = 0.0;

    for (int row = 0; row < billTable->rowCount(); ++row) {
        QTableWidgetItem *totalItem = billTable->item(row, 3);
        QTableWidgetItem *discountItem = billTable->item(row, 4);

        if (totalItem) {
            subtotal += totalItem->text().toDouble();
        }

        if (discountItem) {
            totalDiscount += discountItem->text().toDouble();
        }
    }

    double grandTotal = subtotal - totalDiscount;

    subtotalLabel->setText(QString::number(subtotal, 'f', 2));
    discountLabel->setText(QString::number(totalDiscount, 'f', 2));
    totalLabel->setText(QString::number(grandTotal, 'f', 2));
}

void BillingScreen::on_btnGenerateBill_clicked()
{
    if (ui->tableBill->rowCount() == 0) {
        QMessageBox::warning(this, "Empty Bill", "No items in the bill");
        return;
    }

    QList<QStringList> receiptItems;
    for (int row = 0; row < ui->tableBill->rowCount(); ++row) {
        QStringList item;
        item << ui->tableBill->item(row, 0)->text(); // Product
        item << ui->tableBill->item(row, 1)->text(); // Qty
        item << ui->tableBill->item(row, 2)->text(); // Price
        item << ui->tableBill->item(row, 3)->text(); // Total
        item << ui->tableBill->item(row, 4)->text(); // Discount
        receiptItems.append(item);
    }

    receiptScreen = new ReceiptScreen();
    receiptScreen->setAttribute(Qt::WA_DeleteOnClose);

    receiptScreen->setReceiptData(
        receiptItems,
        ui->labelSubtotalValue->text(),
        ui->labelDiscountValue->text(),
        ui->labelTotalValue->text()
        );

    receiptScreen->show();
}

void BillingScreen::on_btnClearBill_clicked()
{
    QTableWidget* billTable = findChild<QTableWidget*>("tableBill");
    QLabel* subtotalLabel = findChild<QLabel*>("labelSubtotalValue");
    QLabel* discountLabel = findChild<QLabel*>("labelDiscountValue");
    QLabel* totalLabel = findChild<QLabel*>("labelTotalValue");

    if (billTable) billTable->setRowCount(0);
    if (subtotalLabel) subtotalLabel->setText("0.00");
    if (discountLabel) discountLabel->setText("0.00");
    if (totalLabel) totalLabel->setText("0.00");

    if (auto productInput = findChild<QLineEdit*>("lineEditProduct")) {
        productInput->setFocus();
    }
}
