#include "price.h"

Price::Price(int id, QString productCode, double value, QString storeCnpj, QString name, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->productCode = productCode;
    this->value = value;
    this->storeCnpj = storeCnpj;
    this->name = name;
}

Price::Price(QString productCode, double value, QString storeCnpj, QString name, QObject *parent) :
    QObject(parent)
{
    this->id = 0;
    this->productCode = productCode;
    this->value = value;
    this->storeCnpj = storeCnpj;
    this->name = name;
}

int Price::getId()
{
    return this->id;
}

QString Price::getProductCode()
{
    return this->productCode;
}

QString Price::getStoreCnpj()
{
    return this->storeCnpj;
}

double Price::getValue()
{
    return this->value;
}

QString Price::getName()
{
    return this->name;
}

void Price::setProductCode(QString productCode)
{
    this->productCode = productCode;
}

void Price::setStoreCnpj(QString storeCnpj)
{
    this->storeCnpj = storeCnpj;
}

void Price::setValue(double value)
{
    this->value = value;
}

void Price::setName(QString name)
{
    this->name = name;
}
