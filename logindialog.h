#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include<QVector>
#include"info.h"
namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();

private slots:
    void on_pushButtonlogin2_clicked();

private:
    Ui::loginDialog *ui;
signals:
    void sig_login(info inf);
};

#endif // LOGINDIALOG_H

