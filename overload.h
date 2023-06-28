#ifndef OVERLOAD_H
#define OVERLOAD_H

#include "tokenuser.h"
#include <QtCore>
#include <info.h>

QDataStream  &operator << (QDataStream  &out , const info  &p);

QDataStream  &operator >> (QDataStream  &in  ,  info  &p);



QDataStream  &operator << (QDataStream  &out , const info  &p)
{  out<<p.name<<p.last<<p.username<<p.email<<p.password;

    return out;
}

QDataStream  &operator >> (QDataStream  &in  , info  &p)
{
    in>>p.name>>p.last>>p.username>>p.email>>p.password;
    return in;
}
QDataStream  &operator << (QDataStream  &out , tokenuser  &p)
{  out<<p.getUsername()<<p.getToken();

    return out;
}

QDataStream  &operator >> (QDataStream  &in  ,tokenuser&  p)
{QString u,t;
    in>>u>>t;
    p=tokenuser(u,t);
    return in;
}

#endif // OVERLOAD_H
