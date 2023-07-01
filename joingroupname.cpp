#include "joingroupname.h"
#include "ui_joingroupname.h"

joingroupname::joingroupname(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::joingroupname)
{
    chatClient = new ChatClient(this);
    homePage = new homepage();
    ui->setupUi(this);
    connect(chatClient, &ChatClient::joingroupSuccess, this, &joingroupname::handlejoingroupsuccess);
    connect(chatClient, &ChatClient::joingroupError, this, &joingroupname::handlejoingrouperror);
}

joingroupname::~joingroupname()
{
    delete ui;
}

void joingroupname::on_pushButton_joingroup_on_joingroupname_clicked()
{
    QString token = receivedUser.getToken();
    QString group_name = ui->lineEdit_groupname_on_joingroupname->text();
    chatClient->joingroup(token,group_name);
}

void joingroupname::handlejoingroupsuccess(const QString &message)
{
    QMessageBox::information(this, "Join Group", message);
    this->hide();
    ui->lineEdit_groupname_on_joingroupname->clear();
}

void joingroupname::handlejoingrouperror(const QString &errormessage)
{
    QMessageBox::critical(this, "Join Group Error", errormessage);
}
