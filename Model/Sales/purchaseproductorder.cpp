#include "purchaseproductorder.h"

PurchaseProductOrder::PurchaseProductOrder(int id, QString productCode, int quantity, QChar productOriginCode, QString cstIcmsCode,
                                           QString cstIpiCode, QString cstPisCode, QString cstCofinsCode, double icmsValue,
                                           double ipiValue, double pisValue, double cofinsValue, QString cfopCode,
                                           double unitPrice, QString storeCnpj, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->productCode = productCode;
    this->quantity = quantity;
    this->productOriginCode = productOriginCode;
    this->cstIcmsCode = cstIcmsCode;
    this->cstIpiCode = cstIpiCode;
    this->cstPisCode = cstPisCode;
    this->cstCofinsCode = cstCofinsCode;
    this->icmsValue = icmsValue;
    this->ipiValue = ipiValue;
    this->pisValue = pisValue;
    this->cofinsValue = cofinsValue;
    this->cfopCode = cfopCode;
    this->unitPrice = unitPrice;
    this->storeCnpj = storeCnpj;
}

PurchaseProductOrder::PurchaseProductOrder(QString productCode, int quantity, QChar productOriginCode, QString cstIcmsCode,
                                           QString cstIpiCode, QString cstPisCode, QString cstCofinsCode, double icmsValue,
                                           double ipiValue, double pisValue, double cofinsValue,
                                           QString cfopCode, double unitPrice, QString storeCnpj, QObject *parent) :
    QObject(parent)
{
    this->id = 0;
    this->productCode = productCode;
    this->quantity = quantity;
    this->productOriginCode = productOriginCode;
    this->cstIcmsCode = cstIcmsCode;
    this->cstIpiCode = cstIpiCode;
    this->cstPisCode = cstPisCode;
    this->cstCofinsCode = cstCofinsCode;
    this->icmsValue = icmsValue;
    this->ipiValue = ipiValue;
    this->pisValue = pisValue;
    this->cofinsValue = cofinsValue;
    this->cfopCode = cfopCode;
    this->unitPrice = unitPrice;
    this->storeCnpj = storeCnpj;
}

int PurchaseProductOrder::getId()
{
    return this->id;
}

QString PurchaseProductOrder::getProductCode()
{
    return this->productCode;
}

int PurchaseProductOrder::getQuantity()
{
    return this->quantity;
}

QChar PurchaseProductOrder::getProductOriginCode()
{
    return this->productOriginCode;
}

QString PurchaseProductOrder::getCstIcmsCode()
{
    return this->cstIcmsCode;
}

QString PurchaseProductOrder::getCstIpiCode()
{
    return this->cstIpiCode;
}

QString PurchaseProductOrder::getCstPisCode()
{
    return this->cstPisCode;
}

QString PurchaseProductOrder::getCstCofinsCode()
{
    return this->cstCofinsCode;
}

double PurchaseProductOrder::getIcmsValue()
{
    return this->icmsValue;
}

double PurchaseProductOrder::getIpiValue()
{
    return this->ipiValue;
}

double PurchaseProductOrder::getPisValue()
{
    return this->pisValue;
}

double PurchaseProductOrder::getCofinsValue()
{
    return this->cofinsValue;
}

QString PurchaseProductOrder::getCfopCode()
{
    return this->cfopCode;
}

double PurchaseProductOrder::getUnitPrice()
{
    return this->unitPrice;
}

QString PurchaseProductOrder::getStoreCnpj()
{
    return this->storeCnpj;
}

void PurchaseProductOrder::setProductCode(QString productCode)
{
    this->productCode = productCode;
}

void PurchaseProductOrder::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void PurchaseProductOrder::setProductOriginCode(QChar productOriginCode)
{
    this->productOriginCode = productOriginCode;
}

void PurchaseProductOrder::setCstIcmsCode(QString cstIcmsCode)
{
    this->cstIcmsCode = cstIcmsCode;
}

void PurchaseProductOrder::setCstIpiCode(QString cstIpiCode)
{
    this->cstIpiCode = cstIpiCode;
}

void PurchaseProductOrder::setCstPisCode(QString cstPisCode)
{
    this->cstPisCode = cstPisCode;
}

void PurchaseProductOrder::setCstCofinsCode(QString cstCofinsCode)
{
    this->cstCofinsCode = cstCofinsCode;
}

void PurchaseProductOrder::setIcmsValue(double icmsValue)
{
    this->icmsValue = icmsValue;
}

void PurchaseProductOrder::setIpiValue(double ipiValue)
{
    this->ipiValue = ipiValue;
}

void PurchaseProductOrder::setPisValue(double pisValue)
{
    this->pisValue = pisValue;
}

void PurchaseProductOrder::setCofinsValue(double cofinsValue)
{
    this->cofinsValue = cofinsValue;
}

void PurchaseProductOrder::setCfopCode(QString cfopCode)
{
    this->cfopCode = cfopCode;
}

void PurchaseProductOrder::setUnitPrice(double unitPrice)
{
    this->unitPrice = unitPrice;
}

void PurchaseProductOrder::setStoreCnpj(QString storeCnpj)
{
    this->storeCnpj = storeCnpj;
}
