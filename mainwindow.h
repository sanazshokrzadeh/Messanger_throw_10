#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"chatclient.h"
#include"signupdialog.h"
#include"logindialog.h"
#include"info.h"
#include<QVector>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_signup_on_mainwindow_clicked();
     void slot_signup(info infor);
    void slot_login(info per);
   //  void on_pushButton_login_on_mainwindow_clicked();

     void on_pushButton_Login_on_mainwindow_clicked();

 private:
    Ui::MainWindow *ui;
    QVector<MainWindow>vec;
    loginDialog *log;
    SignUpDialog *signUp;
};
#endif // MAINWINDOW_H





