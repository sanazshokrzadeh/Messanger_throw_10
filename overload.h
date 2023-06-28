#ifndef OVERLOAD_H
#define OVERLOAD_H

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

#endif // OVERLOAD_H
