#include "info.h"
#include<QVector>

info::info()
{



}
info::info(QString nam,QString user,QString pass,QString phone,QString e){
    name=nam;username=user;
    this->password=pass;this->phonenum=phone; this->email=e;

}
bool info::operator ==(const info &other){
    if(this->name==other.name&&this->username==other.username&&this->password==other.password&&this->phonenum==other.phonenum&&this->email==other.email){
        return 0;
    }
    return 1;
}
