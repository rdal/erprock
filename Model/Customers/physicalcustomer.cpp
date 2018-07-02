#include "physicalcustomer.h"

const QString PhysicalCustomer::DATE_FORMAT = "dd/MM/yyyy";

PhysicalCustomer::PhysicalCustomer(QString cpf, QString name, QDateTime birthdate, QString phoneNumber, QString email, QString addressStreet,
                                   int addressNumber, QString addressComplement, QString addressSquare, QString addressCity, QString addressState,
                                   QString addressPostalCode, QObject *parent) : Customer(name, phoneNumber, email, addressStreet, addressNumber,
                                                                                          addressComplement, addressSquare, addressCity, addressState,
                                                                                          addressPostalCode, parent)
{
    this->cpf = cpf;
    this->birthdate = birthdate;
}

PhysicalCustomer::~PhysicalCustomer()
{
}

QString PhysicalCustomer::getCpf()
{
    return this->cpf;
}

QDateTime PhysicalCustomer::getBirthDate()
{
    return this->birthdate;
}

void PhysicalCustomer::setCpf(QString cpf)
{
    this->cpf = cpf;
}

void PhysicalCustomer::setBirthDate(QDateTime birthDate)
{
    this->birthdate = birthDate;
}
