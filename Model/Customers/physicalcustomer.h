#ifndef PHYSICALCUSTOMER_H
#define PHYSICALCUSTOMER_H

#include <QDateEdit>
#include "customer.h"

//!  PhysicalCustomer basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for PhysicalCustomer.
*/
class PhysicalCustomer : public Customer
{
public:

    //! Default constructor.
    /*!
    * Create a new instance of PhysicalCustomer.
    */
    explicit PhysicalCustomer(QString cpf, QString name, QDateTime birthdate, QString phoneNumber, QString email, QString addressStreet,
                              int addressNumber, QString addressComplement, QString addressSquare, QString addressCity, QString addressState,
                              QString addressPostalCode, QObject *parent=0);

    virtual ~PhysicalCustomer();

    //! Get physical customer's cpf.
    /*!
      Return the physical customer's cpf
      \return Returns the physical customer's cpf
      \sa setCpf()
    */
    QString getCpf();

    //! Get physical customer's birth date.
    /*!
      Return the physical customer's birth date
      \return Returns the physical customer's birth date
      \sa setBirthDate()
    */
    QDateTime getBirthDate();


    //! Set physical customer's cpf.
    /*!
      \param cpf Physical customer's cpf
      \sa getCpf()
    */
    void setCpf(QString cpf);

    //! Set physical customer's birth date.
    /*!
      \param birthDate Physical customer's birth date
      \sa getBirthDate()
    */
    void setBirthDate(QDateTime birthDate);

    /*!
    * This is a static member that tells the current birth date format.
    */
    static const QString DATE_FORMAT;

private:
    QString cpf;
    QDateTime birthdate;

};

#endif // PHYSICALCUSTOMER_H
