#include "createchannelname.h"
#include "ui_createchannelname.h"

createchannelname::createchannelname(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createchannelname)
{
    chatClient = new ChatClient(this);
    homePage = new homepage();
    connect(chatClient, &ChatClient::createchannelSuccess, this, &createchannelname::handlecreatechannelsuccess);
    connect(chatClient, &ChatClient::createchannelError, this, &createchannelname::handlecreatechannelerror);

    ui->setupUi(this);
}

createchannelname::~createchannelname()
{
    delete ui;
}

void createchannelname::on_pushButton_createchannel_on_createchannelname_clicked()
{
    QString token = receivedUser.getToken();
    QString channel_name = ui->lineEdit_channelname_on_createchannelname->text();
    chatClient->createchannel(token, channel_name);
}

void createchannelname::handlecreatechannelsuccess(const QString &message)
{
    QMessageBox::information(this, "Create Channel", message);
    this->hide();
    ui->lineEdit_channelname_on_createchannelname->clear();
}

void createchannelname::handlecreatechannelerror(const QString &errormessage)
{
    QMessageBox::critical(this, "Create Channel Error", errormessage);
}
