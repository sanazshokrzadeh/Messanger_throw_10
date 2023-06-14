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

void ChatClient::signIn(const QString &username, const QString &password)
{
    QString requestUrl = "http://api.barafardayebehtar.ml:8080/signin?";
    requestUrl += "username=" + username;
    requestUrl += "&password=" + password;

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(requestUrl)));
    reply->setProperty("requestType", "signIn");
}

void ChatClient::handleNetworkReply(QNetworkReply *reply)
{
    QString requestType = reply->property("requestType").toString();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error:" << reply->errorString();
        if (requestType == "signUp") {
            emit signUpError("Network error");
        } else if (requestType == "signIn") {
            emit signInError("Network error");
        }
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isObject()) {
        qDebug() << "Invalid JSON response:" << responseData;
        if (requestType == "signUp") {
            emit signUpError("Invalid JSON response");
        } else if (requestType == "signIn") {
            emit signInError("Invalid JSON response");
        }
        reply->deleteLater();
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();

    int code = jsonObject.value("code").toInt();
    QString message = jsonObject.value("message").toString();

    if (requestType == "signUp") {
        if (code == 200) {
            QString token = jsonObject.value("token").toString();
            emit signUpSuccess(token);
        } else {
            emit signUpError(message);
        }
    } else if (requestType == "signIn") {
        if (code == 200) {
            QString token = jsonObject.value("token").toString();
            emit signInSuccess(token);
        } else {
            emit signInError(message);
        }
    }

    reply->deleteLater();
}

void ChatClient::processSignUpResponse(const QJsonObject &jsonObject)
{
    // Process the sign-up response JSON data
    // Update the UI or take any other necessary action
}

void ChatClient::processSignInResponse(const QJsonObject &jsonObject)
{
    // Process the sign-in response JSON data
    // Update the UI or take any other necessary action
}
