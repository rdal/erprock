#include "customer.h"

Customer::Customer(QString name, QString phoneNumber, QString email, QString addressStreet, int addressNumber,
                   QString addressComplement, QString addressSquare, QString addressCity, QString addressState,
                   QString addressPostalCode, QObject *parent) : QObject(parent)
{
    this->name = name;
    this->phoneNumber = phoneNumber;
    this->email = email;
    this->addressStreet = addressStreet;
    this->addressNumber = addressNumber;
    this->addressComplement = addressComplement;
    this->addressSquare = addressSquare;
    this->addressCity = addressCity;
    this->addressState = addressState;
    this->addressPostalCode = addressPostalCode;
}

Customer::~Customer()
{
}

QString Customer::getName()
{
    return this->name;
}

QString Customer::getPhoneNumber()
{
    return this->phoneNumber;
}

QString Customer::getEmail()
{
    return this->email;
}

QString Customer::getAddressStreet()
{
    return this->addressStreet;
}

int Customer::getAddressNumber()
{
    return this->addressNumber;
}

QString Customer::getAddressComplement()
{
    return this->addressComplement;
}

QString Customer::getAddressSquare()
{
    return this->addressSquare;
}

QString Customer::getAddressCity()
{
    return this->addressCity;
}

QString Customer::getAddressState()
{
    return this->addressState;
}

QString Customer::getAddressPostalCode()
{
    return this->addressPostalCode;
}

void Customer::setName(QString name)
{
    this->name = name;
}

void Customer::setPhoneNumber(QString phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void Customer::setEmail(QString email)
{
    this->email = email;
}

void Customer::setAddressStreet(QString addressStreet)
{
    this->addressStreet = addressStreet;
}

void Customer::setAddressNumber(int addressNumber)
{
    this->addressNumber = addressNumber;
}

void Customer::setAddressComplement(QString addressComplement)
{
    this->addressComplement = addressComplement;
}

void Customer::setAddressSquare(QString addressSquare)
{
    this->addressSquare = addressSquare;
}

void Customer::setAddressCity(QString addressCity)
{
    this->addressCity = addressCity;
}

void Customer::setAddressState(QString addressState)
{
    this->addressState = addressState;
}

void Customer::setAddressPostalCode(QString addressPostalCode)
{
    this->addressPostalCode = addressPostalCode;
}
