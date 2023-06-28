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
    void logIn(const QString &username, const QString &password);
    void logout(const QString &username, const QString &password);
    void sendmessegeuser (const QString &token, const QString &dst,const QString &body);


   // void sendmessegegroup(const QString &token, const QString &sdt,const QString &body);
signals:
    // Define signals to communicate with the UI
    void signUpSuccess();
    void signUpError(const QString &errorMessage);
    void logInSuccess(const QString &token);
    void logInError(const QString &errorMessage);
    void logoutSuccess();
    void logoutError(const QString &errorMessage);
    void AlreadyLogIn();

private slots:
    void handleNetworkReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;


};


#endif // CHATCLIENT_H
