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

    void getuserlist(const QString &token);
    void sendmessegeuser (const QString &token, const QString &dst,const QString &body);
    void getuserchats (const QString &token, const QString &dst);

    void creategroup(const QString &token, const QString &group_name);
    void getgrouplist(const QString &token);
    void joingroup(const QString &token, const QString &group_name);
    void sendmessegegroup(const QString &token, const QString &dst,const QString &body);
    void getgroupchats(const QString &token, const QString &dst);

    void createchannel(const QString &token, const QString &group_name);
    void getchannellist(const QString &token);
    void joinchannel(const QString &token, const QString &group_name);
    void sendmessegechannel(const QString &token, const QString &dst,const QString &body);
    void getchannelchats(const QString &token, const QString &dst);



signals:
    // Define signals to communicate with the UI
    void signUpSuccess();
    void signUpError(const QString &errorMessage);
    void logInSuccess(const QString &token);
    void logInError(const QString &errorMessage);
    void logoutSuccess();
    void logoutError(const QString &errorMessage);
    void AlreadyLogIn();

    void sendmessageuserSuccess();
    void sendmessageuserError(const QString &errorMessage);
    void getuserlistSuccess(const QStringList & blocks);
    void getuserlistError(const QString &errorMessage);
    void getuserchatsSuccess();
    void getuserchatsError(const QString &errorMessage);

    void createchannelSuccess();
    void createchannelError(const QString &errorMessage);
    void getchannellistSuccess(const QStringList & blocks);
    void getchannellistError(const QString &errorMessage);
    void joinchannelSuccess();
    void joinchannelError(const QString &errorMessage);
    void sendmessagechannelSuccess();
    void sendmessagechannelError(const QString &errorMessage);
    void getchannelchatsSuccess();
    void getchannelchatsError(const QString &errorMessage);

    void creategroupSuccess();
    void creategroupError(const QString &errorMessage);
    void getgrouplistSuccess(const QStringList & blocks);
    void getgrouplistError(const QString &errorMessage);
    void joingroupSuccess();
    void joingroupError(const QString &errorMessage);
    void sendmessagegroupSuccess();
    void sendmessagegroupError(const QString &errorMessage);
    void getgroupchatsSuccess();
    void getgroupchatsError(const QString &errorMessage);


private slots:
    void handleNetworkReply(QNetworkReply *reply);


private:
    QNetworkAccessManager *networkManager;


};


#endif // CHATCLIENT_H
