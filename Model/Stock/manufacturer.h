#ifndef MANUFACTURER_H
#define MANUFACTURER_H

#include <QObject>

//!  User basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Manufacturer.
*/
class Manufacturer : public QObject
{
    Q_OBJECT
public:
    //! Default constructor.
    /*!
    * Create a new instance of Manufacturer.
    */
    explicit Manufacturer(QString cnpj, QString stateNumber, QString name, QString fantasyName, QString phoneNumber,
                          QString faxNumber, QString contactName, QString email, QString addressStreet,
                          int addressNumber, QString addressComplement, QString addressSquare, QString addressCity,
                          QString addressState, QString addressPostalCode, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~Manufacturer();


    //! Get manufacturer's CNPJ.
    /*!
      Return the manufacturer's CNPJ
      \return Returns the manufacturer's CNPJ
      \sa setCNPJ()
    */
    QString getCNPJ();

    //! Get manufacturer's State Number.
    /*!
      Return the manufacturer's State Number
      \return Returns the manufacturer's State Number
      \sa setStateNumber()
    */
    QString getStateNumber();

    //! Get manufacturer's Name.
    /*!
      Return the manufacturer's Name
      \return Returns the manufacturer's Name
      \sa setName()
    */
    QString getName();

    //! Get manufacturer's Fantasy Name.
    /*!
      Return the manufacturer's Fantasy Name
      \return Returns the manufacturer's Fantasy Name
      \sa setFantasyName()
    */
    QString getFantasyName();

    //! Get manufacturer's Fantasy Name.
    /*!
      Return the manufacturer's Phone Number
      \return Returns the manufacturer's Phone Number
      \sa setPhoneNumber()
    */
    QString getPhoneNumber();

    //! Get manufacturer's Fax Number.
    /*!
      Return the manufacturer's Fax Number
      \return Returns the manufacturer's Fax Number
      \sa setFaxNumber()
    */
    QString getFaxNumber();

    //! Get manufacturer's Contact Name.
    /*!
      Return the manufacturer's Contact Name
      \return Returns the manufacturer's Contact Name
      \sa setContactName()
    */
    QString getContactName();

    //! Get manufacturer's Email.
    /*!
      Return the manufacturer's Email
      \return Returns the manufacturer's Email
      \sa setEmail()
    */
    QString getEmail();

    //! Get manufacturer's Address Street.
    /*!
      Return the manufacturer's Address Street
      \return Returns the manufacturer's Address Street
      \sa setAddressStreet()
    */
    QString getAddressStreet();

    //! Get manufacturer's Address Number.
    /*!
      Return the manufacturer's Address Number
      \return Returns the manufacturer's Address Number
      \sa setAddressNumber()
    */
    int getAddressNumber();

    //! Get manufacturer's Address Complement.
    /*!
      Return the manufacturer's Address Complement
      \return Returns the manufacturer's Address Complement
      \sa setAddressComplement()
    */
    QString getAddressComplement();

    //! Get manufacturer's Address Square.
    /*!
      Return the manufacturer's Address Square
      \return Returns the manufacturer's Address Square
      \sa setAddressSquare()
    */
    QString getAddressSquare();

    //! Get manufacturer's Address City.
    /*!
      Return the manufacturer's Address City
      \return Returns the manufacturer's Address City
      \sa setAddressCity()
    */
    QString getAddressCity();

    //! Get manufacturer's Address State.
    /*!
      Return the manufacturer's Address State
      \return Returns the manufacturer's Address State
      \sa setAddressState()
    */
    QString getAddressState();

    //! Get manufacturer's Address Postal Code.
    /*!
      Return the manufacturer's Address Postal Code
      \return Returns the manufacturer's Address Postal Code
      \sa setAddressPostalCode()
    */
    QString getAddressPostalCode();


    //! Set manufacturer's CNPJ.
    /*!
      \param cnpj Manufacturer's CNPJ
      \sa getCNPJ()
    */
    void setCNPJ(QString cnpj);

    //! Set manufacturer's State Number.
    /*!
      \param stateNumber Manufacturer's State Number
      \sa getCNPJ()
    */
    void setStateNumber(QString stateNumber);

    //! Set manufacturer's Name.
    /*!
      \param name Manufacturer's Name
      \sa getName()
    */
    void setName(QString name);

    //! Set manufacturer's Fantasy Name.
    /*!
      \param fantasyName Manufacturer's Fantasy Name
      \sa getFantasyName()
    */
    void setFantasyName(QString fantasyName);

    //! Set manufacturer's Phone Number.
    /*!
      \param phoneNumber Manufacturer's Phone Number
      \sa getPhoneNumber()
    */
    void setPhoneNumber(QString phoneNumber);

    //! Set manufacturer's Fax Number.
    /*!
      \param faxNumber Manufacturer's Fax Number
      \sa getFaxNumber()
    */
    void setFaxNumber(QString faxNumber);

    //! Set manufacturer's Contact Name.
    /*!
      \param contactName Manufacturer's Contact Name
      \sa getContactName()
    */
    void setContactName(QString contactName);

    //! Set manufacturer's Email.
    /*!
      \param email Manufacturer's Email
      \sa getEmail()
    */
    void setEmail(QString email);

    //! Set manufacturer's Address Street.
    /*!
      \param addressStreet Manufacturer's Address Street
      \sa getAddressStreet()
    */
    void setAddressStreet(QString addressStreet);

    //! Set manufacturer's Address Number.
    /*!
      \param addressNumber Manufacturer's Address Number
      \sa getAddressNumber()
    */
    void setAddressNumber(int addressNumber);

    //! Set manufacturer's Address Complement.
    /*!
      \param addressComplement Manufacturer's Address Complement
      \sa getAddressComplement()
    */
    void setAddressComplement(QString addressComplement);

    //! Set manufacturer's Address Square.
    /*!
      \param addressSquare Manufacturer's Address Square
      \sa getAddressSquare()
    */
    void setAddressSquare(QString addressSquare);

    //! Set manufacturer's Address City.
    /*!
      \param addressCity Manufacturer's Address City
      \sa getAddressCity()
    */
    void setAddressCity(QString addressCity);

    //! Set manufacturer's Address State.
    /*!
      \param addressState Manufacturer's Address State
      \sa getAddressState()
    */
    void setAddressState(QString addressState);

    //! Set manufacturer's Address Postal Code.
    /*!
      \param addressPostalCode Manufacturer's Address Postal Code
      \sa getAddressPostalCode()
    */
    void setAddressPostalCode(QString addressPostalCode);

private:
    QString cnpj;
    QString stateNumber;
    QString name;
    QString fantasyName;
    QString phoneNumber;
    QString faxNumber;
    QString contactName;
    QString email;
    QString addressStreet;
    int addressNumber;
    QString addressComplement;
    QString addressSquare;
    QString addressCity;
    QString addressState;
    QString addressPostalCode;

signals:

public slots:

};

#endif // MANUFACTURER_H
