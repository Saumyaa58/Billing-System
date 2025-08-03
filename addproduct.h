#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QWidget>

namespace Ui {
class AddProduct;
}

class AddProduct : public QWidget
{
    Q_OBJECT

public:
    explicit AddProduct(QWidget *parent = nullptr);
    ~AddProduct();

private slots:
    void on_btnSave_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddProduct *ui;
};

#endif // ADDPRODUCT_H
