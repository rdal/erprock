#include "customercontroller.h"

CustomerController::CustomerController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

CustomerController::~CustomerController()
{
}

Utilities::StatusControl CustomerController::addCustomer(Customer *customer)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool isPhysicalCustomer = false;
        PhysicalCustomer* physicalCustomer = NULL;
        EnterpriseCustomer* enterpriseCustomer = dynamic_cast<EnterpriseCustomer*> (customer);
        if(!enterpriseCustomer)
        {
            physicalCustomer = dynamic_cast<PhysicalCustomer*> (customer);
            if(physicalCustomer)
            {
                isPhysicalCustomer = true;
            }
        }

        bool exists = false;
        bool isValidId = false;
        bool result = false;
        if(isPhysicalCustomer)
        {
            QString cpf = ((PhysicalCustomer*)customer)->getCpf();
            exists = dbController->physicalCustomerAlreadyExists(cpf);
            isValidId = Utilities::isCpfValid(cpf);
        }
        else
        {
            QString cnpj = ((EnterpriseCustomer*)customer)->getCnpj();
            exists = dbController->enterpriseCustomerAlreadyExists(cnpj);
            isValidId = Utilities::isCNPJValid(cnpj);
        }


        if(exists)
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else if(!isValidId)
        {
            ret = Utilities::INVALID_ID;
        }
        else
        {
            result = (isPhysicalCustomer) ? dbController->createNewPhysicalCustomer((PhysicalCustomer*)customer) :
                                            dbController->createNewEnterpriseCustomer((EnterpriseCustomer*)customer);
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

Utilities::StatusControl CustomerController::updateCustomer(Customer *customer)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool isPhysicalCustomer = false;
        PhysicalCustomer* physicalCustomer = NULL;
        EnterpriseCustomer* enterpriseCustomer = dynamic_cast<EnterpriseCustomer*> (customer);
        if(!enterpriseCustomer)
        {
            physicalCustomer = dynamic_cast<PhysicalCustomer*> (customer);
            if(physicalCustomer)
            {
                isPhysicalCustomer = true;
            }
        }

        bool exists = false;
        bool result = false;
        if(isPhysicalCustomer)
        {
            QString cpf = ((PhysicalCustomer*)customer)->getCpf();
            exists = dbController->physicalCustomerAlreadyExists(cpf);
        }
        else
        {
            QString cnpj = ((EnterpriseCustomer*)customer)->getCnpj();
            exists = dbController->enterpriseCustomerAlreadyExists(cnpj);
        }

        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else
        {
            result = (isPhysicalCustomer) ? dbController->updatePhysicalCustomer((PhysicalCustomer*)customer) :
                                            dbController->updateEnterpriseCustomer((EnterpriseCustomer*)customer);
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

Utilities::StatusControl CustomerController::removeCustomer(QString id)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool isPhysicalCustomer = false;
        if(id.count() == 11)
        {
            isPhysicalCustomer = true;
        }

        bool exists = false;
        bool result = false;
        if(isPhysicalCustomer)
        {
            exists = dbController->physicalCustomerAlreadyExists(id);
        }
        else
        {
            exists = dbController->enterpriseCustomerAlreadyExists(id);
        }


        if(!exists)
        {
            ret = Utilities::DOESNT_EXIST;
        }
        else
        {
            result = (isPhysicalCustomer) ? dbController->removePhysicalCustomer(id) :
                                            dbController->removeEnterpriseCustomer(id);
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

Customer *CustomerController::getCustomerById(QString id)
{
    Customer *customer = NULL;
    if(dbController->isConnectionOpen())
    {
        if(id.count() == 11)
        {
            customer = dbController->getPhysicalCustomerByCPF(id);
        }
        else
        {
            customer = dbController->getEnterpriseCustomerByCNPJ(id);
        }
    }
    return customer;
}

QList<PhysicalCustomer*> *CustomerController::getPhysicalCustomers()
{
    QList<PhysicalCustomer*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getPhysicalCustomers();
    }

    return ret;
}

QList<EnterpriseCustomer*> *CustomerController::getEnterpriseCustomers()
{
    QList<EnterpriseCustomer*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getEnterpriseCustomers();
    }

    return ret;
}
