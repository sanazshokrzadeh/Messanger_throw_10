#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QDialog>
#include"confirmlogout.h"

namespace Ui {
class homepage;
}

class homepage : public QDialog
{
    Q_OBJECT

public:
    explicit homepage(QWidget *parent = nullptr);
    ~homepage();

private slots:
    void on_moreButton_clicked();

    void on_settingsButton_clicked();

private:
    Ui::homepage *ui;
    confirmlogout *logout;
};

#endif // HOMEPAGE_H
