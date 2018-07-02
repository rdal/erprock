#include "cstpis.h"

CstPis::CstPis(QString code, QString name, QObject *parent) :
    QObject(parent)
{
    this->code = code;
    this->name = name;
}

CstPis::~CstPis()
{
}

QString CstPis::getCode()
{
    return this->code;
}

QString CstPis::getName()
{
    return this->name;
}

void CstPis::setCode(QString code)
{
    this->code = code;
}

void CstPis::setName(QString name)
{
    this->name = name;
}
