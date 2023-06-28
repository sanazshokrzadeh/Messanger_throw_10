#include "logindialog.h"
#include "tokenuser.h"

#include "ui_logindialog.h"
#include"info.h"

#include <QApplication>
#include <QCryptographicHash>
#include <QDebug>
#include<QMessageBox>
#include<QSettings>
#include <QFile>
#include <QTextStream>
#include <QDebug>


loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    chatClient = new ChatClient(this);
    connect(chatClient, &ChatClient::AlreadyLogIn, this, &loginDialog::handleAlreadyLogIn);
    connect(chatClient, &ChatClient::logInSuccess, this, &loginDialog::handleLogInSuccess);
    connect(chatClient, &ChatClient::logInError, this, &loginDialog::handleLogInError);
    ui->passwordeye->setIcon(QIcon(":/img/img/icons8-closed-eye-24.png"));

}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButtonlogin2_clicked()
{
    info per;
    per.username=ui->lineEditusername2->text();
    per.password=ui->lineEdit_pass2->text();

    chatClient->logIn(per.username,per.password);
    emit sig_login(per);

}


//////////////////////////////////////////////////


// Function to write token and username to a file
bool writeToFile(QString fileName,QString token,QString username)
{
    QFile file(fileName);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return false;
    }

    QTextStream out(&file);
    if(token!=""){
        out << token << "," << username << "\n";}

    file.close();
    return true;
}

// Function to read token for a specific username from the file
QString readFromFile(QString fileName,QString username)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << file.errorString();
        return QString();
    }

    QTextStream in(&file);
    QString line,result;
    while (!in.atEnd()) {
        line = in.readLine();
        QStringList tokens = line.split(",");
        if (!tokens.at(1).isEmpty()&& tokens.at(0) == username) {
            file.close();
            result=tokens.at(1);
             // Return the token
        }
    }
    if(!result.isNull())
        return result;
    file.close();
    return QString(); // Token not found for the specified username
}

void loginDialog::handleAlreadyLogIn()
{
    // Handle log-in success
    QMessageBox::information(this, "Log In", "You are already logged in!");
    QString username=ui->lineEditusername2->text();

    QString tok=readFromFile("usertoken.txt",username);
         tokenuser person(username,tok);
               logintohomepage(person);



}
void loginDialog::logintohomepage(tokenuser person){
             homepage *HmPage = new homepage();
            //   HmPage(person.getUsername());
             //  homepage HHH(person.getUsername());
             //  emit HmPage->sig_HmPage(person);
            //emit sig_logintohomepage(person);
  // connect(HmPage,SIGNAL(sig_HmPage(person)),this,SLOT(slot_Homepage(person)));

     HmPage->setPerson(person);


             HmPage->show();
}
void loginDialog::slot_Homepage(tokenuser person){

}
void loginDialog::handleLogInSuccess(QString token)
{
    // Handle log-in success
    QMessageBox::information(this, "Log In", "Log In Successful");
             QString username=ui->lineEditusername2->text();
    writeToFile("usertoken.txt",username,token);
    tokenuser person(username,token);
           logintohomepage(person);

}

void loginDialog::handleLogInError(const QString &errorMessage)
{
    // Handle log-in error
    QMessageBox::critical(this, "Log In Error", errorMessage);
    // Perform any additional error handling or UI updates
}


void loginDialog::on_passwordeye_clicked()
{
    if(ui->lineEdit_pass2->echoMode()==QLineEdit::Password){
        //  ui->p_visible_OF->setIcon(QIcon("../res/icon/visibility-off"));
        ui->passwordeye->setIcon(QIcon(":/img/img/icons8-eye-50.png"));
        ui->lineEdit_pass2->setEchoMode(QLineEdit::Normal);}

    else if(ui->lineEdit_pass2->echoMode()==QLineEdit::Normal){
        ui->passwordeye->setIcon(QIcon(":/img/img/icons8-closed-eye-24.png"));
        ui->lineEdit_pass2->setEchoMode(QLineEdit::Password);}

}

