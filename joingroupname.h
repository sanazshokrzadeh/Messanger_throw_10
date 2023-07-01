#ifndef JOINGROUPNAME_H
#define JOINGROUPNAME_H

#include <QDialog>
#include "chatclient.h"
#include "homepage.h"
#include <QMessageBox>

namespace Ui {
class joingroupname;
}

class joingroupname : public QDialog
{
    Q_OBJECT

public:
    explicit joingroupname(QWidget *parent = nullptr);
    ~joingroupname();

private slots:
    void on_pushButton_joingroup_on_joingroupname_clicked();

    void handlejoingroupsuccess(const QString &message);
    void handlejoingrouperror(const QString &errormessage);
private:
    Ui::joingroupname *ui;
    ChatClient *chatClient;
    homepage *homePage;
};

#endif // JOINGROUPNAME_H
