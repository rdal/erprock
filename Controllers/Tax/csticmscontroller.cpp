#include "csticmscontroller.h"

CstIcmsController::CstIcmsController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

CstIcmsController::~CstIcmsController()
{
}

Utilities::StatusControl CstIcmsController::addCstIcms(CstIcms *cstIcms)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->cstIcmsAlreadyExists(cstIcms->getCode());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->createNewCstIcms(cstIcms);
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

Utilities::StatusControl CstIcmsController::updateCstIcms(QString code, CstIcms *cstIcms)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->cstIcmsAlreadyExists(cstIcms->getCode());
        if(exists && (code != cstIcms->getCode()))
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->updateCstIcms(code, cstIcms);
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

Utilities::StatusControl CstIcmsController::removeCstIcms(QString code)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeCstIcms(code);
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

CstIcms *CstIcmsController::getCstIcmsByCode(QString code)
{
    CstIcms *cstIcms = NULL;
    if(dbController->isConnectionOpen())
    {
        cstIcms = dbController->getCstIcmsByCode(code);
    }
    return cstIcms;
}

QList<CstIcms*> *CstIcmsController::getCstIcmss()
{
    QList<CstIcms*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getCstIcmss();
    }

    return ret;
}
