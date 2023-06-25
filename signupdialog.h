#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include<QVector>
#include"info.h"
namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr);
    ~SignUpDialog();
qint32 evaluatePasswordStrength(const QString& password);
private slots:
    void on_pushButtonsignup2_clicked();


private:
    Ui::SignUpDialog *ui;
signals:
    void sig_signup(info infor);
};

#endif // SIGNUPDIALOG_H



