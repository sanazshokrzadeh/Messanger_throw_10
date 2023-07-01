#ifndef JOINCHANNELNAME_H
#define JOINCHANNELNAME_H

#include <QDialog>
#include "chatclient.h"
#include "homepage.h"
#include <QMessageBox>

namespace Ui {
class joinchannelname;
}

class joinchannelname : public QDialog
{
    Q_OBJECT

public:
    explicit joinchannelname(QWidget *parent = nullptr);
    ~joinchannelname();

private slots:
    void handlejoinchannelsuccess(const QString &message);
    void handlejoinchannelerror(const QString &errormessage);
    void on_pushButton_joinchannel_on_joinchannelname2_clicked();
private:
    Ui::joinchannelname *ui;
    ChatClient *chatClient;
    homepage *homePage;
};

#endif // JOINCHANNELNAME_H
