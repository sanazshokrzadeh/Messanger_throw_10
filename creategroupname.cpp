#include "creategroupname.h"
#include "ui_creategroupname.h"


creategroupname::creategroupname(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creategroupname)
{
    chatClient = new ChatClient(this);
    homePage = new homepage();
    connect(chatClient,&ChatClient::creategroupSuccess,this,&creategroupname::handlecreategroupsuccess);
    connect(chatClient,&ChatClient::creategroupError,this,&creategroupname::handlecreategrouperror);


    ui->setupUi(this);
}

creategroupname::~creategroupname()
{
    delete ui;
}

void creategroupname::on_pushButton_creategroup_on_creategroupname_clicked()
{
    QString token = receivedUser.getToken();
    QString group_name = ui->lineEdit_groupname_on_creategroupname->text();
    chatClient->creategroup(token,group_name);

}

void creategroupname::handlecreategroupsuccess(const QString &message)
{
    QMessageBox::information(this,"Create Group",message);
    this->hide();
    ui->lineEdit_groupname_on_creategroupname->clear();

}

void creategroupname::handlecreategrouperror(const QString &errormessage)
{
    QMessageBox::critical(this,"Create Group Error", errormessage);

}

