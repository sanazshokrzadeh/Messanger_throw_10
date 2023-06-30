#ifndef CREATEGROUPNAME_H
#define CREATEGROUPNAME_H

#include <QDialog>
#include "chatclient.h"
#include "homepage.h"

namespace Ui {
class creategroupname;
}

class creategroupname : public QDialog
{
    Q_OBJECT

public:
    explicit creategroupname(QWidget *parent = nullptr);
    ~creategroupname();

private slots:
    void on_pushButton_creategroup_on_creategroupname_clicked();

private:
    Ui::creategroupname *ui;
    ChatClient *chatClient;
    homepage *homePage;

};

#endif // CREATEGROUPNAME_H
