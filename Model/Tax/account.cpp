#include "account.h"

Account::Account(QString code, QString name, AccountType type, bool reductive, QObject *parent) :
    QObject(parent)
{
    this->code = code;
    this->name = name;
    this->type = type;
    this->reductive = reductive;
}

QString Account::getCode()
{
    return this->code;
}

QString Account::getName()
{
    return this->name;
}

Account::AccountType Account::getType()
{
    return this->type;
}

bool Account::isReductive()
{
    return this->reductive;
}

void Account::setCode(QString code)
{
    this->code = code;
}

void Account::setName(QString name)
{
    this->name = name;
}

void Account::setType(AccountType type)
{
    this->type = type;
}

void Account::setReductive(bool reductive)
{
    this->reductive = reductive;
}
