#include "info.h"
#include<QVector>

info::info()
{



}
info::info(QString nam,QString user,QString pass,QString last,QString e, QString ge,QString a){
    name=nam;username=user;
    this->password=pass;this->lastname=last; this->email=e;this->gender=ge;this->age=a;

}
bool info::operator ==(const info &other){
    if(this->name==other.name&&this->username==other.username&&this->password==other.password&&this->age==other.age&&this->lastname==other.lastname&&this->gender==other.gender&&this->email==other.email){
        return 0;
    }
    return 1;
}
