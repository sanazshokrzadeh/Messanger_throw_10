#include "logindialog.h"
#include "ui_logindialog.h"
#include"info.h"
#include <QApplication>
#include <QCryptographicHash>
#include <QDebug>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButtonlogin2_clicked()
{    info per;
    per.username=ui->lineEditusername2->text();

    // per.password=ui->lineEdit_pass2->text();
    QString password=ui->lineEdit_pass2->text();
    QByteArray passData = password.toUtf8();
    QByteArray hashedData = QCryptographicHash::hash(passData, QCryptographicHash::Sha256);
    per.password = QString(hashedData.toHex());
    emit sig_login(per);

}


