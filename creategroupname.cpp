#include "creategroupname.h"
#include "ui_creategroupname.h"


creategroupname::creategroupname(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creategroupname)
{
    chatClient = new ChatClient(this);
    homePage = new homepage();
    //connect(homePage,&homepage::sendtokentocreategroupname,this,&creategroupname::handlesenttoken);

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
    this->hide();
}

