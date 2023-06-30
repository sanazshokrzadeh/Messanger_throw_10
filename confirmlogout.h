#ifndef CONFIRMLOGOUT_H
#define CONFIRMLOGOUT_H

#include <QDialog>
#include "chatclient.h"

namespace Ui {
class confirmlogout;
}

class confirmlogout : public QDialog
{
    Q_OBJECT

public:
    explicit confirmlogout(QWidget *parent = nullptr);
    ~confirmlogout();

private slots:
    void on_pushButton_logout_on_confirmlogout_clicked();
    void handlelogoutSuccess();
    void handlelogoutError(const QString &errorMessage);
    void on_passwordeye_clicked();

signals:
    void hidehomepageaftersuccessfullogout();


private:
    Ui::confirmlogout *ui;
    ChatClient *chatClient;
};

#endif // CONFIRMLOGOUT_H
