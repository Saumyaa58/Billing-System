#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "loginwindow.h"
#include "billingscreen.h"
#include <QMessageBox>
#include <QDir>

extern "C" {
#include "product.h"
#include "login.h"
}

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    ui->stackedWidget2->setCurrentIndex(0);
    connect(ui->loggoutbutton, &QPushButton::clicked, this, &MenuWindow::handleLogout);

    // rest of your connects...

    connect(ui->addbutton1, &QPushButton::clicked, [=]() {
        ui->stackedWidget2->setCurrentWidget(ui->addpage);
    });

    connect(ui->updatedeletebutton, &QPushButton::clicked, [=]() {
        ui->stackedWidget2->setCurrentWidget(ui->updatepage);
    });

    connect(ui->updatebutton, &QPushButton::clicked, this, &MenuWindow::on_updatebutton_clicked);
    connect(ui->deletebutton, &QPushButton::clicked, this, &MenuWindow::on_deletebutton_clicked);

    connect(ui->viewbutton, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget2->setCurrentIndex(3);  // Input page for viewing
    });

    connect(ui->addbutton, &QPushButton::clicked, this, &MenuWindow::on_addbutton_clicked);
    connect(ui->viewbutton_2, &QPushButton::clicked, this, &MenuWindow::on_viewbutton_2_clicked);

    // Back buttons
    connect(ui->back, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget2->setCurrentIndex(0);
    });
    connect(ui->back1, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget2->setCurrentIndex(0);
    });
    connect(ui->back2, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget2->setCurrentIndex(0);
    });
    connect(ui->back3, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget2->setCurrentIndex(0);
    });
    connect(ui->createbutton, &QPushButton::clicked, this, &MenuWindow::on_createbutton_clicked);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_addbutton_clicked()
{
    ui->stackedWidget2->setCurrentWidget(ui->addpage);
    QMessageBox::information(this, "Debug", "Add button clicked!");

    QString idText = ui->idinput2->text().trimmed();
    bool ok;
    int id = idText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Product ID.");
        return;
    }

    QString name = ui->nameinput2->text();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a Product Name.");
        return;
    }

    float price = ui->priceinput2->text().toFloat(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Price.");
        return;
    }

    int stock = ui->qntyinput2->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Stock.");
        return;
    }

    // ✅ Now pass all values including stock
    bool result = addProduct(id, name.toStdString().c_str(), price, stock);

    if (result)
        QMessageBox::information(this, "Success", "Product added successfully!");
    else
        QMessageBox::warning(this, "Failure", "Failed to add product.");
}


void MenuWindow::on_updatebutton_clicked()
{
    ui->stackedWidget2->setCurrentWidget(ui->updatepage);

    bool ok;

    int id = ui->idinput->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Product ID.");
        return;
    }

    QString name = ui->nameinput->text();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a Product Name.");
        return;
    }

    float price = ui->priceinput->text().toFloat(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Price.");
        return;
    }

    int stock = ui->qntyinput->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Stock.");
        return;
    }

    bool result = updateProduct(id, name.toStdString().c_str(), price, stock);

    if (result)
        QMessageBox::information(this, "Success", "Product updated successfully!");
    else
        QMessageBox::warning(this, "Failure", "Product ID not found. Update failed.");
}


void MenuWindow::on_deletebutton_clicked()
{
    bool ok;
    int id = ui->idinput->text().toInt(&ok); // ONLY Product ID required
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Product ID (number).");
        return;
    }

    bool result = deleteProduct(id);

    if (result)
        QMessageBox::information(this, "Success", "Product deleted successfully!");
    else
        QMessageBox::warning(this, "Failure", "Product ID not found. Delete failed.");
}

void MenuWindow::on_viewbutton_2_clicked()
{
    bool ok;
    int id = ui->idinput3->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Product ID.");
        return;
    }

    QString name = ui->nameinput3->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a Product Name.");
        return;
    }

    struct Product p;
    if (viewproduct(id, name.toStdString().c_str(), &p)) {
        ui->idoutput->setText(QString::number(p.id));
        ui->nameoutput->setText(QString::fromStdString(p.name));
        ui->priceoutput->setText(QString::number(p.price));
        ui->stockoutput->setText(QString::number(p.stock));

        ui->stackedWidget2->setCurrentIndex(4);  // View result page
    } else {
        QMessageBox::warning(this, "Not Found", "Product not found. Check ID and Name.");
    }
}
void MenuWindow::handleLogout()
{
    this->close();  // Close menu window

    loginwindow *loginWin = new loginwindow();  // Open login window again
    loginWin->show();
}
void MenuWindow::on_createbutton_clicked()
{
    qDebug();
    BillingScreen *billingWindow = new BillingScreen(this);
    billingWindow->show();
    billingWindow->raise();
    billingWindow->activateWindow();

}
