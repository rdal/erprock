#include "cstpiscontroller.h"

CstPisController::CstPisController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

CstPisController::~CstPisController()
{
}

Utilities::StatusControl CstPisController::addCstPis(CstPis *cstPis)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->cstPisAlreadyExists(cstPis->getCode());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->createNewCstPis(cstPis);
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

Utilities::StatusControl CstPisController::updateCstPis(QString code, CstPis *cstPis)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->cstPisAlreadyExists(cstPis->getCode());
        if(exists && (code != cstPis->getCode()))
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->updateCstPis(code, cstPis);
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

Utilities::StatusControl CstPisController::removeCstPis(QString code)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeCstPis(code);
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

CstPis *CstPisController::getCstPisByCode(QString code)
{
    CstPis *cstPis = NULL;
    if(dbController->isConnectionOpen())
    {
        cstPis = dbController->getCstPisByCode(code);
    }
    return cstPis;
}

QList<CstPis*> *CstPisController::getCstPiss()
{
    QList<CstPis*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getCstPiss();
    }

    return ret;
}
