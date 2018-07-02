#include "providercontroller.h"

ProviderController::ProviderController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

ProviderController::~ProviderController()
{
    //dbController = NULL;
}

Utilities::StatusControl ProviderController::addProvider(Provider *provider)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->providerAlreadyExists(provider->getCNPJ());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else if(!Utilities::isCNPJValid(provider->getCNPJ()))
        {
            ret = Utilities::INVALID_ID;
        }
        else
        {
            bool result = dbController->createNewProvider(provider);
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

Utilities::StatusControl ProviderController::updateProvider(Provider *provider)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->providerAlreadyExists(provider->getCNPJ());
        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else
        {
            bool result = dbController->updateProvider(provider);
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

Utilities::StatusControl ProviderController::removeProvider(QString cnpj)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->providerAlreadyExists(cnpj);
        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else
        {
            bool result = dbController->removeProvider(cnpj);
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

Provider *ProviderController::getProviderByCNPJ(QString cnpj)
{
    Provider *provider = NULL;
    if(dbController->isConnectionOpen())
    {
        provider = dbController->getProviderByCNPJ(cnpj);
    }
    return provider;
}

QList<Provider*> *ProviderController::getProviders()
{
    QList<Provider*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getProviders();
    }

    return ret;
}
