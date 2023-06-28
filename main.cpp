#include "mainwindow.h"

#include <QApplication>
QString recievedToken;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/icon/Screen Shot 1402-04-06 at 12.34.11-fotor-bg-remover-20230627124344.png"));


    MainWindow w;
    w.show();
    return a.exec();
}
