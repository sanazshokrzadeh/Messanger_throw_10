#include "chatclient.h"

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
    QString requestUrl = "http://api.barafardayebehtar.ml:8080/signin?";
    requestUrl += "username=" + username;
    requestUrl += "&password=" + password;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "logIn");
}

void ChatClient::handleNetworkReply(QNetworkReply *reply)
{
    QString requestType = reply->property("requestType").toString();
    QString replyMessage = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(replyMessage.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    QString message = jsonObj["message"].toString();
    QString code = jsonObj["code"].toString();

    qDebug() << "Received Reply:";
    qDebug() << "Message:" << message;
    qDebug() << "Code:" << code;

    if (requestType == "signUp") {
        if (code == "200") {
            // SignUp successful, do something
        }
        else if (code == "204") {
            emit signUpError("Duplicate request");
        }
        else {
            emit signUpError("Error: " + message);
        }
    }
    else if (requestType == "logIn") {
        if (code == "200") {
            QString token = jsonObj["token"].toString();
            // LogIn successful, do something with the token
        }
        else if (code == "401") {
            emit logInError("Incorrect information");
        }
        else {
            emit logInError("Error: " + message);
        }
    }

    // Clean up the network reply
    reply->deleteLater();
}



