#include "taxratecontroller.h"

TaxRateController::TaxRateController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

TaxRateController::~TaxRateController()
{
}

Utilities::StatusControl TaxRateController::addTaxRate(TaxRate *taxRate)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->taxRateAlreadyExists(taxRate->getName());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->createNewTaxRate(taxRate);
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

Utilities::StatusControl TaxRateController::updateTaxRate(QString name, TaxRate *taxRate)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->taxRateAlreadyExists(taxRate->getName());
        if(exists && (name != taxRate->getName()))
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->updateTaxRate(name, taxRate);
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

Utilities::StatusControl TaxRateController::removeTaxRate(QString name)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeTaxRate(name);
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

TaxRate *TaxRateController::getTaxRateByName(QString name)
{
    TaxRate *taxRate = NULL;
    if(dbController->isConnectionOpen())
    {
        taxRate = dbController->getTaxRateByName(name);
    }
    return taxRate;
}

QList<TaxRate*> *TaxRateController::getTaxRates()
{
    QList<TaxRate*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getTaxRates();
    }

    return ret;
}
