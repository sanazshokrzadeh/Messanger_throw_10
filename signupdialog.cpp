#include "signupdialog.h"
#include "ui_signupdialog.h"
#include "chatclient.h"

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}



void SignUpDialog::on_pushButton_signup_on_signup_clicked()
{
    QString firstname = ui->lineEdit_firstname_on_signup->text();
    QString lastname = ui->lineEdit_lastname_on_signup->text();
    QString username = ui->lineEdit_username_on_signup->text();
    QString password = ui->lineEdit_password_on_signup->text();

    chatClient->signUp(username,password,firstname,lastname);


}

