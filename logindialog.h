#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include<QVector>
#include"homepage.h"
#include"info.h"
#include"chatclient.h"
namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();



public slots:
    void logintohomepage(tokenuser person);

private slots:
    void on_pushButtonlogin2_clicked();
    void handleLogInSuccess(QString token);
    void handleLogInError(const QString &errorMessage);
      void handleAlreadyLogIn();
    void on_passwordeye_clicked();
      void slot_Homepage(tokenuser person);

private:
    Ui::loginDialog *ui;
    ChatClient *chatClient;

signals:
    void sig_login(info inf);
    void sig_logintohomepage(tokenuser person);
};

#endif // LOGINDIALOG_H






