#include"homepage.h"
#include "QtCore/qdir.h"
#include "ui_homepage.h"
#include<QMenu>
#include <QObject>
#include<QTimer>
#include<QMessageBox>
#include"creategroupname.h"

tokenuser receivedUser=tokenuser("","");
QStringList contatctuser,grouplist,channelList;
homepage::homepage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homepage)
{    ui->setupUi(this);
     setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

     chatClient = new ChatClient(this);
     adduser =new newchatusername();
     logout = new confirmlogout();
     groupname = nullptr;
     connect(adduser, &newchatusername::sendchatusernametohomepage, this, &homepage::handlechatusernamesignal);
     connect(logout, &confirmlogout::hidehomepageaftersuccessfullogout, this, &homepage::handlehidehomepageaftersuccessfullogout);
     connect(chatClient, &ChatClient::getuserlistSuccess, this, &homepage::handlegetuserlistrSuccess);
     connect(chatClient, &ChatClient::getgrouplistSuccess, this, &homepage::handlegetgrouplistSuccess);
     connect(chatClient, &ChatClient::getchannellistSuccess, this, &homepage::handlegetchannellistSuccess);
     connect(chatClient, &ChatClient::getuserchatsSuccess, this, &::homepage::handlegetuserchatsSuccess);
     // Set up the QTimer to refresh the contacts every second

     QTimer* refreshTimer = new QTimer(this);
     connect(refreshTimer, &QTimer::timeout, this, &homepage::refreshContacts);
     connect(refreshTimer, &QTimer::timeout, this, &homepage::refreshChatroom);
     refreshTimer->start(500); // Refresh every 1 second


     connect(ui->contactListWidget, &QListWidget::itemClicked, this, &homepage::contactClicked);
     connect(ui->groupListWidget, &QListWidget::itemClicked, this, &homepage::groupClicked);
     connect(ui->channelListWidget, &QListWidget::itemClicked, this, &homepage::channelClicked);
     ui->moreButton->setIcon(QIcon(":/send/icons8-more-80.png"));
     ui->settingsButton->setIcon(QIcon(":/send/icons8-menu-80.png"));
     ui->sendButton->setIcon(QIcon(":/send/send/icons8-send-80.png"));
     //ui->label
     ui->partlabel->hide();

     //login=new loginDialog(this);
     //connect(login, &loginDialog::sig_logintohomepage, this, &homepage::handletoken);
}
void homepage::startRefreshTimer()
{
     QTimer* refreshTimer = new QTimer(this);
     connect(refreshTimer, &QTimer::timeout, this, &homepage::refreshContacts);
     refreshTimer->start(500);

     // Refresh every 1 second
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
{contatctuser=blocks;}

void homepage::refreshChatroom()
{
    ui->chatroom->clear();
    QString token = receivedUser.getToken();
    if(!ui->profile_lable->text().isNull()&&ui->partlabel->text()=="user"){
    chatClient->getuserchats(token, ui->profile_lable->text());
        readInformationFromFile();}
}


void homepage::handlegetgrouplistSuccess(const QStringList &blocks)
{grouplist=blocks;


}

void homepage::handlegetuserchatsSuccess(const QStringList &blocks)
{   QString folderName = "user";
    QDir folder;
    if (!folder.exists(folderName))
        folder.mkdir(folderName);

    // Create the file inside the folder

    for (int i = 0; i < contatctuser.size(); ++i) {

        QString blockSource = contatctuser.at(i);

        // Create a file name based on the block source
        QString fileName = blockSource + ".txt";
        QString filePath = folder.absoluteFilePath(fileName);
        // Open the file for writing
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
           // qDebug()<<"file named"<<fileName<<"created\n";
            // Write the block source to the file
            for (int i = 0; i < blocks.size(); i+=4) {

                QString body = blocks.at(i);
                QString dst =blocks.at(i + 1);
                QString src = blocks.at(i + 2); QString time = blocks.at(i + 3);
                if(src==blockSource||dst==blockSource){
                    out<<src<< ":" << body << "\n";
               out << time << "\n";

               // out << "\n";
                }
            }

            // Close the file
            file.close();
        } else {
            qDebug() << "Failed to create file:" << fileName;
        }
    }
}
void homepage::readInformationFromFile()
{
    QString folderName = "user";
    QDir folder;
    if (!folder.exists(folderName))
        folder.mkdir(folderName);
    QString blockSource = ui->profile_lable->text();
    QString fileName = blockSource + ".txt";
    QString filePath = folder.absoluteFilePath(fileName);
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading";
        return;
    }

    QTextStream stream(&file);
    QStringList information;
    QString line;

    // Read the file line by line
    while (stream.readLineInto(&line)) {

        QString body = line;
        qDebug()<<line;
        QString time = stream.readLine();
        QTextCursor cursor = ui->chatroom->textCursor();
        QTextCharFormat defaultFormat = cursor.charFormat();

        // Set the font properties for the time
        QTextCharFormat timeFormat = defaultFormat;
        timeFormat.setFontFamily("Roboto");
        timeFormat.setFontPointSize(8);
        timeFormat.setFontWeight(QFont::Normal);
        QColor timeColor("#c1e1c1");
        timeFormat.setForeground(timeColor);
        // Append the body text
        cursor.insertText(body + '\n', defaultFormat);

        // Append the time with the desired fontType
        cursor.insertText(time + '\n', timeFormat);

        // Append the separator
        cursor.insertText("_______________________________________\n", defaultFormat);

        // Scroll to the bottom
       ui->chatroom->ensureCursorVisible();
      //  ui->chatroom->append(body+'\n'+formattedTime+"\n_______________________________________\n");
        // Create a QTextCursor to manipulate the text in the QTextBrowser



        }
    file.close();

   // qDebug() << "Information read from file:\n" << content;
}


void homepage::handlegetchannellistSuccess(const QStringList &blocks)
{channelList=blocks;


}
 void homepage::contactClicked(QListWidgetItem* item)
 {
    QString contact = item->text();
    ui->profile_lable->setText(contact);
    ui->chatroom->clear();
    ui->partlabel->setText("user");
    // Handle the click event for the selected contact
    // You can implement your own logic here, such as opening a chat window, showing contact details, etc.
 }
 void homepage::channelClicked(QListWidgetItem* item)
 {
    QString contact = item->text();
    ui->profile_lable->setText(contact);
 ui->partlabel->setText("channel");

    // Handle the click event for the selected contact
    // You can implement your own logic here, such as opening a chat window, showing contact details, etc.
 }
 void homepage::groupClicked(QListWidgetItem* item)
 {
    QString contact = item->text();
    ui->profile_lable->setText(contact);
 ui->partlabel->setText("group");
    // Handle the click event for the selected contact
    // You can implement your own logic here, such as opening a chat window, showing contact details, etc.
 }
 void homepage::refreshContacts()
 {
    QString token = receivedUser.getToken();
    chatClient->getuserlist(token);
    chatClient->getgrouplist(token);
    chatClient->getchannellist(token);
    // Clear the existing contacts and groups in the list widgets

    ui->groupListWidget->clear();
    // Clear the existing contacts in the list widget
    ui->contactListWidget->clear();
    ui->channelListWidget->clear();
    // Retrieve the updated contact list
    QStringList contacts = contatctuser;// Replace with your own logic to get the updated contacts
    QStringList groups = grouplist;
    QStringList channels=channelList;
    // Add the contacts to the list widget
    for (const QString& contact : contacts) {
        QListWidgetItem* item = new QListWidgetItem(contact);
        item->setFlags(item->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->contactListWidget->addItem(item);
    }
    for (const QString& group : groups) {
        QListWidgetItem* item = new QListWidgetItem(group);
        item->setFlags(item->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->groupListWidget->addItem(item);
    }
    for (const QString& channel : channels) {
        QListWidgetItem* item = new QListWidgetItem(channel);
        item->setFlags(item->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->channelListWidget->addItem(item);
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












void homepage::on_sendButton_clicked()
{
   QString token = receivedUser.getToken();
    QString part = ui->partlabel->text();
   if(part.isNull()){
        QMessageBox::information(this, "message", "You need to type something!");
    }
   else{
    if(part == "user"){

        chatClient->sendmessegeuser(token,ui->profile_lable->text(),ui->messagebar->toPlainText());
        ui->messagebar->clear();

    }
    else if(part == "group"){
        chatClient->sendmessegegroup(token,ui->profile_lable->text(),ui->messagebar->toPlainText());
        ui->messagebar->clear();

    }
    else if(part == "channel"){

    }}

}

void homepage::on_pushButton_creategroup_on_homepage_clicked()
{
    if (!groupname) {
            groupname = new creategroupname(this); // Create an instance of the new window
            groupname->setAttribute(Qt::WA_DeleteOnClose); // Delete the window when closed
        }

        groupname->show();
}

