#include "info.h"
#include<QVector>

info::info()
{



}
info::info(QString nam,QString user,QString pass,QString last,QString e){
    name=nam;username=user;
    this->password=pass;this->last=last; this->email=e;

}
bool info::operator ==(const info &other){
    if(this->name==other.name&&this->username==other.username&&this->password==other.password&&this->last==other.last&&this->email==other.email){
        return 0;
    }
    return 1;
}
