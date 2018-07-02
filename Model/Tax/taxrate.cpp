#include "taxrate.h"

TaxRate::TaxRate(QString name, double value, QObject *parent) :
    QObject(parent)
{
    this->name = name;
    this->value = value;
}

TaxRate::~TaxRate()
{
}

QString TaxRate::getName()
{
    return this->name;
}

double TaxRate::getValue()
{
    return this->value;
}

void TaxRate::setName(QString name)
{
    this->name = name;
}

void TaxRate::setValue(double value)
{
    this->value = value;
}
