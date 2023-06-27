#ifndef INFO_H
#define INFO_H
#include <QVector>
#include <QtCore>

class info
{
public:
    info();
QString name, username,password,lastname,email,gender,age;
    info(QString nam,QString user,QString pass,QString last,QString e, QString ge,QString a);
    bool operator ==(const info &other);


};

#endif // INFO_H
