#include "productcategory.h"

ProductCategory::ProductCategory(int id, QString name, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->name = name;
}

ProductCategory::ProductCategory(QString name, QObject *parent) :
    QObject(parent)
{
    this->id = 0;
    this->name = name;
}

ProductCategory::~ProductCategory()
{
}

int ProductCategory::getId()
{
    return this->id;
}

QString ProductCategory::getName()
{
    return this->name;
}

void ProductCategory::setId(int id)
{
    this->id = id;
}

void ProductCategory::setName(QString name)
{
    this->name = name;
}

