#include "productorigin.h"

ProductOrigin::ProductOrigin(QString code, QString name, QObject *parent) :
    QObject(parent)
{
    this->code = code;
    this->name = name;
}

ProductOrigin::~ProductOrigin()
{
}

QString ProductOrigin::getCode()
{
    return this->code;
}

QString ProductOrigin::getName()
{
    return this->name;
}

void ProductOrigin::setCode(QString code)
{
    this->code = code;
}

void ProductOrigin::setName(QString name)
{
    this->name = name;
}
