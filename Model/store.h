#ifndef STORE_H
#define STORE_H

#include <QObject>

//!  Store basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Store.
*/
class Store : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of Store.
    */
    explicit Store(QString cnpj, QString stateNumber, QString name, QString fantasyName, QString phoneNumber,
                   QString faxNumber, QString contactName, QString email, QString addressStreet,
                   int addressNumber, QString addressComplement, QString addressSquare, QString addressCity,
                   QString addressState, QString addressPostalCode, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~Store();

    //! Get store's CNPJ.
    /*!
      Return the store's CNPJ
      \return Returns the store's CNPJ
      \sa setCNPJ()
    */
    QString getCNPJ();

    //! Get store's State Number.
    /*!
      Return the store's State Number
      \return Returns the store's State Number
      \sa setStateNumber()
    */
    QString getStateNumber();

    //! Get store's Name.
    /*!
      Return the store's Name
      \return Returns the store's Name
      \sa setName()
    */
    QString getName();

    //! Get store's Fantasy Name.
    /*!
      Return the store's Fantasy Name
      \return Returns the store's Fantasy Name
      \sa setFantasyName()
    */
    QString getFantasyName();

    //! Get store's Fantasy Name.
    /*!
      Return the store's Phone Number
      \return Returns the store's Phone Number
      \sa setPhoneNumber()
    */
    QString getPhoneNumber();

    //! Get store's Fax Number.
    /*!
      Return the store's Fax Number
      \return Returns the store's Fax Number
      \sa setFaxNumber()
    */
    QString getFaxNumber();

    //! Get store's Contact Name.
    /*!
      Return the store's Contact Name
      \return Returns the store's Contact Name
      \sa setContactName()
    */
    QString getContactName();

    //! Get store's Email.
    /*!
      Return the store's Email
      \return Returns the store's Email
      \sa setEmail()
    */
    QString getEmail();

    //! Get store's Address Street.
    /*!
      Return the store's Address Street
      \return Returns the store's Address Street
      \sa setAddressStreet()
    */
    QString getAddressStreet();

    //! Get store's Address Number.
    /*!
      Return the store's Address Number
      \return Returns the store's Address Number
      \sa setAddressNumber()
    */
    int getAddressNumber();

    //! Get store's Address Complement.
    /*!
      Return the store's Address Complement
      \return Returns the store's Address Complement
      \sa setAddressComplement()
    */
    QString getAddressComplement();

    //! Get store's Address Square.
    /*!
      Return the store's Address Square
      \return Returns the store's Address Square
      \sa setAddressSquare()
    */
    QString getAddressSquare();

    //! Get store's Address City.
    /*!
      Return the store's Address City
      \return Returns the store's Address City
      \sa setAddressCity()
    */
    QString getAddressCity();

    //! Get store's Address State.
    /*!
      Return the store's Address State
      \return Returns the store's Address State
      \sa setAddressState()
    */
    QString getAddressState();

    //! Get store's Address Postal Code.
    /*!
      Return the store's Address Postal Code
      \return Returns the store's Address Postal Code
      \sa setAddressPostalCode()
    */
    QString getAddressPostalCode();


    //! Set store's CNPJ.
    /*!
      \param cnpj Store's CNPJ
      \sa getCNPJ()
    */
    void setCNPJ(QString cnpj);

    //! Set store's State Number.
    /*!
      \param stateNumber Store's State Number
      \sa getCNPJ()
    */
    void setStateNumber(QString stateNumber);

    //! Set store's Name.
    /*!
      \param name Store's Name
      \sa getName()
    */
    void setName(QString name);

    //! Set store's Fantasy Name.
    /*!
      \param fantasyName Store's Fantasy Name
      \sa getFantasyName()
    */
    void setFantasyName(QString fantasyName);

    //! Set store's Phone Number.
    /*!
      \param phoneNumber Store's Phone Number
      \sa getPhoneNumber()
    */
    void setPhoneNumber(QString phoneNumber);

    //! Set store's Fax Number.
    /*!
      \param faxNumber Store's Fax Number
      \sa getFaxNumber()
    */
    void setFaxNumber(QString faxNumber);

    //! Set store's Contact Name.
    /*!
      \param contactName Store's Contact Name
      \sa getContactName()
    */
    void setContactName(QString contactName);

    //! Set store's Email.
    /*!
      \param email Store's Email
      \sa getEmail()
    */
    void setEmail(QString email);

    //! Set store's Address Street.
    /*!
      \param addressStreet Store's Address Street
      \sa getAddressStreet()
    */
    void setAddressStreet(QString addressStreet);

    //! Set store's Address Number.
    /*!
      \param addressNumber Store's Address Number
      \sa getAddressNumber()
    */
    void setAddressNumber(int addressNumber);

    //! Set store's Address Complement.
    /*!
      \param addressComplement Store's Address Complement
      \sa getAddressComplement()
    */
    void setAddressComplement(QString addressComplement);

    //! Set store's Address Square.
    /*!
      \param addressSquare Store's Address Square
      \sa getAddressSquare()
    */
    void setAddressSquare(QString addressSquare);

    //! Set store's Address City.
    /*!
      \param addressCity Store's Address City
      \sa getAddressCity()
    */
    void setAddressCity(QString addressCity);

    //! Set store's Address State.
    /*!
      \param addressState Store's Address State
      \sa getAddressState()
    */
    void setAddressState(QString addressState);

    //! Set store's Address Postal Code.
    /*!
      \param addressPostalCode Store's Address Postal Code
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

#endif // STORE_H
