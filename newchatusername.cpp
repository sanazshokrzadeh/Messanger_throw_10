#include "newchatusername.h"
#include "ui_newchatusername.h"

newchatusername::newchatusername(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newchatusername)
{
    ui->setupUi(this);

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

