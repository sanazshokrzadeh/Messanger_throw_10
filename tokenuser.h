#ifndef TOKENUSER_H
#define TOKENUSER_H

#include<QString>
class tokenuser
{
public:
    tokenuser();tokenuser(QString user,QString tok);
    QString getToken();
    QString getUsername();
private:
    QString token,username;
};

#endif // TOKENUSER_H
