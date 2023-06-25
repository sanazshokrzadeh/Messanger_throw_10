#include "logindialog.h"
#include "ui_logindialog.h"
#include"info.h"
#include <QApplication>
#include <QCryptographicHash>
#include <QDebug>
#include<QMessageBox>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    chatClient = new ChatClient(this);
    connect(chatClient, &ChatClient::logInSuccess, this, &loginDialog::handleLogInSuccess);
    connect(chatClient, &ChatClient::logInError, this, &loginDialog::handleLogInError);
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButtonlogin2_clicked()
{
    info per;
    per.username=ui->lineEditusername2->text();

    // per.password=ui->lineEdit_pass2->text();
    QString password=ui->lineEdit_pass2->text();
    QByteArray passData = password.toUtf8();
    QByteArray hashedData = QCryptographicHash::hash(passData, QCryptographicHash::Sha256);
    per.password = QString(hashedData.toHex());
    emit sig_login(per);

}


void loginDialog::handleLogInSuccess(const QString &token)
{
    // Handle log-in success
    QMessageBox::information(this, "Log In", "Log In Successful");
    // Perform any additional actions or UI updates
    // You can also store the token for future use, e.g., in a member variable
}

void loginDialog::handleLogInError(const QString &errorMessage)
{
    // Handle log-in error
    QMessageBox::critical(this, "Log In Error", errorMessage);
    // Perform any additional error handling or UI updates
}

