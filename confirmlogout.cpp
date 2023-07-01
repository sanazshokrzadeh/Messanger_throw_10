#include "confirmlogout.h"
#include "ui_confirmlogout.h"
#include <QMessageBox>
#include<QFile>
#include<homepage.h>
confirmlogout::confirmlogout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmlogout)
{
    chatClient = new ChatClient(this);
    ui->setupUi(this);
    connect(chatClient, &ChatClient::logoutSuccess, this, &confirmlogout::handlelogoutSuccess);
    connect(chatClient, &ChatClient::logoutError, this, &confirmlogout::handlelogoutError);
     ui->passwordeye->setIcon(QIcon(":/img/img/icons8-closed-eye-24.png"));
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
    homepage *h;
    h->handlelogoutSuccesshm();
    // Handle logout success
    QMessageBox::information(this, "logout", "logout Successful");
    QFile file("usertoken2.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << file.errorString();
        return ;
    }
  file.close();

    this->hide();
    emit hidehomepageaftersuccessfullogout();




}

void confirmlogout::handlelogoutError(const QString &errorMessage)
{
    // Handle logout error
    QMessageBox::critical(this, "logout Error", errorMessage);
    this->hide();

}




void confirmlogout::on_passwordeye_clicked()
{
    if(ui->lineEdit_password_on_confirmlogout->echoMode()==QLineEdit::Password){
        //  ui->p_visible_OF->setIcon(QIcon("../res/icon/visibility-off"));
        ui->passwordeye->setIcon(QIcon(":/img/img/icons8-eye-50.png"));
        ui->lineEdit_password_on_confirmlogout->setEchoMode(QLineEdit::Normal);}

    else if(ui->lineEdit_password_on_confirmlogout->echoMode()==QLineEdit::Normal){
        ui->passwordeye->setIcon(QIcon(":/img/img/icons8-closed-eye-24.png"));
        ui->lineEdit_password_on_confirmlogout->setEchoMode(QLineEdit::Password);}
}

