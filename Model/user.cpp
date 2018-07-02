#include "user.h"

User::User(QString cpf, UserRole role, QString name, QString password, QObject *parent) :
    QObject(parent)
{
    this->cpf = cpf;
    this->role = role;
    this->name = name;
    this->password = password;
}

User::~User()
{

}

QString User::getCpf()
{
    return this->cpf;
}

User::UserRole User::getRole()
{
    return this->role;
}

QString User::getName()
{
    return this->name;
}

QString User::getPassword()
{
    return this->password;
}

void User::setCpf(QString cpf)
{
    this->cpf = cpf;
}

void User::setRole(UserRole role)
{
    this->role = role;
}

void User::setName(QString name)
{
    this->name = name;
}

void User::setPassword(QString password)
{
    this->password = password;
}
