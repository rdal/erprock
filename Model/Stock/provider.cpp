#include "provider.h"

Provider::Provider(QString cnpj, QString stateNumber, QString name, QString fantasyName, QString phoneNumber,
                   QString faxNumber, QString contactName, QString email, QString addressStreet,
                   int addressNumber, QString addressComplement, QString addressSquare, QString addressCity,
                   QString addressState, QString addressPostalCode, QObject *parent) :
    QObject(parent)
{
    this->cnpj = cnpj;
    this->stateNumber = stateNumber;
    this->name = name;
    this->fantasyName = fantasyName;
    this->phoneNumber = phoneNumber;
    this->faxNumber = faxNumber;
    this->contactName = contactName;
    this->email = email;
    this->addressStreet = addressStreet;
    this->addressNumber = addressNumber;
    this->addressComplement = addressComplement;
    this->addressSquare = addressSquare;
    this->addressCity = addressCity;
    this->addressState = addressState;
    this->addressPostalCode = addressPostalCode;
}

Provider::~Provider()
{
    //fsd
}

//========= GETTERS ==========
QString Provider::getCNPJ()
{
    return this->cnpj;
}

QString Provider::getStateNumber()
{
    return this->stateNumber;
}

QString Provider::getName()
{
    return this->name;
}

QString Provider::getFantasyName()
{
    return this->fantasyName;
}

QString Provider::getPhoneNumber()
{
    return this->phoneNumber;
}

QString Provider::getFaxNumber()
{
    return this->faxNumber;
}

QString Provider::getContactName()
{
    return this->contactName;
}

QString Provider::getEmail()
{
    return this->email;
}

QString Provider::getAddressStreet()
{
    return this->addressStreet;
}

int Provider::getAddressNumber()
{
    return this->addressNumber;
}

QString Provider::getAddressComplement()
{
    return this->addressComplement;
}

QString Provider::getAddressSquare()
{
    return this->addressSquare;
}

QString Provider::getAddressCity()
{
    return this->addressCity;
}

QString Provider::getAddressState()
{
    return this->addressState;
}

QString Provider::getAddressPostalCode()
{
    return this->addressPostalCode;
}

//========= SETTERS ==========
void Provider::setCNPJ(QString cnpj)
{
    this->cnpj = cnpj;
}

void Provider::setStateNumber(QString stateNumber)
{
    this->stateNumber = stateNumber;
}

void Provider::setName(QString name)
{
    this->name = name;
}

void Provider::setFantasyName(QString fantasyName)
{
    this->fantasyName = fantasyName;
}

void Provider::setPhoneNumber(QString phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void Provider::setFaxNumber(QString faxNumber)
{
    this->faxNumber = faxNumber;
}

void Provider::setContactName(QString contactName)
{
    this->contactName = contactName;
}

void Provider::setEmail(QString email)
{
    this->email = email;
}

void Provider::setAddressStreet(QString addressStreet)
{
    this->addressStreet = addressStreet;
}

void Provider::setAddressNumber(int addressNumber)
{
    this->addressNumber = addressNumber;
}

void Provider::setAddressComplement(QString addressComplement)
{
    this->addressComplement = addressComplement;
}

void Provider::setAddressSquare(QString addressSquare)
{
    this->addressSquare = addressSquare;
}

void Provider::setAddressCity(QString addressCity)
{
    this->addressCity = addressCity;
}

void Provider::setAddressState(QString addressState)
{
    this->addressState = addressState;
}

void Provider::setAddressPostalCode(QString addressPostalCode)
{
    this->addressPostalCode = addressPostalCode;
}
