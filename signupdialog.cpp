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
#include"info.h"



SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
    chatClient = new ChatClient(this);
    connect(chatClient, &ChatClient::signUpSuccess, this, &SignUpDialog::handleSignUpSuccess);
    connect(chatClient, &ChatClient::signUpError, this, &SignUpDialog::handleSignUpError);


}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}
//


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
    person.lastname=ui->lineEditlast->text();
    person.email=ui->lineEditemail->text();
    person.username=ui->lineEditusername->text();
    QString password=ui->lineEditpassword->text();

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

    // person.password =ui->lineEditpassword->text();
    ui->lineEditpassword->setText("your password strength is "+strength);

    // Display the result
    if (strength=="Weak"){
        ui->pushButtonsignup2->setEnabled(false);
        //goto pass;
        QMessageBox::information(nullptr, "Hey your password strength is", strength);//strength
        //on_bar_sliderMoved();
    }
    // pushButtonsignup2setStyleSheet();


    person.age=ui->lineEditage->text();
    person.gender=ui->comboBoxgender->currentText();
    // double age=ui->lineEditage->;
    //  QMessageBox::information(this,"gender",ui->comboBoxgender->currentText());
    if((person.name!='\0'&&person.username!='\0'&&person.password!='\0')){
        ui->pushButtonsignup2->setEnabled(true);
        // goto k;
    }
    emit sig_signup(person);

    chatClient->signUp(person.username,password,person.name,person.lastname);

    hide();

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



