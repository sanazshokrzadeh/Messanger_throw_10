#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class ChatClient : public QObject
{
    Q_OBJECT

public:
    explicit ChatClient(QObject *parent = nullptr);

    void signUp(const QString &username, const QString &password, const QString &firstName, const QString &lastName);
    void signIn(const QString &username, const QString &password);
    // Add other member functions as needed

signals:
    // Define signals to communicate with the UI
    void signUpSuccess(const QString &token);
    void signUpError(const QString &errorMessage);
    void signInSuccess(const QString &token);
    void signInError(const QString &errorMessage);

private slots:
    void handleNetworkReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;

    void processSignUpResponse(const QJsonObject &jsonObject);
    void processSignInResponse(const QJsonObject &jsonObject);
    // Add other private member functions as needed
};


#endif // CHATCLIENT_H
