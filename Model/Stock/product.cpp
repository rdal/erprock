#include "product.h"

Product::Product(QString code, QString barCode, int productCategoryId, QString manufacturerCnpj,
                 QString name, QString description, QString cstIcms, QString cstIpi,
                 QString cstPis, QString cstCofins, QString icmsPercentName, QString ipiPercentName,
                 QString pisPercentName, QString cofinsPercentName, QString cfopCode, QObject *parent) :
    QObject(parent)
{
    this->code = code;
    this->barCode = barCode;
    this->productCategoryId = productCategoryId;
    this->manufacturerCnpj = manufacturerCnpj;
    this->name = name;
    this->description = description;
    this->cstIcms = cstIcms;
    this->cstIpi = cstIpi;
    this->cstPis = cstPis;
    this->cstCofins = cstCofins;
    this->icmsPercentName = icmsPercentName;
    this->ipiPercentName = ipiPercentName;
    this->pisPercentName = pisPercentName;
    this->cofinsPercentName = cofinsPercentName;
    this->cfopCode = cfopCode;
}

Product::~Product()
{
}

QString Product::getCode()
{
    return this->code;
}

QString Product::getBarCode()
{
    return this->barCode;
}

int Product::getProductCategoryId()
{
    return this->productCategoryId;
}

QString Product::getManufacturerCnpj()
{
    return this->manufacturerCnpj;
}

QString Product::getName()
{
    return this->name;
}

QString Product::getDescription()
{
    return this->description;
}

QString Product::getCstIcms()
{
    return this->cstIcms;
}

QString Product::getCstIpi()
{
    return this->cstIpi;
}

QString Product::getCstPis()
{
    return this->cstPis;
}

QString Product::getCstCofins()
{
    return this->cstCofins;
}

QString Product::getIcmsPercentName()
{
    return this->icmsPercentName;
}

QString Product::getIpiPercentName()
{
    return this->ipiPercentName;
}

QString Product::getPisPercentName()
{
    return this->pisPercentName;
}

QString Product::getCofinsPercentName()
{
    return this->cofinsPercentName;
}

QString Product::getCfopCode()
{
    return this->cfopCode;
}

void Product::setCode(QString code)
{
    this->code = code;
}

void Product::setBarCode(QString barCode)
{
    this->barCode = barCode;
}

void Product::setProductCategoryId(int productCategoryId)
{
    this->productCategoryId = productCategoryId;
}

void Product::setManufacturerCnpj(QString manufacturerCnpj)
{
    this->manufacturerCnpj = manufacturerCnpj;
}

void Product::setName(QString name)
{
    this->name = name;
}

void Product::setDescription(QString description)
{
    this->description = description;
}

void Product::setCstIcms(QString cstIcms)
{
    this->cstIcms = cstIcms;
}

void Product::setCstIpi(QString cstIpi)
{
    this->cstIpi = cstIpi;
}

void Product::setCstPis(QString cstPis)
{
    this->cstPis = cstPis;
}

void Product::setCstCofins(QString cstCofins)
{
    this->cstCofins = cstCofins;
}

void Product::setIcmsPercentName(QString icmsPercentName)
{
    this->icmsPercentName = icmsPercentName;
}

void Product::setIpiPercentName(QString ipiPercentName)
{
    this->ipiPercentName = ipiPercentName;
}

void Product::setPisPercentName(QString pisPercentName)
{
    this->pisPercentName = pisPercentName;
}

void Product::setCofinsPercentName(QString cofinsPercentName)
{
    this->cofinsPercentName = cofinsPercentName;
}

void Product::setCfopCode(QString cfopCode)
{
    this->cfopCode = cfopCode;
}
