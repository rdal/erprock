#include "csticms.h"

CstIcms::CstIcms(QString code, QString name, QObject *parent) :
    QObject(parent)
{
    this->code = code;
    this->name = name;
}

CstIcms::~CstIcms()
{
}

QString CstIcms::getCode()
{
    return this->code;
}

QString CstIcms::getName()
{
    return this->name;
}

void CstIcms::setCode(QString code)
{
    this->code = code;
}

void CstIcms::setName(QString name)
{
    this->name = name;
}
