#include "cstipicontroller.h"

CstIpiController::CstIpiController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

CstIpiController::~CstIpiController()
{
}

Utilities::StatusControl CstIpiController::addCstIpi(CstIpi *cstIpi)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->cstIpiAlreadyExists(cstIpi->getCode());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->createNewCstIpi(cstIpi);
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

Utilities::StatusControl CstIpiController::updateCstIpi(QString code, CstIpi *cstIpi)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->cstIpiAlreadyExists(cstIpi->getCode());
        if(exists && (code != cstIpi->getCode()))
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool result = dbController->updateCstIpi(code, cstIpi);
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

Utilities::StatusControl CstIpiController::removeCstIpi(QString code)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeCstIpi(code);
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

CstIpi *CstIpiController::getCstIpiByCode(QString code)
{
    CstIpi *cstIpi = NULL;
    if(dbController->isConnectionOpen())
    {
        cstIpi = dbController->getCstIpiByCode(code);
    }
    return cstIpi;
}

QList<CstIpi*> *CstIpiController::getCstIpis()
{
    QList<CstIpi*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getCstIpis();
    }

    return ret;
}
