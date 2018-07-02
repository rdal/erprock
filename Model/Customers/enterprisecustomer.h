#ifndef ENTERPRISECUSTOMER_H
#define ENTERPRISECUSTOMER_H

#include "customer.h"

//!  EnterpriseCustomer basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for EnterpriseCustomer.
*/
class EnterpriseCustomer : public Customer
{
public:

    //! Default constructor.
    /*!
    * Create a new instance of EnterpriseCustomer.
    */
    explicit EnterpriseCustomer(QString cnpj, QString stateNumber, QString name, QString fantasyName,QString phoneNumber,
                                QString faxNumber, QString contactName, QString email, QString addressStreet,
                                int addressNumber, QString addressComplement, QString addressSquare, QString addressCity,
                                QString addressState, QString addressPostalCode, QObject *parent=0);

    virtual ~EnterpriseCustomer();

    //! Get enterprise customer's cnpj.
    /*!
      Return the enterprise customer's cnpj
      \return Returns the enterprise customer's cnpj
      \sa setCnpj()
    */
    QString getCnpj();

    //! Get enterprise customer's state number.
    /*!
      Return the enterprise customer's state number
      \return Returns the enterprise customer's state number
      \sa setStateNumber()
    */
    QString getStateNumber();

    //! Get enterprise customer's fantasy name.
    /*!
      Return the enterprise customer's fantasy name
      \return Returns the enterprise customer's fantasy name
      \sa setFantasyName()
    */
    QString getFantasyName();

    //! Get enterprise customer's fax number.
    /*!
      Return the enterprise customer's fax number
      \return Returns the enterprise customer's fax number
      \sa setFaxNumber()
    */
    QString getFaxNumber();

    //! Get enterprise customer's contact name.
    /*!
      Return the enterprise customer's contact name
      \return Returns the enterprise customer's contact name
      \sa setContactName()
    */
    QString getContactName();


    //! Set enterprise customer's cnpj.
    /*!
      \param cnpj Enterprise customer's cnpj
      \sa getCnpj()
    */
    void setCnpj(QString cnpj);

    //! Set enterprise customer's state number.
    /*!
      \param stateNumber Enterprise customer's state number
      \sa getStateNumber()
    */
    void setStateNumber(QString stateNumber);

    //! Set enterprise customer's fantasy name.
    /*!
      \param fantasyName Enterprise customer's fantasy name
      \sa getFantasyName()
    */
    void setFantasyName(QString fantasyName);

    //! Set enterprise customer's fax number.
    /*!
      \param faxNumber Enterprise customer's fax number
      \sa getFaxNumber()
    */
    void setFaxNumber(QString faxNumber);

    //! Set enterprise customer's contact name.
    /*!
      \param contactName Enterprise customer's contact name
      \sa getContactName()
    */
    void setContactName(QString contactName);

private:
    QString cnpj;
    QString stateNumber;
    QString fantasyName;
    QString faxNumber;
    QString contactName;
};

#endif // ENTERPRISECUSTOMER_H
