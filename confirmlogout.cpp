#include "confirmlogout.h"
#include "ui_confirmlogout.h"
#include <QMessageBox>

confirmlogout::confirmlogout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmlogout)
{
    chatClient = new ChatClient(this);
    ui->setupUi(this);
}

confirmlogout::~confirmlogout()
{
    delete ui;
}

void confirmlogout::on_pushButton_logout_on_confirmlogout_clicked()
{
    QString username = ui->lineEdit_username_on_confirmlogout->text();
    QString password = ui->lineEdit_password_on_confirmlogout->text();

    chatClient->logout(username,password);

}


void confirmlogout::handlelogoutSuccess()
{
    // Handle logout success
    QMessageBox::information(this, "logout", "logout Successful");
    //note:open mainwindow
}

void confirmlogout::handlelogoutError(const QString &errorMessage)
{
    // Handle logout error
    QMessageBox::critical(this, "logout Error", errorMessage);
    //note:open homepage again
}



