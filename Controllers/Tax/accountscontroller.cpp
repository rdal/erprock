#include "accountscontroller.h"

AccountsController::AccountsController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

AccountsController::~AccountsController()
{
    //dbController = NULL;
}

Utilities::StatusControl AccountsController::addAccount(Account *account)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->accountAlreadyExists(account->getCode());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool isAnalytic = false;
            if(account->getCode().length() == 9)
            {
                isAnalytic = true;
            }

            bool result = dbController->createNewAccount(account, isAnalytic);
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

Utilities::StatusControl AccountsController::updateAccount(QString code, Account *account)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->accountAlreadyExists(account->getCode());
        if(exists && (code != account->getCode()))
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else
        {
            bool isAnalytic = false;
            if(account->getCode().length() == 9)
            {
                isAnalytic = true;
            }

            bool result = dbController->updateAccount(code, account, isAnalytic);
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

Utilities::StatusControl AccountsController::removeAccount(QString code)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->accountAlreadyExists(code);
        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else
        {
            bool result = dbController->removeAccount(code);
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

Account *AccountsController::getAccountByCode(QString code)
{
    Account *account = NULL;
    if(dbController->isConnectionOpen())
    {
        account = dbController->getAccountByCode(code);
    }
    return account;
}

QList<Account*> *AccountsController::getAccounts()
{
    QList<Account*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getAccounts();
    }

    return ret;
}

QList<Account*> *AccountsController::getAnalyticAccounts()
{
    QList<Account*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getAccounts("WHERE length(code) = 9");
    }

    return ret;
}

QList<Account*> *AccountsController::getSyntheticAccounts()
{
    QList<Account*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getAccounts("WHERE length(code) < 9");
    }

    return ret;
}

QStringList *AccountsController::getAccountTypes()
{
    QStringList *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getAccountTypes();
    }

    return ret;
}
