

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<chatclient.h>
#include<QMessageBox>
#include<overload.h>

#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
//QVector<info>vecinfo;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Hide the sign-up and login buttons initially
    ui->pushButton_signup_on_mainwindow->hide();
    ui->pushButton_Login_on_mainwindow->hide();

    // Set up the QTimer for the logo display duration
    timer = new QTimer(this);
    timer->setSingleShot(true); // Trigger the timeout only once
    timer->setInterval(1500); // Adjust the duration as needed

    // Create a QPropertyAnimation to animate the opacity property of the logo label
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(ui->label);
    ui->label->setGraphicsEffect(opacityEffect);

    QPropertyAnimation* animation = new QPropertyAnimation(opacityEffect, "opacity", this);
    animation->setDuration(100); // Adjust the duration as needed
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);

    // Connect the timer's timeout() signal to start the animation
    connect(timer, &QTimer::timeout, this, [animation]() {
        animation->start();
    });

    // Connect the animation's finished() signal to show the sign-up and login buttons
    connect(animation, &QPropertyAnimation::finished, [this]() {
        ui->pushButton_signup_on_mainwindow->show();
        ui->pushButton_Login_on_mainwindow->show();
    });

    // Connect the timer's timeout() signal to hide the logo label
    connect(timer, &QTimer::timeout, ui->label, &QLabel::hide);

    ui->label->setAttribute(Qt::WA_TranslucentBackground);

    // Start the timer
    timer->start();
}


void MainWindow::slot_login(info per){

}

void save()
{
    QFile file("person1.txt");
    file.open(QIODevice :: WriteOnly);
    QDataStream  out(&file);
    out.setVersion(QDataStream ::Qt_4_7);
    file.flush();
    file.close();
}

//////////////////////////////////////////////////
void load()
{

    QFile file("person1.txt");

    file.open(QIODevice :: ReadOnly);

    QDataStream  in(&file);

    in.setVersion(QDataStream ::Qt_4_7);

    info i;

    while(!in.atEnd()){
        in>> i;
    }


    file.close();

}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_Login_on_mainwindow_clicked()
{ //read(p);
    // load();
    log = new loginDialog();
    connect(log,SIGNAL(sig_login(info)),this,SLOT(slot_login(info)));
    log->show();
}


void MainWindow::slot_signup(info infor){

}



void MainWindow::on_pushButton_signup_on_mainwindow_clicked()
{
    signUp=new SignUpDialog();
    connect(signUp,SIGNAL(sig_signup(info)),this,SLOT(slot_signup(info)));
    signUp->show();
}

