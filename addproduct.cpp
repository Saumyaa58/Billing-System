#include "addproduct.h"
#include "ui_addproduct.h"
#include "productmanager.h"
#include <QMessageBox>

AddProduct::AddProduct(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddProduct)
{
    ui->setupUi(this);
}

AddProduct::~AddProduct()
{
    delete ui;
}

void AddProduct::on_btnSave_clicked()
{
    QString name = ui->lineProductName->text();
    QString category = ui->lineCategory->text();
    double price = ui->linePrice->text().toDouble();

    ProductManager manager;
    manager.saveProduct(name, category, price);

    QMessageBox::information(this, "Saved", "Product saved successfully!");

    ui->lineProductName->clear();
    ui->lineCategory->clear();
    ui->linePrice->clear();
}

void AddProduct::on_btnCancel_clicked()
{
    this->close();
}

void AddProduct::on_pushButton_clicked()
{

}

