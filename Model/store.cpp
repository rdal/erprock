#include "store.h"

Store::Store(QString cnpj, QString stateNumber, QString name, QString fantasyName, QString phoneNumber,
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

Store::~Store()
{
    //fsd
}

//========= GETTERS ==========
QString Store::getCNPJ()
{
    return this->cnpj;
}

QString Store::getStateNumber()
{
    return this->stateNumber;
}

QString Store::getName()
{
    return this->name;
}

QString Store::getFantasyName()
{
    return this->fantasyName;
}

QString Store::getPhoneNumber()
{
    return this->phoneNumber;
}

QString Store::getFaxNumber()
{
    return this->faxNumber;
}

QString Store::getContactName()
{
    return this->contactName;
}

QString Store::getEmail()
{
    return this->email;
}

QString Store::getAddressStreet()
{
    return this->addressStreet;
}

int Store::getAddressNumber()
{
    return this->addressNumber;
}

QString Store::getAddressComplement()
{
    return this->addressComplement;
}

QString Store::getAddressSquare()
{
    return this->addressSquare;
}

QString Store::getAddressCity()
{
    return this->addressCity;
}

QString Store::getAddressState()
{
    return this->addressState;
}

QString Store::getAddressPostalCode()
{
    return this->addressPostalCode;
}

//========= SETTERS ==========
void Store::setCNPJ(QString cnpj)
{
    this->cnpj = cnpj;
}

void Store::setStateNumber(QString stateNumber)
{
    this->stateNumber = stateNumber;
}

void Store::setName(QString name)
{
    this->name = name;
}

void Store::setFantasyName(QString fantasyName)
{
    this->fantasyName = fantasyName;
}

void Store::setPhoneNumber(QString phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void Store::setFaxNumber(QString faxNumber)
{
    this->faxNumber = faxNumber;
}

void Store::setContactName(QString contactName)
{
    this->contactName = contactName;
}

void Store::setEmail(QString email)
{
    this->email = email;
}

void Store::setAddressStreet(QString addressStreet)
{
    this->addressStreet = addressStreet;
}

void Store::setAddressNumber(int addressNumber)
{
    this->addressNumber = addressNumber;
}

void Store::setAddressComplement(QString addressComplement)
{
    this->addressComplement = addressComplement;
}

void Store::setAddressSquare(QString addressSquare)
{
    this->addressSquare = addressSquare;
}

void Store::setAddressCity(QString addressCity)
{
    this->addressCity = addressCity;
}

void Store::setAddressState(QString addressState)
{
    this->addressState = addressState;
}

void Store::setAddressPostalCode(QString addressPostalCode)
{
    this->addressPostalCode = addressPostalCode;
}
