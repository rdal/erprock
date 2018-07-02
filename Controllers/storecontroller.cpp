#include "storecontroller.h"

StoreController::StoreController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

StoreController::~StoreController()
{
    //dbController = NULL;
}

Utilities::StatusControl StoreController::addStore(Store *store)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->storeAlreadyExists(store->getCNPJ());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else if(!Utilities::isCNPJValid(store->getCNPJ()))
        {
            ret = Utilities::INVALID_ID;
        }
        else
        {
            bool result = dbController->createNewStore(store);
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

Utilities::StatusControl StoreController::updateStore(Store *store)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->storeAlreadyExists(store->getCNPJ());
        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else
        {
            bool result = dbController->updateStore(store);
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

Utilities::StatusControl StoreController::removeStore(QString cnpj)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->storeAlreadyExists(cnpj);
        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else if(dbController->getDefaultStore()->getCNPJ() == cnpj)
        {
            ret = Utilities::ACTION_FORBIDDEN;
        }
        else
        {
            bool result = dbController->removeStore(cnpj);
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

Store *StoreController::getStoreByCNPJ(QString cnpj)
{
    Store *store = NULL;
    if(dbController->isConnectionOpen())
    {
        store = dbController->getStoreByCNPJ(cnpj);
    }
    return store;
}

QList<Store*> *StoreController::getStores()
{
    QList<Store*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getStores();
    }

    return ret;
}
