#include "usercontroller.h"

UserController::UserController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

UserController::~UserController()
{
    //dbController = NULL;
}

Utilities::StatusControl UserController::addUser(User *user)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->userAlreadyExists(user->getCpf());
        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else if(!Utilities::isCpfValid(user->getCpf()))
        {
            ret = Utilities::INVALID_ID;
        }
        else
        {
            bool result = dbController->createNewUser(user->getCpf(), user->getRole(), user->getName(), user->getPassword());
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

Utilities::StatusControl UserController::updateUser(User *user)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->userAlreadyExists(user->getCpf());
        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else
        {
            bool result = dbController->updateUser(user->getCpf(), user->getRole(), user->getName(), user->getPassword());
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

Utilities::StatusControl UserController::removeUser(QString cpf)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool exists = dbController->userAlreadyExists(cpf);
        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else
        {
            bool result = dbController->removeUser(cpf);
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

User *UserController::getUserByCPF(QString cpf)
{
    User *user = NULL;
    if(dbController->isConnectionOpen())
    {
        user = dbController->getUserByCPF(cpf);
    }
    return user;
}

QList<User*> *UserController::getUsers()
{
    QList<User*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getUsers();
    }

    return ret;
}

QString UserController::getUserRoleName(User::UserRole role)
{
    QString ret;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getUserRoleName(role);
    }

    return ret;
}

QStringList *UserController::getUsersRoles()
{
    QStringList *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getUsersRoles();
    }

    return ret;
}

bool UserController::validateLogin(QString cpf, QString password)
{
    bool ret = false;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->validateLogin(cpf, password);
    }

    return ret;
}
