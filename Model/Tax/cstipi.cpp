#include "cstipi.h"

CstIpi::CstIpi(QString code, QString name, QObject *parent) :
    QObject(parent)
{
    this->code = code;
    this->name = name;
}

CstIpi::~CstIpi()
{
}

QString CstIpi::getCode()
{
    return this->code;
}

QString CstIpi::getName()
{
    return this->name;
}

void CstIpi::setCode(QString code)
{
    this->code = code;
}

void CstIpi::setName(QString name)
{
    this->name = name;
}
