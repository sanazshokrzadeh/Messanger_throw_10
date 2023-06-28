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
    ui->passwordeye->setIcon(QIcon(":/img/img/icons8-closed-eye-24.png"));

}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButtonlogin2_clicked()
{
    info per;
    per.username=ui->lineEditusername2->text();
    per.password=ui->lineEdit_pass2->text();

    chatClient->logIn(per.username,per.password);
    emit sig_login(per);

}


void loginDialog::handleLogInSuccess(const QString &token)
{
    // Handle log-in success
    QMessageBox::information(this, "Log In", "Log In Successful");


}

void loginDialog::handleLogInError(const QString &errorMessage)
{
    // Handle log-in error
    QMessageBox::critical(this, "Log In Error", errorMessage);
    // Perform any additional error handling or UI updates
}


void loginDialog::on_passwordeye_clicked()
{
    if(ui->lineEdit_pass2->echoMode()==QLineEdit::Password){
        //  ui->p_visible_OF->setIcon(QIcon("../res/icon/visibility-off"));
        ui->passwordeye->setIcon(QIcon(":/img/img/icons8-eye-50.png"));
        ui->lineEdit_pass2->setEchoMode(QLineEdit::Normal);}

    else if(ui->lineEdit_pass2->echoMode()==QLineEdit::Normal){
        ui->passwordeye->setIcon(QIcon(":/img/img/icons8-closed-eye-24.png"));
        ui->lineEdit_pass2->setEchoMode(QLineEdit::Password);}

}

