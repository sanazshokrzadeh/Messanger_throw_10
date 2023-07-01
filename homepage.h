#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QDialog>
#include "QtWidgets/qlistwidget.h"
#include"confirmlogout.h"
#include "tokenuser.h"
#include"chatclient.h"
#include"newchatusername.h"
#include<QObject>
#include<QMenu>
extern tokenuser receivedUser;
class creategroupname;
class joingroupname;
class createchannelname;
class joinchannelname;


namespace Ui {
class homepage;
}

class homepage : public QDialog
{
    Q_OBJECT

public:
    explicit homepage(QWidget *parent = nullptr);
    homepage(QString username);
    ~homepage();
    void setPerson( tokenuser person);

private slots:
    void on_moreButton_clicked();
    void on_pushButtonadd_2_clicked();
    void handlehidehomepageaftersuccessfullogout();
    void handlechatusernamesignal(QString chatusername);
    void handlegetuserlistrSuccess(const QStringList &blocks);
    void handlegetgrouplistSuccess(const QStringList &blocks);
    void handlegetuserchatsSuccess(const QStringList &blocks);
    void refreshContacts();
    void contactClicked(QListWidgetItem *item);
    void groupClicked(QListWidgetItem *item);
    void startRefreshTimer();
    void channelClicked(QListWidgetItem *item);
    void handlegetchannellistSuccess(const QStringList &blocks);
    void on_sendButton_clicked();
    void refreshChatroom();
    void readInformationFromFile();
    void on_pushButton_creategroup_on_homepage_clicked();
    void on_pushButton_joingroup_on_homepage_clicked();
    void on_pushButton_createchannel_on_homepage_clicked();
    void on_pushButton_joinchannel_on_homepage_clicked();
    void handlewhileoffline();
    void handlegroupwhileoffline();
   void handlechannelwhileoffline();
   void handlegetgroupchatsSuccess(const QStringList &blocks);
   void handlegetchannelchatsSuccess(const QStringList &blocks);
   void handlesendmessageerror(const QString &errormessage);

private:
    Ui::homepage *ui;
    confirmlogout *logout;
    ChatClient *chatClient;
    newchatusername *adduser;
    creategroupname *Creategroupname;
    joingroupname *Joingroupname;
    createchannelname *Createchannelname;
    joinchannelname *Joinchannelname;


signals:
    void sig_HmPage(tokenuser person);

};

#endif // HOMEPAGE_H
