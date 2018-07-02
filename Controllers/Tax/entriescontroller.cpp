#include "entriescontroller.h"

EntriesController::EntriesController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

EntriesController::~EntriesController()
{
}

Utilities::StatusControl EntriesController::addEntry(Entry *entry)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->createNewEntry(entry);
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

Utilities::StatusControl EntriesController::updateEntry(Entry *entry)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->updateEntry(entry);
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

Utilities::StatusControl EntriesController::removeEntry(int id)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeEntry(id);
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

Entry *EntriesController::getEntryById(int id)
{
    Entry *entry = NULL;
    if(dbController->isConnectionOpen())
    {
        entry = dbController->getEntryById(id);
    }
    return entry;
}

QList<Entry*> *EntriesController::getEntriesBetweenDates(QDateTime startDate, QDateTime endDate)
{
    QList<Entry*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getEntriesBetweenDates(startDate, endDate);
    }

    return ret;
}

QList<Entry*> *EntriesController::getEntries()
{
    QList<Entry*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getEntries();
    }

    return ret;
}
