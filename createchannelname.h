#ifndef CREATECHANNELNAME_H
#define CREATECHANNELNAME_H

#include <QDialog>
#include "chatclient.h"
#include "homepage.h"
#include <QMessageBox>

namespace Ui {
class createchannelname;
}

class createchannelname : public QDialog
{
    Q_OBJECT

public:
    explicit createchannelname(QWidget *parent = nullptr);
    ~createchannelname();

private slots:
    void on_pushButton_createchannel_on_createchannelname_clicked();

    void handlecreatechannelsuccess(const QString &message);

    void handlecreatechannelerror(const QString &errormessage);

private:
    Ui::createchannelname *ui;
    ChatClient *chatClient;
    homepage *homePage;

};

#endif // CREATECHANNELNAME_H

