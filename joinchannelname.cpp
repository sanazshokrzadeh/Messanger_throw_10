#include "joinchannelname.h"
#include "ui_joinchannelname.h"

joinchannelname::joinchannelname(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::joinchannelname)
{
    chatClient = new ChatClient(this);
    homePage = new homepage();
    ui->setupUi(this);
    connect(chatClient, &ChatClient::joinchannelSuccess, this, &joinchannelname::handlejoinchannelsuccess);
    connect(chatClient, &ChatClient::joinchannelError, this, &joinchannelname::handlejoinchannelerror);
}

joinchannelname::~joinchannelname()
{
    delete ui;
}



void joinchannelname::handlejoinchannelsuccess(const QString &message)
{
    QMessageBox::information(this, "Join Channel", message);
    this->hide();
    ui->lineEdit_channelname_on_joinchannelname->clear();
}

void joinchannelname::handlejoinchannelerror(const QString &errormessage)
{
    QMessageBox::critical(this, "Join Channel Error", errormessage);
}

void joinchannelname::on_pushButton_joinchannel_on_joinchannelname2_clicked()
{
    QString token = receivedUser.getToken();
    QString channel_name = ui->lineEdit_channelname_on_joinchannelname->text();
    chatClient->joinchannel(token, channel_name);
}

