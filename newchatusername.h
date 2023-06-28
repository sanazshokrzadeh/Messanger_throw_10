#ifndef NEWCHATUSERNAME_H
#define NEWCHATUSERNAME_H

#include <QDialog>

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

signals:
    void sendchatusernametohomepage(QString chatusername);
};

#endif // NEWCHATUSERNAME_H
