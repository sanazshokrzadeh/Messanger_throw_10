#ifndef INFO_H
#define INFO_H
#include <QVector>
#include <QtCore>

class info
{
public:
    info();
QString name, username,password,phonenum,email;
    info(QString nam,QString user,QString pass,QString phone,QString e);
    bool operator ==(const info &other);


};

#endif // INFO_H
