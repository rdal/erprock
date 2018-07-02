#include "cstcofinscontroller.h"

CstCofinsController::CstCofinsController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

CstCofinsController::~CstCofinsController()
{
}

Utilities::StatusControl CstCofinsController::addCstCofins(CstCofins *cstCofins)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->cstCofinsAlreadyExists(cstCofins->getCode());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->createNewCstCofins(cstCofins);
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

Utilities::StatusControl CstCofinsController::updateCstCofins(QString code, CstCofins *cstCofins)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->cstCofinsAlreadyExists(cstCofins->getCode());
        if(exists && (code != cstCofins->getCode()))
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->updateCstCofins(code, cstCofins);
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

Utilities::StatusControl CstCofinsController::removeCstCofins(QString code)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeCstCofins(code);
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

CstCofins *CstCofinsController::getCstCofinsByCode(QString code)
{
    CstCofins *cstCofins = NULL;
    if(dbController->isConnectionOpen())
    {
        cstCofins = dbController->getCstCofinsByCode(code);
    }
    return cstCofins;
}

QList<CstCofins*> *CstCofinsController::getCstCofinss()
{
    QList<CstCofins*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getCstCofinss();
    }

    return ret;
}
