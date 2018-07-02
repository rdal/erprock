#include "historiescontroller.h"

HistoriesController::HistoriesController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

Utilities::StatusControl HistoriesController::addHistory(History *history)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->historyAlreadyExists(history->getName());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->createNewHistory(history);
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

Utilities::StatusControl HistoriesController::updateHistory(History *history)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->historyAlreadyExists(history->getName());
        if(exists) //&& (name != history->getName()))
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->updateHistory(history);
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

Utilities::StatusControl HistoriesController::removeHistory(int id)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeHistory(id);
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

History *HistoriesController::getHistoryById(int id)
{
    History *history = NULL;
    if(dbController->isConnectionOpen())
    {
        history = dbController->getHistoryById(id);
    }
    return history;
}

QList<History*> *HistoriesController::getHistories()
{
    QList<History*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getHistories();
    }

    return ret;
}
