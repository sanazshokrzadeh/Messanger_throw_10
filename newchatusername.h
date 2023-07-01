#ifndef NEWCHATUSERNAME_H
#define NEWCHATUSERNAME_H

#include <QDialog>
#include <QMessageBox>
#include "chatclient.h"
namespace Ui {
class newchatusername;
}

class newchatusername : public QDialog
{
    Q_OBJECT

public:
    explicit newchatusername(QWidget *parent = nullptr);
    ~newchatusername();

private slots:
    void on_pushButton_add_on_newchatusername_clicked();


private:
    Ui::newchatusername *ui;
    ChatClient *chatClient;

signals:
    void sendchatusernametohomepage(QString chatusername);
};

#endif // NEWCHATUSERNAME_H
