#include "newchatusername.h"
#include "ui_newchatusername.h"

newchatusername::newchatusername(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newchatusername)
{
    ui->setupUi(this);
//    connect(chatClient,&ChatClient::sendmessageuserSuccess,this,&newchatusername::handleaddnewusersuccess);
//    connect(chatClient,&ChatClient::sendmessageuserError,this,&newchatusername::handleaddnewusererror);
}

newchatusername::~newchatusername()
{
    delete ui;
}

void newchatusername::on_pushButton_add_on_newchatusername_clicked()
{
    QString chatusername = ui->lineEdit_username_on_newchatusername->text();
    emit sendchatusernametohomepage(chatusername);
    this->hide();
}

//void newchatusername::handleaddnewusersuccess(){
//    QMessageBox::information(this,"Hello sent","Added Successfully");
//    this->hide();
//    ui->lineEdit_username_on_newchatusername->clear();
//}

//void newchatusername::handleaddnewusererror(const QString &errormessage){
//    QMessageBox::critical(this,":(",errormessage);
//    this->hide();

//}
