#include"homepage.h"
#include "ui_homepage.h"
#include<QMenu>
tokenuser receivedUser;
homepage::homepage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homepage)
{    ui->setupUi(this);
     setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);


     chatClient = new ChatClient(this);
     adduser =new newchatusername();
     logout = new confirmlogout();
     connect(adduser, &newchatusername::sendchatusernametohomepage, this, &homepage::handlechatusernamesignal);
     connect(logout, &confirmlogout::hidehomepageaftersuccessfullogout, this, &homepage::handlehidehomepageaftersuccessfullogout);
     connect(chatClient, &ChatClient::getuserlistSuccess, this, &homepage::handlegetuserlistrSuccess);


    //ui->label


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


void homepage::handlegetuserlistrSuccess(const QStringList &blocks)
 {   QMenu *menu = new QMenu();
   for (int i = 0; i < blocks.size(); ++i) {
        QString str = QString(blocks.at(i)).leftJustified(51, ' ');
 menu->addAction(str);

        menu->popup(QPoint(ui->room_paneluser->pos().x()+256, ui->room_paneluser->pos().y()+123+i));

    }
    connect(menu, &QMenu::triggered, this, &homepage::buttonsProc);
}


void homepage::buttonsProc(QAction *action){
    ui->profile_lable->setText(action->text());
    if(action->text()=="sanaz"){
        ui->chat_panel->addAction("hooooooooooooooooo");
    }
  }





void homepage::on_pushButtonadd_2_clicked()
{

    adduser->show();
}

void homepage::handlehidehomepageaftersuccessfullogout(){
    this->hide();
}

void homepage::handlechatusernamesignal(QString chatusername){
    QString token = receivedUser.getToken();
    chatClient->sendmessegeuser(token,chatusername,"hi");


}


void homepage::on_pushButton_getuserlist_on_homepage_clicked()
{
    QString token = receivedUser.getToken();
    chatClient->getuserlist(token);
}


void homepage::on_pushButton_getuserchats_on_homepage_clicked()
{
    QString token = receivedUser.getToken();
    chatClient->getuserchats(token,"khar");
}


void homepage::on_pushButton_creategroup_clicked()
{
    QString token = receivedUser.getToken();
    chatClient->creategroup(token,"hg_firstgroupcreated");
}


void homepage::on_pushButton_getgrouplist_clicked()
{
    QString token = receivedUser.getToken();
    chatClient->getgrouplist(token);
}

