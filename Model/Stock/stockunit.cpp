#include "stockunit.h"

StockUnit::StockUnit(int id, QString name, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->name = name;
}

StockUnit::StockUnit(QString name, QObject *parent) :
    QObject(parent)
{
    this->id = 0;
    this->name = name;
}

StockUnit::~StockUnit()
{
}

int StockUnit::getId()
{
    return this->id;
}

QString StockUnit::getName()
{
    return this->name;
}

void StockUnit::setId(int id)
{
    this->id = id;
}

void StockUnit::setName(QString name)
{
    this->name = name;
}
