#include"homepage.h"
#include "QtCore/qdir.h"
#include "ui_homepage.h"
#include<QMenu>
#include <QObject>
#include<QTimer>
#include<QMessageBox>
#include"creategroupname.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>
#include<QCoreApplication>
#include<QProcess>
#include"joingroupname.h"
#include"joinchannelname.h"
#include"createchannelname.h"

tokenuser receivedUser=tokenuser("","");
QStringList contatctuser,grouplist,channelList;
homepage::homepage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homepage)
{
     ui->setupUi(this);
     setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

     chatClient = new ChatClient(this);
     adduser =new newchatusername();
     logout = new confirmlogout();
     Creategroupname = nullptr;
     Joingroupname = nullptr;
     Createchannelname = nullptr;
     Joinchannelname = nullptr;
     connect(adduser, &newchatusername::sendchatusernametohomepage, this, &homepage::handlechatusernamesignal);
     connect(logout, &confirmlogout::hidehomepageaftersuccessfullogout, this, &homepage::handlehidehomepageaftersuccessfullogout);
     connect(chatClient, &ChatClient::getuserlistSuccess, this, &homepage::handlegetuserlistrSuccess);
     connect(chatClient, &ChatClient::getgrouplistSuccess, this, &homepage::handlegetgrouplistSuccess);
     connect(chatClient, &ChatClient::getchannellistSuccess, this, &homepage::handlegetchannellistSuccess);
     connect(chatClient, &ChatClient::getuserchatsSuccess, this, &::homepage::handlegetuserchatsSuccess);
     connect(chatClient, &ChatClient::getgroupchatsSuccess, this, &::homepage::handlegetgroupchatsSuccess);
     connect(chatClient, &ChatClient::getchannelchatsSuccess, this, &::homepage::handlegetchannelchatsSuccess);
     // Set up the QTimer to refresh the contacts every second

     QTimer* refreshTimer = new QTimer(this);

     connect(refreshTimer, &QTimer::timeout, this, &homepage::refreshContacts);
     connect(refreshTimer, &QTimer::timeout, this, &homepage::handlewhileoffline);
     connect(refreshTimer, &QTimer::timeout, this, &::homepage::handlegroupwhileoffline);
     connect(refreshTimer, &QTimer::timeout, this, &homepage::handlechannelwhileoffline);
     connect(refreshTimer, &QTimer::timeout, this, &homepage::refreshChatroom);
     connect(refreshTimer, &QTimer::timeout, this, &homepage::readInformationFromFile);

     refreshTimer->start(500); // Refresh every 1 second


     connect(ui->contactListWidget, &QListWidget::itemClicked, this, &homepage::contactClicked);
     connect(ui->groupListWidget, &QListWidget::itemClicked, this, &homepage::groupClicked);
     connect(ui->channelListWidget, &QListWidget::itemClicked, this, &homepage::channelClicked);

     ui->moreButton->setIcon(QIcon(":/send/icons8-more-80.png"));

     ui->sendButton->setIcon(QIcon(":/send/send/icons8-send-80.png"));

     ui->partlabel->hide();

     connect(chatClient,&ChatClient::sendmessageuserError,this,&homepage::handlesendmessageerror);
     connect(chatClient,&ChatClient::sendmessagegroupError,this,&homepage::handlesendmessageerror);
     connect(chatClient,&ChatClient::sendmessagechannelError,this,&homepage::handlesendmessageerror);


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

    QString username = person.getUsername();
    QString token = person.getToken();
    receivedUser=tokenuser(username,token);
    ui->label_2->setText("Hi, Welcome "+username+"! :)");


}

homepage::~homepage()
{
    delete ui;
}

void homepage::on_moreButton_clicked()
{
    logout->show();
}





void homepage::handlegetuserlistrSuccess(const QStringList &blocks)
{contatctuser=blocks;}

void homepage::handlewhileoffline()
{

    QStringList contactList;
    // Open the user contact file
    QFile file("user_contacts.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to read from file:" <<"user_contacts.txt";}

    QTextStream in(&file);
    while (!in.atEnd())
    {
        // Read each line from the file and add it to the contact list
        QString line = in.readLine();
        contactList.append(line);
    }

    // Close the file
    file.close();
    contatctuser=contactList;


}

void homepage::handlegroupwhileoffline(){
    QStringList grList;
    // Open the user contact file
    QFile file("grouplistoff.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to read from file:" <<"user_contacts.txt";}

    QTextStream in(&file);
    while (!in.atEnd())
    {
        // Read each line from the file and add it to the contact list
        QString line = in.readLine();
        grList.append(line);
    }

    // Close the file
    file.close();
    grouplist=grList;


}
void homepage::handlechannelwhileoffline(){
    QStringList chList;
    // Open the user contact file
    QFile file("channellistoff.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to read from file:" <<"user_contacts.txt";}

    QTextStream in(&file);
    while (!in.atEnd())
    {
        // Read each line from the file and add it to the contact list
        QString line = in.readLine();
        chList.append(line);
    }

    // Close the file
    file.close();
    channelList=chList;


}



void homepage::refreshChatroom()
{



    QString token = receivedUser.getToken();
    if(!ui->profile_lable->text().isNull()&&ui->partlabel->text()=="user"){
        //readInformationFromFile();
    chatClient->getuserchats(token, ui->profile_lable->text());
      }
    if(!ui->profile_lable->text().isNull()&&ui->partlabel->text()=="group"){  //readInformationFromFile();
        chatClient->getgroupchats(token, ui->profile_lable->text());
      }

    if(!ui->profile_lable->text().isNull()&&ui->partlabel->text()=="channel"){  //readInformationFromFile();
        chatClient->getchannelchats(token, ui->profile_lable->text());
    }

}


void homepage::handlegetgrouplistSuccess(const QStringList &blocks)
{grouplist=blocks;


}



void homepage::handlegetuserchatsSuccess(const QStringList &blocks)
{
       QString folderName = "user";
    QDir folder("user");
    if (!folder.exists())
        folder.mkpath(".");

    foreach (const QString& blockSource, contatctuser)
    {
        QString filePath = folderName + "/" + blockSource+".txt";
        QFile file(filePath);





        // Read existing content
        QString existingContent;

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            existingContent = in.readAll();
            file.close();
        }

        // Append new content if there are differences
        QString newContent;
        for (int i = 0; i < blocks.size(); i += 4) {
            QString body = blocks.at(i);
            QString dst = blocks.at(i + 1);
            QString src = blocks.at(i + 2);
            QString time = blocks.at(i + 3);
            if (src == blockSource || dst == blockSource) {
                QString line = src + ":" + body + "\n" + time + "\n";
                if (!existingContent.contains(line))
                    newContent += line;
            }
        }

        // Append new content to the file
        if (!newContent.isEmpty() && file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << newContent;
            file.close();
        } else {
            qDebug() << "Failed to append additions to file:" << blockSource;
        }
    }
}

void homepage::handlegetgroupchatsSuccess(const QStringList &blocks)
{
    QString folderName = "group";
    QDir folder("group");
    if (!folder.exists())
        folder.mkpath(".");

    foreach (const QString& blockSource, grouplist)
    {
        QString filePath = folderName + "/" + blockSource+".txt";
        QFile file(filePath);




        // Open the file for writing
        // Read existing content
        QString existingContent;

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            existingContent = in.readAll();
            file.close();
        }

        // Append new content if there are differences
        QString newContent;
        for (int i = 0; i < blocks.size(); i += 4) {
            QString body = blocks.at(i);
            QString dst = blocks.at(i + 1);
            QString src = blocks.at(i + 2);
            QString time = blocks.at(i + 3);
            if (src == blockSource || dst == blockSource) {
                QString line = src + ":" + body + "\n" + time + "\n";
                if (!existingContent.contains(line))
                    newContent += line;
            }
        }

        // Append new content to the file
        if (!newContent.isEmpty() && file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << newContent;
            file.close();
        } else {
            qDebug() << "Failed to append additions to file:" << blockSource;
        }
    }
}
void homepage::handlegetchannelchatsSuccess(const QStringList &blocks)
{
    QString folderName = "channel";
    QDir folder("channel");
    if (!folder.exists())
        folder.mkpath(".");

    foreach (const QString& blockSource, channelList)
    {
        QString filePath = folderName + "/" + blockSource+".txt";
        QFile file(filePath);




        // Open the file for writing
        // Read existing content
        QString existingContent;

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            existingContent = in.readAll();
            file.close();
        }

        // Append new content if there are differences
        QString newContent;
        for (int i = 0; i < blocks.size(); i += 4) {
            QString body = blocks.at(i);
            QString dst = blocks.at(i + 1);
            QString src = blocks.at(i + 2);
            QString time = blocks.at(i + 3);
            if (src == blockSource || dst == blockSource) {
                QString line = src + ":" + body + "\n" + time + "\n";
                if (!existingContent.contains(line))
                    newContent += line;
            }
        }

        // Append new content to the file
        if (!newContent.isEmpty() && file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << newContent;
            file.close();
        } else {
            qDebug() << "Failed to append additions to file:" << blockSource;
        }
    }
}


void homepage::readInformationFromFile()
{
    if( ui->partlabel->text()=="user"|| ui->partlabel->text()=="channel"|| ui->partlabel->text()=="group"){
           QString folderName = ui->partlabel->text();
        QDir folder(folderName);
        if (!folder.exists())
            folder.mkpath(".");
             QString blockSource = ui->profile_lable->text();

            QString filePath = folderName + "/" + blockSource+".txt";
            QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for reading"<<blockSource;
            return;
        }
        QString exist=ui->chatroom->toPlainText();
        QTextStream stream(&file);
        QStringList information;
        QString line;
        QString existingChatroomContent;
        QTextDocument document;

        // Read the file line by line
        bool isBodyLine = true;
        QString bodyText;
        while (!stream.atEnd()) {
            line = stream.readLine();

            if (isBodyLine) {
                bodyText = line;
                qDebug() << line;
                isBodyLine = false;
            } else {
                QString time = line;


                existingChatroomContent+=bodyText + '\n';

                existingChatroomContent+= time + '\n';

                existingChatroomContent+="____________________________________________\n";

                isBodyLine = true;
            }
        }


        // Compare the lengths of existingChatroomContent and exist
        if (existingChatroomContent.length() > exist.length()) {
            // Find the additions in existingChatroomContent
            QString additions = existingChatroomContent.mid(exist.length()).trimmed();

            // Append the additions to the chatroom
            ui->chatroom->append(additions);
        }

        // Append the formatted content to the string
        // existingChatroomContent = document.toHtml();


        // Display the formatted content in a QTextBrowser widget

        file.close();}

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
    ui->chatroom->clear();
    ui->partlabel->setText("channel");

    // Handle the click event for the selected contact
    // You can implement your own logic here, such as opening a chat window, showing contact details, etc.
 }
 void homepage::groupClicked(QListWidgetItem* item)
 {
    QString contact = item->text();
    ui->profile_lable->setText(contact);
    ui->chatroom->clear();
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
    chatClient->sendmessegeuser(token,chatusername,"Hello");


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
        chatClient->sendmessegechannel(token,ui->profile_lable->text(),ui->messagebar->toPlainText());
        ui->messagebar->clear();

    }}

}

void homepage::handlesendmessageerror(const QString &errormessage)
{
    QMessageBox::critical(this,"Send Message",errormessage);

}




void homepage::on_pushButton_creategroup_on_homepage_clicked()
{
    if (!Creategroupname) {
            Creategroupname = new creategroupname(this); // Create an instance of the new window
            Creategroupname->setAttribute(Qt::WA_DeleteOnClose); // Delete the window when closed
        }

        Creategroupname->show();
}


void homepage::on_pushButton_joingroup_on_homepage_clicked()
{
    if (!Joingroupname) {
            Joingroupname = new joingroupname(this); // Create an instance of the new window
            Joingroupname->setAttribute(Qt::WA_DeleteOnClose); // Delete the window when closed
        }

        Joingroupname->show();
}


void homepage::on_pushButton_createchannel_on_homepage_clicked()
{
    if (!Createchannelname) {
            Createchannelname = new createchannelname(this); // Create an instance of the new window
            Createchannelname->setAttribute(Qt::WA_DeleteOnClose); // Delete the window when closed
        }

        Createchannelname->show();
}


void homepage::on_pushButton_joinchannel_on_homepage_clicked()
{
    if (!Joinchannelname) {
            Joinchannelname = new joinchannelname(this); // Create an instance of the new window
            Joinchannelname->setAttribute(Qt::WA_DeleteOnClose); // Delete the window when closed
        }

        Joinchannelname->show();
}

void deleteFile(const QString& filePath)
{
        QFile file(filePath);

        // Check if the file exists
        if (!file.exists())
        {
            qWarning() << "File does not exist:" << filePath;
            return ;
        }

        // Attempt to remove the file
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qWarning() << "Failed to delete file:" << file.errorString();
            return ;
        }file.close();

        qDebug() << "File deleted successfully:" << filePath;
        return ;
}


void homepage::handlelogoutSuccesshm(){
    QString folderName = "channel";
    QDir folder("channel");
    if (!folder.exists())
        folder.mkpath(".");

    foreach (const QString& blockSource, channelList)
    {
        QString filePath = folderName + "/" + blockSource+".txt";
        QFile file(filePath);


        }
    QString folderName2 = "group";
    QDir folder2("group");
    if (!folder2.exists())
        folder2.mkpath(".");

    foreach (const QString& blockSource, grouplist)
    {
        QString filePath = folderName2 + "/" + blockSource+".txt";
        QFile file(filePath);



            deleteFile(filePath);}
    QString folderName3 = "user";
    QDir folder3("user");
    if (!folder3.exists())
        folder3.mkpath(".");

    foreach (const QString& blockSource, contatctuser)
    {
        QString filePath = folderName3 + "/" + blockSource+".txt";
        QFile file(filePath);



            deleteFile(filePath);
        }
        deleteFile("channellistoff.txt");
        deleteFile("grouplistoff.txt");
        deleteFile("user_contacts.txt");


}
