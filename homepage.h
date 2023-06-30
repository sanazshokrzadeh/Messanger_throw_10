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

    void on_settingsButton_clicked();

    //void handletoken( QString token);

    void on_pushButtonadd_2_clicked();

    void handlehidehomepageaftersuccessfullogout();

    void handlechatusernamesignal(QString chatusername);



    void on_pushButton_getuserchats_on_homepage_clicked();

    void on_pushButton_creategroup_clicked();



    void handlegetuserlistrSuccess(const QStringList &blocks);
    void handlegetgrouplistSuccess(const QStringList &blocks);
    void refreshContacts();
    void contactClicked(QListWidgetItem *item);
    void groupClicked(QListWidgetItem *item);
    void startRefreshTimer();
    void channelClicked(QListWidgetItem *item);
    void handlegetchannellistSuccess(const QStringList &blocks);
    void on_sendButton_clicked();




    void on_pushButton_creategroup_on_homepage_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::homepage *ui;
    confirmlogout *logout;
    ChatClient *chatClient;
    newchatusername *adduser;
    creategroupname *groupname;


signals:
    void sig_HmPage(tokenuser person);
    void sendtokentocreategroupname(const QString &token);
};

#endif // HOMEPAGE_H
