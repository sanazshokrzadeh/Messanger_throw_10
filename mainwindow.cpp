

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QMessageBox>
#include<overload.h>
QVector<info>vecinfo;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
bool search(info i){
    for(auto& i1:vecinfo){
        if(i==i1)
            return false;
    }
    return true;
}
qint32 searchuser(info i){qint32 num=0;
    for(auto& i1:vecinfo){
        if(i==i1)
            return num;
        num++;
    }
    return -1;
}
//void MainWindow::on_pushButton_Login_on_mainwindow_clicked()
//{
//    log = new loginDialog();
//    connect(log,SIGNAL(sig_login(info)),this,SLOT(slot_login(info)));
//    log->show();



//}

void MainWindow::slot_login(info per){
    qDebug()<<vecinfo[0].username;
    QMessageBox message;
    message.setWindowTitle("Answer");
    for(auto i:vecinfo){
        // qDebug()<<i.username;
        if(per.username==i.username){
            qDebug()<<i.password;
            if(per.password==i.password){
                message.setText("WLCOME!");
                message.setIcon(QMessageBox::Information);
                message.exec();
                return;
            }
            if(per.password!=i.password){
                message.setText("You are not allowed!\nPassword is wrong!");
                message.setIcon(QMessageBox::Information);
                message.exec();
                return;
            }
        }

    }
    message.setText("Not found!");
    message.setIcon(QMessageBox::Information);
    message.exec();
}

void save()
{


    QFile file("person.txt");
//
    file.open(QIODevice :: WriteOnly);

    QDataStream  out(&file);

    out.setVersion(QDataStream ::Qt_4_7);
    for(auto& i:vecinfo){
        out << i;
    }
    out<<"\nDOnefile!";
    file.flush();
    file.close();

}

//////////////////////////////////////////////////
void load()
{

    QFile file("person.txt");

    file.open(QIODevice :: ReadOnly);

    QDataStream  in(&file);

    in.setVersion(QDataStream ::Qt_4_7);



    info i;
    in>>i;
    while(i.name!="\nDOnefile!"){
        in>> i;
        if(search(i)){
            vecinfo.push_back(i);
        }
    }


    file.close();
    //qDebug() << p1.name<<":"<< p1.age;
    //qDebug() << p2.name<<":"<< p2.age;



}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_Login_on_mainwindow_clicked()
{ //read(p);
       load();
        log = new loginDialog();
        connect(log,SIGNAL(sig_login(info)),this,SLOT(slot_login(info)));
        log->show();



}


/*void on_pushButton_signup_on_mainwindow_clicked()
{
    SignUpDialog signUpDialog;
    signUpDialog.exec();
}*/

void MainWindow::slot_signup(info infor){
    qint32 num=searchuser(infor);
    if(num==-1){
        vecinfo.push_back(infor);
        save();
    }
    else{
        if(!(vecinfo[num]==infor)){
            QMessageBox::warning(nullptr, "Error", "This user has been added\n Please enter an other user!");}


        else if(vecinfo[num].username==infor.username){
            QMessageBox::warning(nullptr, "Error", "This username has been taken\n Try more");}

    }

}



void MainWindow::on_pushButton_signup_on_mainwindow_clicked()
{
    signUp=new SignUpDialog();
    connect(signUp,SIGNAL(sig_signup(info)),this,SLOT(slot_signup(info)));
    signUp->show();
}

