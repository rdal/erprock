#include "pricecontroller.h"
#include "product.h"
//#include "store.h"

PriceController::PriceController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

PriceController::~PriceController()
{
}

Utilities::StatusControl PriceController::addPrice(Price *price)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->priceAlreadyExists(price->getId(), price->getProductCode(), price->getStoreCnpj());
        bool existsName = dbController->priceNameAlreadyExists(price->getId(), price->getName());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else if(existsName)
        {
            ret = Utilities::ALREADY_EXISTS_NAME;
        }
        else
        {
            bool result = dbController->createNewPrice(price);
            if(!result)
            {
                ret = Utilities::UNKNOWN_ERROR;
            }
        }
    }
    else
    {
        ret = Utilities::DB_NOT_CONNECTED;
    }

    return ret;
}

Utilities::StatusControl PriceController::updatePrice(Price *price)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->priceAlreadyExists(price->getId(), price->getProductCode(), price->getStoreCnpj());
        bool existsName = dbController->priceNameAlreadyExists(price->getId(), price->getName());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else if(existsName)
        {
            ret = Utilities::ALREADY_EXISTS_NAME;
        }
        else
        {
            bool result = dbController->updatePrice(price);
            if(!result)
            {
                ret = Utilities::UNKNOWN_ERROR;
            }
        }
    }
    else
    {
        ret = Utilities::DB_NOT_CONNECTED;
    }
    return ret;
}

Utilities::StatusControl PriceController::removePrice(int id)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removePrice(id);
        if(!result)
        {
            ret = Utilities::UNKNOWN_ERROR;
        }
    }
    else
    {
        ret = Utilities::DB_NOT_CONNECTED;
    }
    return ret;
}

Price *PriceController::getPriceById(int id)
{
    Price *price = NULL;
    if(dbController->isConnectionOpen())
    {
        price = dbController->getPriceById(id);
    }
    return price;
}

Price *PriceController::getPriceByName(QString name)
{
    Price *price = NULL;
    if(dbController->isConnectionOpen())
    {
        price = dbController->getPriceByName(name);
    }
    return price;
}

Price *PriceController::getPriceByProductCode(QString productCode)
{
    Price *price = NULL;
    if(dbController->isConnectionOpen())
    {
        price = dbController->getPriceByProductCodeAndStoreCnpj(productCode, this->dbController->getDefaultStore()->getCNPJ());
    }
    return price;
}

QList<Price*> *PriceController::getPrices()
{
    QList<Price*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getPrices();
    }

    return ret;
}

QString PriceController::getProductName(QString productCode)
{
    QString ret;

    Product *p = dbController->getProductByCode(productCode);
    ret = p->getName();

    return ret;
}

QString PriceController::getStoreName(QString storeCnpj)
{
    QString ret;

    Store *s = dbController->getStoreByCNPJ(storeCnpj);
    ret = s->getName();

    return ret;
}
