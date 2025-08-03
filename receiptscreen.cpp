#include "receiptscreen.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

ReceiptScreen::ReceiptScreen(QWidget *parent) : QWidget(parent)
{
    // Set window properties
    setWindowTitle("Grocify - Receipt");
    setFixedSize(400, 600);

    // Create main layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Create header label
    headerLabel = new QLabel("GROCIFY<br>Smart Grocery Billing");
    headerLabel->setAlignment(Qt::AlignCenter);
    headerLabel->setStyleSheet("font-weight: bold; font-size: 18px;");
    headerLabel->setTextFormat(Qt::RichText);
    mainLayout->addWidget(headerLabel);

    // Create date label
    dateLabel = new QLabel(QDateTime::currentDateTime().toString("dd.MMM.yyyy hh:mm"));
    dateLabel->setAlignment(Qt::AlignCenter);
    dateLabel->setStyleSheet("font-size: 12px; color: #555;");
    mainLayout->addWidget(dateLabel);

    // Add top divider line
    topLine = new QFrame();
    topLine->setFrameShape(QFrame::HLine);
    topLine->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(topLine);

    // Create receipt table with 5 columns
    receiptTable = new QTableWidget(0, 5); // 5 columns: Product, Qty, Price, Total, Discount
    receiptTable->setHorizontalHeaderLabels({"Product", "Qty", "Price", "Total", "Discount"});
    receiptTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    receiptTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    receiptTable->setSelectionMode(QAbstractItemView::NoSelection);
    receiptTable->setStyleSheet("QTableWidget { border: none; }");
    mainLayout->addWidget(receiptTable);

    // Add bottom divider line
    bottomLine = new QFrame();
    bottomLine->setFrameShape(QFrame::HLine);
    bottomLine->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(bottomLine);

    // Create totals section labels
    subtotalLabel = new QLabel("Subtotal: $0.00");
    discountLabel = new QLabel("Discount: $0.00");
    totalLabel = new QLabel("Total: $0.00");
    totalLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #c00;");

    mainLayout->addWidget(subtotalLabel);
    mainLayout->addWidget(discountLabel);
    mainLayout->addWidget(totalLabel);

    // Add tax info label at the bottom
    taxInfoLabel = new QLabel("All items are inclusive of tax.");
    taxInfoLabel->setAlignment(Qt::AlignCenter);
    taxInfoLabel->setStyleSheet("font-size: 11px; font-style: italic; color: #555;");
    mainLayout->addWidget(taxInfoLabel);

    // Create buttons layout
    buttonLayout = new QHBoxLayout();

    printButton = new QPushButton("Print");
    closeButton = new QPushButton("Close");

    buttonLayout->addWidget(printButton);
    buttonLayout->addWidget(closeButton);
    mainLayout->addLayout(buttonLayout);

    // Connect button signals to slots
    connect(printButton, &QPushButton::clicked, this, &ReceiptScreen::printReceipt);
    connect(closeButton, &QPushButton::clicked, this, &ReceiptScreen::closeReceipt);

}

ReceiptScreen::~ReceiptScreen()
{
    // No special cleanup needed; Qt deletes child widgets automatically
}

void ReceiptScreen::setReceiptData(const QList<QStringList> &items,
                                   const QString &subtotal,
                                   const QString &discount,
                                   const QString &total)
{
    receiptTable->setRowCount(0); // Clear existing rows

    for (const QStringList &row : items) {
        int rowNum = receiptTable->rowCount();
        receiptTable->insertRow(rowNum);

        for (int col = 0; col < row.size() && col < receiptTable->columnCount(); ++col) {
            receiptTable->setItem(rowNum, col, new QTableWidgetItem(row[col]));
        }
    }

    subtotalLabel->setText("Subtotal:Rs. " + subtotal);
    discountLabel->setText("Discount:Rs. " + discount);
    totalLabel->setText("Total:Rs. " + total);
}

void ReceiptScreen::printReceipt()
{
    qDebug() << "Print button clicked - implement actual printing here.";
    // Add your printing logic here
}

void ReceiptScreen::closeReceipt()
{
    this->close();
}
