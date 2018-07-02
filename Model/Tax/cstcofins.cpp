#include "cstcofins.h"

CstCofins::CstCofins(QString code, QString name, QObject *parent) :
    QObject(parent)
{
    this->code = code;
    this->name = name;
}

CstCofins::~CstCofins()
{
}

QString CstCofins::getCode()
{
    return this->code;
}

QString CstCofins::getName()
{
    return this->name;
}

void CstCofins::setCode(QString code)
{
    this->code = code;
}

void CstCofins::setName(QString name)
{
    this->name = name;
}
