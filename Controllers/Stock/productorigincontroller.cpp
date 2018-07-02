#include "productorigincontroller.h"

ProductOriginController::ProductOriginController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

ProductOriginController::~ProductOriginController()
{
}

Utilities::StatusControl ProductOriginController::addProductOrigin(ProductOrigin *productOrigin)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->productOriginAlreadyExists(productOrigin->getCode());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->createNewProductOrigin(productOrigin);
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

Utilities::StatusControl ProductOriginController::updateProductOrigin(QString code, ProductOrigin *productOrigin)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->updateProductOrigin(code, productOrigin);
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

Utilities::StatusControl ProductOriginController::removeProductOrigin(QString code)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeProductOrigin(code);
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

ProductOrigin *ProductOriginController::getProductOriginByCode(QString code)
{
    ProductOrigin *productOrigin = NULL;
    if(dbController->isConnectionOpen())
    {
        productOrigin = dbController->getProductOriginByCode(code);
    }
    return productOrigin;
}

QList<ProductOrigin*> *ProductOriginController::getProductOrigins()
{
    QList<ProductOrigin*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getProductOrigins();
    }

    return ret;
}
