#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QDialog>
#include"confirmlogout.h"
#include "tokenuser.h"
#include"chatclient.h"
#include"newchatusername.h"

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
    void handlegetuserlistrSuccess(const QStringList &blocks);
    void on_pushButton_getuserlist_on_homepage_clicked();
 void buttonsProc(QAction *action);
   private:
    Ui::homepage *ui;
    confirmlogout *logout;
    ChatClient *chatClient;
    newchatusername *adduser;

signals:
    void sig_HmPage(tokenuser person);
};

#endif // HOMEPAGE_H
