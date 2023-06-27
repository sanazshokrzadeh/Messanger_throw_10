#ifndef OVERLOAD_H
#define OVERLOAD_H

#include <QtCore>
#include <info.h>

QDataStream  &operator << (QDataStream  &out , const info  &p);

QDataStream  &operator >> (QDataStream  &in  ,  info  &p);



QDataStream  &operator << (QDataStream  &out , const info  &p)
{  out<<p.name<<p.lastname<<p.username<<p.age<<p.email<<p.gender<<p.password;

    return out;
}

QDataStream  &operator >> (QDataStream  &in  , info  &p)
{
    in>>p.name>>p.lastname>>p.username>>p.age>>p.email>>p.gender>>p.password;
    return in;
}

#endif // OVERLOAD_H
