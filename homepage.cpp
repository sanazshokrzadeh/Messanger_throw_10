#include"homepage.h"
#include "ui_homepage.h"
#include<QMenu>
tokenuser receivedUser;
homepage::homepage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homepage)
{    ui->setupUi(this);
<<<<<<< HEAD
     chatClient = new ChatClient(this);
     adduser =new newchatusername();
     logout = new confirmlogout();
     connect(adduser, &newchatusername::sendchatusernametohomepage, this, &homepage::handlechatusernamesignal);
     connect(logout, &confirmlogout::hidehomepageaftersuccessfullogout, this, &homepage::handlehidehomepageaftersuccessfullogout);

=======
    //ui->label
>>>>>>> 6ddfd7ce80b56fb2b85420444f1fa5b9c4ca71dd

//    login=new loginDialog(this);
    //    connect(login, &loginDialog::sig_logintohomepage, this, &homepage::handletoken);
}

void homepage::setPerson(tokenuser person)
{
    // Use the person object here or store it as a member variable
    // You can access its attributes using person.username and person.token
    // Example:
    QString username = person.getUsername();
    QString token = person.getToken();
    receivedUser=tokenuser(username,token);
    ui->label->setText(username);
    ui->label_2->setText(token);
}

homepage::~homepage()
{
    delete ui;
}

void homepage::on_moreButton_clicked()
{

    logout->show();
}


void homepage::on_settingsButton_clicked()
{
//        delete menu;
//        if (menuParent == "sb")
//        {
//            return;
//        }
    QMenu *menu = new QMenu();
     //   menuParent = "sb";
    menu->addAction(QIcon("../res/icon/acc_settings_icon.png"), "Account Settings");
    menu->addAction(QIcon("../res/icon/app_settings_icon.png"), "App Settings");
    menu->addAction(QIcon("../res/icon/add_room_icon.png"), "Add Room");
    menu->addAction(QIcon("../res/icon/enter_room_icon.png"), "Enter Room");
    menu->addAction(QIcon("../res/icon/remove_account_icon.png"), "Delete Account");
    menu->addAction(QIcon("../res/icon/leave_icon.png"), "Logout");
      //  connect(menu, &QMenu::triggered, this, &ChatWindow::buttonsProc);
    menu->popup(QPoint(ui->settingsButton->pos().x(), ui->settingsButton->pos().y() + 70));
}





void homepage::on_pushButtonadd_2_clicked()
{
<<<<<<< HEAD
    adduser->show();
}

void homepage::handlehidehomepageaftersuccessfullogout(){
    this->hide();
}

void homepage::handlechatusernamesignal(QString chatusername){
    QString token = receivedUser.getToken();
    chatClient->sendmessegeuser(token,chatusername,"hi");
=======
>>>>>>> 6ddfd7ce80b56fb2b85420444f1fa5b9c4ca71dd

}

