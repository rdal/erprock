#include "saleproductorder.h"

SaleProductOrder::SaleProductOrder(int id, QString productCode, int quantity, QString cstIcmsCode, QString cstIpiCode,
                                   QString cstPisCode, QString cstCofinsCode, QString icmsPercentName, QString ipiPercentName,
                                   QString pisPercentName, QString cofinsPercentName, QString cfopCode, QString storeCnpj,
                                   double value, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->productCode = productCode;
    this->quantity = quantity;
    this->cstIcmsCode = cstIcmsCode;
    this->cstIpiCode = cstIpiCode;
    this->cstPisCode = cstPisCode;
    this->cstCofinsCode = cstCofinsCode;
    this->icmsPercentName = icmsPercentName;
    this->ipiPercentName = ipiPercentName;
    this->pisPercentName = pisPercentName;
    this->cofinsPercentName = cofinsPercentName;
    this->cfopCode = cfopCode;
    //this->priceId = priceId;
    this->storeCnpj = storeCnpj;
    this->value = value;
}

SaleProductOrder::SaleProductOrder(QString productCode, int quantity, QString cstIcmsCode, QString cstIpiCode, QString cstPisCode,
                                   QString cstCofinsCode, QString icmsPercentName, QString ipiPercentName, QString pisPercentName,
                                   QString cofinsPercentName, QString cfopCode, QString storeCnpj, double value, QObject *parent) :
    QObject(parent)
{
    this->id = 0;
    this->productCode = productCode;
    this->quantity = quantity;
    this->cstIcmsCode = cstIcmsCode;
    this->cstIpiCode = cstIpiCode;
    this->cstPisCode = cstPisCode;
    this->cstCofinsCode = cstCofinsCode;
    this->icmsPercentName = icmsPercentName;
    this->ipiPercentName = ipiPercentName;
    this->pisPercentName = pisPercentName;
    this->cofinsPercentName = cofinsPercentName;
    this->cfopCode = cfopCode;
    //this->priceId = priceId;
    this->storeCnpj = storeCnpj;
    this->value = value;
}

int SaleProductOrder::getId()
{
    return this->id;
}

QString SaleProductOrder::getProductCode()
{
    return this->productCode;
}

int SaleProductOrder::getQuantity()
{
    return this->quantity;
}

QString SaleProductOrder::getCstIcmsCode()
{
    return this->cstIcmsCode;
}

QString SaleProductOrder::getCstIpiCode()
{
    return this->cstIpiCode;
}

QString SaleProductOrder::getCstPisCode()
{
    return this->cstPisCode;
}

QString SaleProductOrder::getCstCofinsCode()
{
    return this->cstCofinsCode;
}

QString SaleProductOrder::getIcmsPercentName()
{
    return this->icmsPercentName;
}

QString SaleProductOrder::getIpiPercentName()
{
    return this->ipiPercentName;
}

QString SaleProductOrder::getPisPercentName()
{
    return this->pisPercentName;
}

QString SaleProductOrder::getCofinsPercentName()
{
    return this->cofinsPercentName;
}

QString SaleProductOrder::getCfopCode()
{
    return this->cfopCode;
}

//int SaleProductOrder::getPriceId()
//{
//    return priceId;
//}

QString SaleProductOrder::getStoreCnpj()
{
    return this->storeCnpj;
}

double SaleProductOrder::getValue()
{
    return this->value;
}

void SaleProductOrder::setProductCode(QString productCode)
{
    this->productCode = productCode;
}

void SaleProductOrder::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void SaleProductOrder::setCstIcmsCode(QString cstIcmsCode)
{
    this->cstIcmsCode = cstIcmsCode;
}

void SaleProductOrder::setCstIpiCode(QString cstIpiCode)
{
    this->cstIpiCode = cstIpiCode;
}

void SaleProductOrder::setCstPisCode(QString cstPisCode)
{
    this->cstPisCode = cstPisCode;
}

void SaleProductOrder::setCstCofinsCode(QString cstCofinsCode)
{
    this->cstCofinsCode = cstCofinsCode;
}

void SaleProductOrder::setIcmsPercentName(QString icmsPercentName)
{
    this->icmsPercentName = icmsPercentName;
}

void SaleProductOrder::setIpiPercentName(QString ipiPercentName)
{
    this->ipiPercentName = ipiPercentName;
}

void SaleProductOrder::setPisPercentName(QString pisPercentName)
{
    this->pisPercentName = pisPercentName;
}

void SaleProductOrder::setCofinsPercentName(QString cofinsPercentName)
{
    this->cofinsPercentName = cofinsPercentName;
}

void SaleProductOrder::setCfopCode(QString cfopCode)
{
    this->cfopCode = cfopCode;
}

//void SaleProductOrder::setPriceId(int priceId)
//{
//    this->priceId = priceId;
//}

void SaleProductOrder::setStoreCnpj(QString storeCnpj)
{
    this->storeCnpj = storeCnpj;
}

void SaleProductOrder::setValue(double value)
{
    this->value = value;
}
