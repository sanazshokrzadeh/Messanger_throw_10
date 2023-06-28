#include "tokenuser.h"

tokenuser::tokenuser()
{

}

tokenuser::tokenuser(QString user, QString tok)
{
    username=user;token=tok;
}

QString tokenuser::getToken()
{
    return this->token;
}

QString tokenuser::getUsername()
{
    return this->username;
}
