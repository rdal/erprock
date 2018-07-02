#include "manufacturercontroller.h"

ManufacturerController::ManufacturerController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

ManufacturerController::~ManufacturerController()
{
    //dbController = NULL;
}

Utilities::StatusControl ManufacturerController::addManufacturer(Manufacturer *manufacturer)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->manufacturerAlreadyExists(manufacturer->getCNPJ());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else if(!Utilities::isCNPJValid(manufacturer->getCNPJ()))
        {
            ret = Utilities::INVALID_ID;
        }
        else
        {
            bool result = dbController->createNewManufacturer(manufacturer);
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

Utilities::StatusControl ManufacturerController::updateManufacturer(Manufacturer *manufacturer)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->manufacturerAlreadyExists(manufacturer->getCNPJ());
        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else
        {
            bool result = dbController->updateManufacturer(manufacturer);
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

Utilities::StatusControl ManufacturerController::removeManufacturer(QString cnpj)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->manufacturerAlreadyExists(cnpj);
        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else
        {
            bool result = dbController->removeManufacturer(cnpj);
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

Manufacturer *ManufacturerController::getManufacturerByCNPJ(QString cnpj)
{
    Manufacturer *manufacturer = NULL;
    if(dbController->isConnectionOpen())
    {
        manufacturer = dbController->getManufacturerByCNPJ(cnpj);
    }
    return manufacturer;
}

QList<Manufacturer*> *ManufacturerController::getManufacturers()
{
    QList<Manufacturer*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getManufacturers();
    }

    return ret;
}
