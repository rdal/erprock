#include "enterprisecustomer.h"

EnterpriseCustomer::EnterpriseCustomer(QString cnpj, QString stateNumber, QString name, QString fantasyName,
                                       QString phoneNumber, QString faxNumber, QString contactName, QString email,
                                       QString addressStreet, int addressNumber, QString addressComplement,
                                       QString addressSquare, QString addressCity, QString addressState,
                                       QString addressPostalCode, QObject *parent) : Customer(name, phoneNumber, email, addressStreet, addressNumber,
                                                                                              addressComplement, addressSquare, addressCity, addressState,
                                                                                              addressPostalCode, parent)
{
    this->cnpj = cnpj;
    this->stateNumber = stateNumber;
    this->fantasyName = fantasyName;
    this->faxNumber = faxNumber;
    this->contactName = contactName;
}

EnterpriseCustomer::~EnterpriseCustomer()
{
}

QString EnterpriseCustomer::getCnpj()
{
    return this->cnpj;
}

QString EnterpriseCustomer::getStateNumber()
{
    return this->stateNumber;
}

QString EnterpriseCustomer::getFantasyName()
{
    return this->fantasyName;
}

QString EnterpriseCustomer::getFaxNumber()
{
    return this->faxNumber;
}

QString EnterpriseCustomer::getContactName()
{
    return this->contactName;
}

void EnterpriseCustomer::setCnpj(QString cnpj)
{
    this->cnpj = cnpj;
}

void EnterpriseCustomer::setStateNumber(QString stateNumber)
{
    this->stateNumber = stateNumber;
}

void EnterpriseCustomer::setFantasyName(QString fantasyName)
{
    this->fantasyName = fantasyName;
}

void EnterpriseCustomer::setFaxNumber(QString faxNumber)
{
    this->faxNumber = faxNumber;
}

void EnterpriseCustomer::setContactName(QString contactName)
{
    this->contactName = contactName;
}

