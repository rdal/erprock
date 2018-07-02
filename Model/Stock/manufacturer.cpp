#include "manufacturer.h"

Manufacturer::Manufacturer(QString cnpj, QString stateNumber, QString name, QString fantasyName, QString phoneNumber,
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

Manufacturer::~Manufacturer()
{
    //fsd
}

//========= GETTERS ==========
QString Manufacturer::getCNPJ()
{
    return this->cnpj;
}

QString Manufacturer::getStateNumber()
{
    return this->stateNumber;
}

QString Manufacturer::getName()
{
    return this->name;
}

QString Manufacturer::getFantasyName()
{
    return this->fantasyName;
}

QString Manufacturer::getPhoneNumber()
{
    return this->phoneNumber;
}

QString Manufacturer::getFaxNumber()
{
    return this->faxNumber;
}

QString Manufacturer::getContactName()
{
    return this->contactName;
}

QString Manufacturer::getEmail()
{
    return this->email;
}

QString Manufacturer::getAddressStreet()
{
    return this->addressStreet;
}

int Manufacturer::getAddressNumber()
{
    return this->addressNumber;
}

QString Manufacturer::getAddressComplement()
{
    return this->addressComplement;
}

QString Manufacturer::getAddressSquare()
{
    return this->addressSquare;
}

QString Manufacturer::getAddressCity()
{
    return this->addressCity;
}

QString Manufacturer::getAddressState()
{
    return this->addressState;
}

QString Manufacturer::getAddressPostalCode()
{
    return this->addressPostalCode;
}

//========= SETTERS ==========
void Manufacturer::setCNPJ(QString cnpj)
{
    this->cnpj = cnpj;
}

void Manufacturer::setStateNumber(QString stateNumber)
{
    this->stateNumber = stateNumber;
}

void Manufacturer::setName(QString name)
{
    this->name = name;
}

void Manufacturer::setFantasyName(QString fantasyName)
{
    this->fantasyName = fantasyName;
}

void Manufacturer::setPhoneNumber(QString phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void Manufacturer::setFaxNumber(QString faxNumber)
{
    this->faxNumber = faxNumber;
}

void Manufacturer::setContactName(QString contactName)
{
    this->contactName = contactName;
}

void Manufacturer::setEmail(QString email)
{
    this->email = email;
}

void Manufacturer::setAddressStreet(QString addressStreet)
{
    this->addressStreet = addressStreet;
}

void Manufacturer::setAddressNumber(int addressNumber)
{
    this->addressNumber = addressNumber;
}

void Manufacturer::setAddressComplement(QString addressComplement)
{
    this->addressComplement = addressComplement;
}

void Manufacturer::setAddressSquare(QString addressSquare)
{
    this->addressSquare = addressSquare;
}

void Manufacturer::setAddressCity(QString addressCity)
{
    this->addressCity = addressCity;
}

void Manufacturer::setAddressState(QString addressState)
{
    this->addressState = addressState;
}

void Manufacturer::setAddressPostalCode(QString addressPostalCode)
{
    this->addressPostalCode = addressPostalCode;
}
