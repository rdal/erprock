#ifndef PROVIDER_H
#define PROVIDER_H

#include <QObject>

//!  Provider basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Provider.
*/
class Provider : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of Provider.
    */
    explicit Provider(QString cnpj, QString stateNumber, QString name, QString fantasyName, QString phoneNumber,
                      QString faxNumber, QString contactName, QString email, QString addressStreet,
                      int addressNumber, QString addressComplement, QString addressSquare, QString addressCity,
                      QString addressState, QString addressPostalCode, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~Provider();


    //! Get provider's CNPJ.
    /*!
      Return the provider's CNPJ
      \return Returns the provider's CNPJ
      \sa setCNPJ()
    */
    QString getCNPJ();

    //! Get provider's State Number.
    /*!
      Return the provider's State Number
      \return Returns the provider's State Number
      \sa setStateNumber()
    */
    QString getStateNumber();

    //! Get provider's Name.
    /*!
      Return the provider's Name
      \return Returns the provider's Name
      \sa setName()
    */
    QString getName();

    //! Get provider's Fantasy Name.
    /*!
      Return the provider's Fantasy Name
      \return Returns the provider's Fantasy Name
      \sa setFantasyName()
    */
    QString getFantasyName();

    //! Get provider's Fantasy Name.
    /*!
      Return the provider's Phone Number
      \return Returns the provider's Phone Number
      \sa setPhoneNumber()
    */
    QString getPhoneNumber();

    //! Get provider's Fax Number.
    /*!
      Return the provider's Fax Number
      \return Returns the provider's Fax Number
      \sa setFaxNumber()
    */
    QString getFaxNumber();

    //! Get provider's Contact Name.
    /*!
      Return the provider's Contact Name
      \return Returns the provider's Contact Name
      \sa setContactName()
    */
    QString getContactName();

    //! Get provider's Email.
    /*!
      Return the provider's Email
      \return Returns the provider's Email
      \sa setEmail()
    */
    QString getEmail();

    //! Get provider's Address Street.
    /*!
      Return the provider's Address Street
      \return Returns the provider's Address Street
      \sa setAddressStreet()
    */
    QString getAddressStreet();

    //! Get provider's Address Number.
    /*!
      Return the provider's Address Number
      \return Returns the provider's Address Number
      \sa setAddressNumber()
    */
    int getAddressNumber();

    //! Get provider's Address Complement.
    /*!
      Return the provider's Address Complement
      \return Returns the provider's Address Complement
      \sa setAddressComplement()
    */
    QString getAddressComplement();

    //! Get provider's Address Square.
    /*!
      Return the provider's Address Square
      \return Returns the provider's Address Square
      \sa setAddressSquare()
    */
    QString getAddressSquare();

    //! Get provider's Address City.
    /*!
      Return the provider's Address City
      \return Returns the provider's Address City
      \sa setAddressCity()
    */
    QString getAddressCity();

    //! Get provider's Address State.
    /*!
      Return the provider's Address State
      \return Returns the provider's Address State
      \sa setAddressState()
    */
    QString getAddressState();

    //! Get provider's Address Postal Code.
    /*!
      Return the provider's Address Postal Code
      \return Returns the provider's Address Postal Code
      \sa setAddressPostalCode()
    */
    QString getAddressPostalCode();


    //! Set provider's CNPJ.
    /*!
      \param cnpj Provider's CNPJ
      \sa getCNPJ()
    */
    void setCNPJ(QString cnpj);

    //! Set provider's State Number.
    /*!
      \param stateNumber Provider's State Number
      \sa getCNPJ()
    */
    void setStateNumber(QString stateNumber);

    //! Set provider's Name.
    /*!
      \param name Provider's Name
      \sa getName()
    */
    void setName(QString name);

    //! Set provider's Fantasy Name.
    /*!
      \param fantasyName Provider's Fantasy Name
      \sa getFantasyName()
    */
    void setFantasyName(QString fantasyName);

    //! Set provider's Phone Number.
    /*!
      \param phoneNumber Provider's Phone Number
      \sa getPhoneNumber()
    */
    void setPhoneNumber(QString phoneNumber);

    //! Set provider's Fax Number.
    /*!
      \param faxNumber Provider's Fax Number
      \sa getFaxNumber()
    */
    void setFaxNumber(QString faxNumber);

    //! Set provider's Contact Name.
    /*!
      \param contactName Provider's Contact Name
      \sa getContactName()
    */
    void setContactName(QString contactName);

    //! Set provider's Email.
    /*!
      \param email Provider's Email
      \sa getEmail()
    */
    void setEmail(QString email);

    //! Set provider's Address Street.
    /*!
      \param addressStreet Provider's Address Street
      \sa getAddressStreet()
    */
    void setAddressStreet(QString addressStreet);

    //! Set provider's Address Number.
    /*!
      \param addressNumber Provider's Address Number
      \sa getAddressNumber()
    */
    void setAddressNumber(int addressNumber);

    //! Set provider's Address Complement.
    /*!
      \param addressComplement Provider's Address Complement
      \sa getAddressComplement()
    */
    void setAddressComplement(QString addressComplement);

    //! Set provider's Address Square.
    /*!
      \param addressSquare Provider's Address Square
      \sa getAddressSquare()
    */
    void setAddressSquare(QString addressSquare);

    //! Set provider's Address City.
    /*!
      \param addressCity Provider's Address City
      \sa getAddressCity()
    */
    void setAddressCity(QString addressCity);

    //! Set provider's Address State.
    /*!
      \param addressState Provider's Address State
      \sa getAddressState()
    */
    void setAddressState(QString addressState);

    //! Set provider's Address Postal Code.
    /*!
      \param addressPostalCode Provider's Address Postal Code
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

#endif // PROVIDER_H
