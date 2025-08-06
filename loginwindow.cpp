extern "C" {
#include "login.h"
#include "product.h"
}
#include "menuwindow.h"
#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include "./ui_menuwindow.h"
#include <QMessageBox>
#include <QDebug>

loginwindow::loginwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginwindow)
{
    ui->setupUi(this);

    // Install event filter on front page widget to detect clicks
    ui->GROCIFY->installEventFilter(this);

    // Show front page first
    ui->stackedWidget->setCurrentIndex(0);

    // Connect login button
    connect(ui->loginbutton, &QPushButton::clicked, this, &loginwindow::handleLogin);

    // Connect signup button to switch to signup page
    connect(ui->signinbutton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(2);  // Signup page index
    });

    // Connect signup submit button
    connect(ui->submitbutton, &QPushButton::clicked, this, &loginwindow::handleSignup);
}

loginwindow::~loginwindow()
{
    delete ui;
}

bool loginwindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->GROCIFY && event->type() == QEvent::MouseButtonPress) {
        qDebug() << "Front page clicked - switching to login page";
        ui->stackedWidget->setCurrentIndex(1); // Switch to login page
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}

void loginwindow::handleLogin()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    QByteArray u = username.toLocal8Bit();
    QByteArray p = password.toLocal8Bit();

    int result = authenticate(u.data(), p.data());

    if (result == 1) {
        QMessageBox::information(this, "Login Successful", "Welcome, " + username + "!");

        // Create MenuWindow instance
        MenuWindow *menuWindow = new MenuWindow();

        // Show MenuWindow
        menuWindow->show();

        // Close the login window
        this->close();

        // Optional: if you want loginwindow object to be deleted safely later, set Qt::WA_DeleteOnClose flag
        this->setAttribute(Qt::WA_DeleteOnClose);
    } else {
        QMessageBox::warning(this, "Login Failed", "Incorrect username or password.");
    }
}


void loginwindow::handleSignup()
{
    QString username = ui->signupUsernameLineEdit->text();
    QString password = ui->signupPassword->text();
    QString confirmPassword = ui->confirmPassword->text();

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Password Mismatch", "Passwords do not match.");
        return;
    }

    QByteArray u = username.toLocal8Bit();
    QByteArray p = password.toLocal8Bit();

    int result = register_user(u.data(), p.data());

    if (result == 1) {
        QMessageBox::information(this, "Signup Successful", "User registered successfully.");
        ui->stackedWidget->setCurrentIndex(1); // Go back to login page
    } else {
        QMessageBox::warning(this, "Signup Failed", "Username already exists or error occurred.");
    }
}

