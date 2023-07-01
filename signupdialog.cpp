#include "signupdialog.h"
#include "ui_signupdialog.h"
#include "chatclient.h"
#include <QCoreApplication>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>
#include<QMessageBox>
#include<QPushButton>
#include<QHBoxLayout>
#include<QSlider>
#include<QTimer>

#include"info.h"




SignUpDialog::SignUpDialog(QWidget *parent) : QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);


    //
    //email_regex.setPattern("^(\\w+(\\.|-)?\\w+)+@[a-zA-Z0-9]+\\.[a-zA-Z]+$");
    ui->setupUi(this);
    chatClient = new ChatClient(this);
    connect(chatClient, &ChatClient::signUpSuccess, this, &SignUpDialog::handleSignUpSuccess);
    connect(chatClient, &ChatClient::signUpError, this, &SignUpDialog::handleSignUpError);
    ui->pushButton->setIcon(QIcon(":/img/img/icons8-closed-eye-24.png"));
    ui->horizontalSlider->setStatusTip("Your password strength");
    ui->pbconfirm->setIcon(QIcon(":/img/img/icons8-closed-eye-24.png"));ui->horizontalSlider->setRange(0, 4);
    ui->horizontalSlider->setValue(0);// Range matches the possible score values
    //ui->lineEditemail->setPattern("^(\\w+(\\.|-)?\\w+)+@[a-zA-Z0-9]+\\.[a-zA-Z]+$");
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}



//void SignUpDialog::on_pushButton_signup_on_signup_clicked()
//{
//    QString firstname = ui->lineEdit_firstname_on_signup->text();
//    QString lastname = ui->lineEdit_lastname_on_signup->text();
//    QString username = ui->lineEdit_username_on_signup->text();
//    QString password = ui->lineEdit_password_on_signup->text();

//    chatClient->signUp(username,password,firstname,lastname);


//}
qint32 SignUpDialog::evaluatePasswordStrength(const QString& password)
{
    // Define regular expressions for password strength criteria
    QRegularExpression lowerCaseRegex("[a-z]");
    QRegularExpression upperCaseRegex("[A-Z]");
    QRegularExpression digitRegex("\\d");
    QRegularExpression specialCharRegex("[!@#$%^&*(),.?\":{}|<>]");

    // Check each criteria
    bool hasLowerCase = password.contains(lowerCaseRegex);
    bool hasUpperCase = password.contains(upperCaseRegex);
    bool hasDigit = password.contains(digitRegex);
    bool hasSpecialChar = password.contains(specialCharRegex);

    // Calculate the strength score
    int score = 0;
    if (hasLowerCase)
        score += 1;
    if (hasUpperCase)
        score += 1;
    if (hasDigit)
        score += 1;
    if (hasSpecialChar)
        score += 1;
return score;

}



void SignUpDialog::on_pushButtonsignup2_clicked()
{
    info person;
    person.name=ui->lineEditname->text();

    person.last=ui->lineEditphone->text();
    person.email=ui->lineEditemail->text();
    person.username=ui->lineEditusername->text();

    QString password=ui->lineEditpassword->text();
    //person.password =ui->lineEditpassword->text();
    qint32 score = evaluatePasswordStrength(password);
    // Determine the password strength based on the score
    QString strength;
    if (score < 2)
        strength = "Weak";
    else if (score < 4)
        strength = "Medium";
    else
        strength = "Strong";
  //  QSlider slider(Qt::Horizontal);
    ui->horizontalSlider->setRange(0, 4); // Range matches the possible score values
    ui->horizontalSlider->setTickPosition(QSlider::TicksBelow);
    ui->horizontalSlider->setTickInterval(1);
    ui->horizontalSlider->setSingleStep(1);
    ui->horizontalSlider->setPageStep(1);
    ui->horizontalSlider->show();
    ui->horizontalSlider->setValue(score);
    ui->lineEditpassword->setStatusTip("Your password strength is "+strength);
    person.password =ui->lineEditpassword->text();

    QString pass=ui->c_password_lineEdit->text();
    if(pass!=person.password){
        ui->c_password_lineEdit->setStatusTip("Please Enter your password correctlly");
    }
    //setText("your password strength is "+strength);

    if (strength=="Weak"){
        //  ui->pushButtonsignup2->setEnabled(false);
        //goto pass;
        QMessageBox(QMessageBox::Information, "Your Password Strength is", strength);

        // QTimer::singleShot(3000, &messageBox, &QMessageBox::close);
        //strength
        //on_bar_sliderMoved();
    }
    // pushButtonsignup2setStyleSheet();




    if(person.name.isEmpty()||person.username.isEmpty()||person.password.isEmpty()||person.last.isEmpty()){
        QMessageBox::warning(this,"Warning", "Please fill out the information");

    }
    else{      ui->pushButtonsignup2->setEnabled(true);
        hide();
        chatClient->signUp(person.username,password,person.name,person.last);
        emit sig_signup(person);
    }

}


void SignUpDialog::handleSignUpSuccess()
{
    // Handle sign-up success
    QMessageBox::information(this, "Sign Up", "Sign Up Successful");
    // Perform any additional actions or UI updates
}

void SignUpDialog::handleSignUpError(const QString &errorMessage)
{
    // Handle sign-up error
    QMessageBox::critical(this, "Sign Up Error", errorMessage);
    // Perform any additional error handling or UI updates
}





void SignUpDialog::on_pushButton_clicked()
{
    if(ui->lineEditpassword->echoMode()==QLineEdit::Password){
        //  ui->p_visible_OF->setIcon(QIcon("../res/icon/visibility-off"));
        ui->pushButton->setIcon(QIcon(":/img/img/icons8-eye-50.png"));
        ui->lineEditpassword->setEchoMode(QLineEdit::Normal);}

    else if(ui->lineEditpassword->echoMode()==QLineEdit::Normal){
        ui->pushButton->setIcon(QIcon(":/img/img/icons8-closed-eye-24.png"));
        ui->lineEditpassword->setEchoMode(QLineEdit::Password);}
}


void SignUpDialog::on_pbconfirm_clicked()
{
    /*   if (is_Cpassword_visible) {
         ui->c_password_lineEdit->setEchoMode(QLineEdit::Password);
         ui->pbconfirm->setIcon(QIcon(":/confirm/confirm/closed-eye-24.png"));
         ui->c_password_lineEdit->setEchoMode(QLineEdit::Normal);
    }
    else {
         ui->c_password_lineEdit->setEchoMode(QLineEdit::Normal);
         ui->pbconfirm->setIcon(QIcon(":/confirm/confirm/eye-50.png"));
     ui->lineEditpassword->setEchoMode(QLineEdit::Normal);
    }*/
    if(ui->c_password_lineEdit->echoMode()==QLineEdit::Password){
        //  ui->p_visible_OF->setIcon(QIcon("../res/icon/visibility-off"));
        ui->pbconfirm->setIcon(QIcon(":/confirm/confirm/eye-50.png"));
        ui->c_password_lineEdit->setEchoMode(QLineEdit::Normal);}

    else if(ui->c_password_lineEdit->echoMode()==QLineEdit::Normal){
        ui->pbconfirm->setIcon(QIcon(":/confirm/confirm/closed-eye-24.png"));
        ui->c_password_lineEdit->setEchoMode(QLineEdit::Password);}
}

