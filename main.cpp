#include "mainwindow.h"

#include <QApplication>
#include<QFile>
#include<tokenuser.h>
#include<homepage.h>
bool readFromFile()
{
    QFile file("usertoken2.txt");


    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << file.errorString();
        return false;
    }

    QTextStream in(&file);
    QString line,user,token;
    line = in.readLine();
    QStringList tokens = line.split(",");
    //file.readAll();
    if(!line.isNull()){
        qDebug()<<line;
    token=tokens.at(1);
        user=tokens.at(0);
    tokenuser recievedToken(user,token);
        homepage *HmPage = new homepage();


        HmPage->setPerson(recievedToken);


        HmPage->show();
        return true;
    }
   file.close();
    return false;
    }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/icon/Screen Shot 1402-04-06 at 12.34.11-fotor-bg-remover-20230627124344.png"));

    MainWindow w;

    w.show();
    readFromFile();

    return a.exec();
}
