#include "stockunitcontroller.h"

StockUnitController::StockUnitController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

StockUnitController::~StockUnitController()
{
}

Utilities::StatusControl StockUnitController::addStockUnit(StockUnit *stockUnit)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->stockUnitAlreadyExists(stockUnit->getName());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->createNewStockUnit(stockUnit);
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

Utilities::StatusControl StockUnitController::updateStockUnit(StockUnit *stockUnit)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->updateStockUnit(stockUnit);
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

Utilities::StatusControl StockUnitController::removeStockUnit(int id)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeStockUnit(id);
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

StockUnit *StockUnitController::getStockUnitById(int id)
{
    StockUnit *stockUnit = NULL;
    if(dbController->isConnectionOpen())
    {
        stockUnit = dbController->getStockUnitById(id);
    }
    return stockUnit;
}

QList<StockUnit*> *StockUnitController::getStockUnits()
{
    QList<StockUnit*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getStockUnits();
    }

    return ret;
}
