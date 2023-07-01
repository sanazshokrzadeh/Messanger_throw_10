#include "chatclient.h"
#include "qdir.h"
#include<QMessageBox>

ChatClient::ChatClient(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &ChatClient::handleNetworkReply);

}

void ChatClient::signUp(const QString &username, const QString &password, const QString &firstName, const QString &lastName)
{
    QString requestUrl = "http://api.barafardayebehtar.ml:8080/signup?";
    requestUrl += "username=" + username;
    requestUrl += "&password=" + password;
    requestUrl += "&firstname=" + firstName;
    requestUrl += "&lastname=" + lastName;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));

    reply->setProperty("requestType", "signUp");
}

void ChatClient::logIn(const QString &username, const QString &password)
{
    QString requestUrl = "http://api.barafardayebehtar.ml:8080/login?";
    requestUrl += "username=" + username;
    requestUrl += "&password=" + password;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "logIn");
}

void ChatClient::logout(const QString &username, const QString &password)
{
    QString requestUrl = "http://api.barafardayebehtar.ml:8080/logout?";
    requestUrl += "username=" + username;
    requestUrl += "&password=" + password;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "logout");
}


////////////////////////////////////////////sending user requests///////////////////////////////////////////////////////

void ChatClient::sendmessegeuser (const QString &token, const QString &dst,const QString &body)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/sendmessageuser?";
    requestUrl += "token=" + token;
    requestUrl += "&dst=" + dst;
    requestUrl += "&body=" + body;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "sendmessageuser");
}

void ChatClient::getuserlist (const QString &token)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/getuserlist?";
    requestUrl += "token=" + token;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "getuserlist");
}


void ChatClient::getuserchats (const QString &token, const QString &dst)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/getuserchats?";
    requestUrl += "token=" + token;
    requestUrl += "&dst=" + dst;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "getuserchats");
}

////////////////////////////////////////////sending group requests///////////////////////////////////////////////////////

void ChatClient::creategroup (const QString &token, const QString &group_name)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/creategroup?";
    requestUrl += "token=" + token;
    requestUrl += "&group_name=" + group_name;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "creategroup");
}

void ChatClient::getgrouplist (const QString &token)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/getgrouplist?";
    requestUrl += "token=" + token;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "getgrouplist");
}

void ChatClient::joingroup (const QString &token, const QString &group_name)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/joingroup?";
    requestUrl += "token=" + token;
    requestUrl += "&group_name=" + group_name;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "joingroup");
}

void ChatClient::sendmessegegroup (const QString &token, const QString &dst,const QString &body)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/sendmessagegroup?";
    requestUrl += "token=" + token;
    requestUrl += "&dst=" + dst;
    requestUrl += "&body=" + body;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "sendmessagegroup");
}

void ChatClient::getgroupchats (const QString &token, const QString &dst)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/getgroupchats?";
    requestUrl += "token=" + token;
    requestUrl += "&dst=" + dst;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "getgroupchats");
}

////////////////////////////////////////////sending channel requests///////////////////////////////////////////////////////

void ChatClient::createchannel (const QString &token, const QString &channel_name)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/createchannel?";
    requestUrl += "token=" + token;
    requestUrl += "&channel_name=" + channel_name;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "createchannel");
}

void ChatClient::getchannellist (const QString &token)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/getchannellist?";
    requestUrl += "token=" + token;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "getchannellist");
}

void ChatClient::joinchannel (const QString &token, const QString &channel_name)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/joinchannel?";
    requestUrl += "token=" + token;
    requestUrl += "&channel_name=" + channel_name;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "joinchannel");
}

void ChatClient::sendmessegechannel (const QString &token, const QString &dst,const QString &body)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/sendmessagechannel?";
    requestUrl += "token=" + token;
    requestUrl += "&dst=" + dst;
    requestUrl += "&body=" + body;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "sendmessagechannel");
}

void ChatClient::getchannelchats (const QString &token, const QString &dst)
{

    QString requestUrl = "http://api.barafardayebehtar.ml:8080/getchannelchats?";
    requestUrl += "token=" + token;
    requestUrl += "&dst=" + dst;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "getchannelchats");
}

///////////////////////////////////////////////////////////////////////////////////////////////////


void createFiles(const QStringList& stringList, const QString& folderPath)
{
    // Create the folder if it doesn't exist
    QDir folder(folderPath);
    if (!folder.exists())
        folder.mkpath(".");

    foreach (const QString& str, stringList)
    {
        QString filePath = folderPath + "/" + str+".txt";
        QFile file(filePath);

        // Check if the file already exists
        if (file.exists())
        {
            qWarning() << "File already exists:" << filePath;
            continue;
        }

        // Create the file
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.close();
            qDebug() << "File created successfully:" << filePath;
        }
        else
        {
            qWarning() << "Failed to create file:" << file.errorString();
        }
    }
}


void ChatClient::writeToFile(const QStringList& contactList, const QString& fileName)
{
    // Open the file for writing
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Failed to open the file
        return;
    }

    QTextStream out(&file);
    for (const QString& contact : contactList)
    {
        // Write each contact to a new line in the file
        out << contact << '\n';
    }

    // Close the file
    file.close();
}




void ChatClient::handleNetworkReply(QNetworkReply *reply)
{
    QString requestType = reply->property("requestType").toString();
    QString replyMessage = reply->readAll();
   qDebug() << replyMessage;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(replyMessage.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    QString message = jsonObj["message"].toString();
    QString code = jsonObj["code"].toString();

    qDebug() << "Received Reply:";
    qDebug() << "Message:" << message;
    qDebug() << "Code:" << code;

    if (requestType == "signUp") {
        if (code == "200") {
            emit signUpSuccess();
            // SignUp successful, do something
        }
        else {
            emit signUpError("Error: " + message);
        }
    }
    else if (requestType == "logIn") {
        if(message=="You are already logged in!"){
            emit AlreadyLogIn();
        }
        else if (code == "200") {
            QString token = jsonObj["token"].toString();
            qDebug()<<token;
          emit logInSuccess(token);

            // LogIn successful, do something with the token
        }
        else {
            emit logInError("Error: " + message);
        }
    }
    else if (requestType == "logout") {
        if (code == "200") {
            emit logoutSuccess();
            // logout successful, do something
        }
        else {
            emit logoutError("Error: " + message);
        }
    }

    ////////////////////////user replies/////////////////////////////

    else if (requestType == "sendmessageuser") {
            if (code == "200") {
                emit sendmessageuserSuccess();
                // sendmessageuser successful, do something
            }
            else {
                emit sendmessageuserError("Error: " + message);
            }
        }
        else if (requestType == "getuserlist") {
            if (code == "200") {

                // sendmessageuser successful, do something
                QJsonObject blocksObj = jsonObj;
                blocksObj.remove("message");
                blocksObj.remove("code");

                QStringList keys = blocksObj.keys();
                int numBlocks = keys.size();
                //qDebug() << "Number of blocks:" << numBlocks;
                QStringList block;

                for (int i = 0; i < numBlocks; ++i) {
                    QString blockKey = "block " + QString::number(i);
                    QJsonObject blockObj = blocksObj.value(blockKey).toObject();
                    QString src = blockObj["src"].toString();
                    block<<src;
                    qDebug() << "block" << i ;
                    qDebug() << "src:" << src;
                    // Do something with the src value

                }
               createFiles(block,"user");
                writeToFile(block,"user_contacts.txt");
                emit getuserlistSuccess(block);
            }
            else {
                emit getuserlistError("Error: " + message);
            }
        }
    else if (requestType == "getuserchats") {
        if (code == "200") {
          //  emit getuserchatsSuccess();
            // getuserchats successful, do something

            QJsonObject blocksObj = jsonObj;
            blocksObj.remove("message");
            blocksObj.remove("code");

            QStringList keys = blocksObj.keys();
            int numBlocks = keys.size();
            //qDebug() << "Number of blocks:" << numBlocks;
            QStringList message;
            for (int i = 0; i < numBlocks; ++i) {
                QString blockKey = "block " + QString::number(i);
                QJsonObject blockObj = blocksObj.value(blockKey).toObject();
                QString body = blockObj["body"].toString();
                QString src = blockObj["src"].toString();
                QString dst = blockObj["dst"].toString();
                QString date = blockObj["date"].toString();
                qDebug() << "block" << i;
                qDebug() << "body:" << body;
                qDebug() << "src:" << src;
                qDebug() << "dst:" << dst;
                qDebug() << "date:" << date;
                message<<body<<dst<<src<<date;



                // Do something with the block contents

            }
            emit getuserchatsSuccess(message);
        }
        else {
            emit getuserchatsError("Error: " + message);
        }
    }

    ////////////////////////group replies/////////////////////////////

    else if (requestType == "creategroup") {
        if (code == "200") {
            emit creategroupSuccess("Message: " + message);
            // creategroup successful, do something
        }
        else {
            emit creategroupError("Error: " + message);
        }
    }
    else if (requestType == "getgrouplist") {
        if (code == "200") {

            // getgrouplist successful, do something
            QJsonObject blocksObj = jsonObj;
            blocksObj.remove("message");
            blocksObj.remove("code");

            QStringList keys = blocksObj.keys();
            int numBlocks = keys.size();
            //qDebug() << "Number of blocks:" << numBlocks;
            QStringList blocks;
            for (int i = 0; i < numBlocks; ++i) {
                QString blockKey = "block " + QString::number(i);
                QJsonObject blockObj = blocksObj.value(blockKey).toObject();
                QString group_name = blockObj["group_name"].toString();
                blocks<<group_name;
                qDebug() << "block" << i ;
                qDebug() <<"group_name:" << group_name;
                // Do something with the group_name value
            }
            writeToFile(blocks,"grouplistoff.txt");
            createFiles(blocks,"group");
            emit getgrouplistSuccess(blocks);
        }
        else {
            emit getgrouplistError("Error: " + message);
        }
    }
    else if (requestType == "joingroup") {
        if (code == "200") {
            emit joingroupSuccess("Message: " + message);
            // joingroup successful, do something
        }
        else {
            emit joingroupError("Error: " + message);
        }
    }
    else if (requestType == "sendmessagegroup") {
        if (code == "200") {
            emit sendmessagegroupSuccess();
            // sendmessagegroup successful, do something
        }
        else {
            emit sendmessagegroupError("Error: " + message);
        }
    }
    else if (requestType == "getgroupchats") {
        if (code == "200") {

            QJsonObject blocksObj = jsonObj;
            blocksObj.remove("message");
            blocksObj.remove("code");

            QStringList keys = blocksObj.keys();
            int numBlocks = keys.size();

            QStringList message;
            for (int i = 0; i < numBlocks; ++i) {
                QString blockKey = "block " + QString::number(i);
                QJsonObject blockObj = blocksObj.value(blockKey).toObject();

                QString body = blockObj["body"].toString();
                QString src = blockObj["src"].toString();
                QString dst = blockObj["dst"].toString();
                QString date = blockObj["date"].toString();
                qDebug() << "Groupblock" << i;
                qDebug() << "body:" << body;
                qDebug() << "src:" << src;
                qDebug() << "dst:" << dst;
                qDebug() << "date:" << date;
                // Do something with the block contents
                message<<body<<dst<<src<<date;

            }emit getgroupchatsSuccess(message);
        }
        else {
            emit getgroupchatsError("Error: " + message);
        }
    }


    ////////////////////////channel replies/////////////////////////////

    else if (requestType == "createchannel") {
        if (code == "200") {
            emit createchannelSuccess("Message: " + message);
            // createchannel successful, do something
        }
        else {
            emit createchannelError("Error: " + message);
        }
    }
    else if (requestType == "getchannellist") {
        if (code == "200") {

            // getchannellist successful, do something
            QJsonObject blocksObj = jsonObj;
            blocksObj.remove("message");
            blocksObj.remove("code");

            QStringList keys = blocksObj.keys();
            int numBlocks = keys.size();
            QStringList blocks;
            for (int i = 0; i < numBlocks; ++i) {
                QString blockKey = "block " + QString::number(i);
                QJsonObject blockObj = blocksObj.value(blockKey).toObject();
                QString channel_name = blockObj["channel_name"].toString();
                qDebug() << "block" << i;
                qDebug() << "channel_name:" << channel_name;
                blocks<<channel_name;
                // Do something with the channel_name value
            }
            writeToFile(blocks,"channellistoff.txt");
            createFiles(blocks,"channel");
            emit getchannellistSuccess(blocks);
        }
        else {
            emit getchannellistError("Error: " + message);
        }
    }
    else if (requestType == "joinchannel") {
        if (code == "200") {
            emit joinchannelSuccess("Message: " + message);
            // joinchannel successful, do something
        }
        else {
            emit joinchannelError("Error: " + message);
        }
    }
    else if (requestType == "sendmessagechannel") {
        if (code == "200") {
            emit sendmessagechannelSuccess();
            // sendmessagechannel successful, do something
        }
         else
            emit sendmessagechannelError("Error: " + message);

        }

    else if (requestType == "getchannelchats") {
        if (code == "200") {

            // getchannelchats successful, do something

            QJsonObject blocksObj = jsonObj;
            blocksObj.remove("message");
            blocksObj.remove("code");

            QStringList keys = blocksObj.keys();
            int numBlocks = keys.size();
            QStringList message;
            for (int i = 0; i < numBlocks; ++i) {
                QString blockKey = "block " + QString::number(i);
                QJsonObject blockObj = blocksObj.value(blockKey).toObject();
                QString body = blockObj["body"].toString();
                QString src = blockObj["src"].toString();
                QString dst = blockObj["dst"].toString();
                QString date = blockObj["date"].toString();
                qDebug() << "block" << i;
                qDebug() << "body:" << body;
                qDebug() << "src:" << src;
                qDebug() << "dst:" << dst;
                qDebug() << "date:" << date;
                 message<<body<<dst<<src<<date;
                // Do something with the block contents
            } emit getchannelchatsSuccess(message);
        }
        else {
            emit getchannelchatsError("Error: " + message);
        }
    }



    // Clean up the network reply
    reply->deleteLater();
}


