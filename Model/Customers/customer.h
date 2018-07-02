#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>

//!  Customer basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Customer.
*/
class Customer : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of Customer.
    */
    explicit Customer(QString name, QString phoneNumber, QString email, QString addressStreet, int addressNumber,
                      QString addressComplement, QString addressSquare, QString addressCity, QString addressState,
                      QString addressPostalCode, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    virtual ~Customer();

    //! Get customer's Name.
    /*!
      Return the customer's Name
      \return Returns the customer's Name
      \sa setName()
    */
    QString getName();

    //! Get customer's Fantasy Name.
    /*!
      Return the customer's Phone Number
      \return Returns the customer's Phone Number
      \sa setPhoneNumber()
    */
    QString getPhoneNumber();

    //! Get customer's Email.
    /*!
      Return the customer's Email
      \return Returns the customer's Email
      \sa setEmail()
    */
    QString getEmail();

    //! Get customer's Address Street.
    /*!
      Return the customer's Address Street
      \return Returns the customer's Address Street
      \sa setAddressStreet()
    */
    QString getAddressStreet();

    //! Get customer's Address Number.
    /*!
      Return the customer's Address Number
      \return Returns the customer's Address Number
      \sa setAddressNumber()
    */
    int getAddressNumber();

    //! Get customer's Address Complement.
    /*!
      Return the customer's Address Complement
      \return Returns the customer's Address Complement
      \sa setAddressComplement()
    */
    QString getAddressComplement();

    //! Get customer's Address Square.
    /*!
      Return the customer's Address Square
      \return Returns the customer's Address Square
      \sa setAddressSquare()
    */
    QString getAddressSquare();

    //! Get customer's Address City.
    /*!
      Return the customer's Address City
      \return Returns the customer's Address City
      \sa setAddressCity()
    */
    QString getAddressCity();

    //! Get customer's Address State.
    /*!
      Return the customer's Address State
      \return Returns the customer's Address State
      \sa setAddressState()
    */
    QString getAddressState();

    //! Get customer's Address Postal Code.
    /*!
      Return the customer's Address Postal Code
      \return Returns the customer's Address Postal Code
      \sa setAddressPostalCode()
    */
    QString getAddressPostalCode();

    //! Set customer's Name.
    /*!
      \param name Customer's Name
      \sa getName()
    */
    void setName(QString name);

    //! Set customer's Phone Number.
    /*!
      \param phoneNumber Customer's Phone Number
      \sa getPhoneNumber()
    */
    void setPhoneNumber(QString phoneNumber);

    //! Set customer's Email.
    /*!
      \param email Customer's Email
      \sa getEmail()
    */
    void setEmail(QString email);

    //! Set customer's Address Street.
    /*!
      \param addressStreet Customer's Address Street
      \sa getAddressStreet()
    */
    void setAddressStreet(QString addressStreet);

    //! Set customer's Address Number.
    /*!
      \param addressNumber Customer's Address Number
      \sa getAddressNumber()
    */
    void setAddressNumber(int addressNumber);

    //! Set customer's Address Complement.
    /*!
      \param addressComplement Customer's Address Complement
      \sa getAddressComplement()
    */
    void setAddressComplement(QString addressComplement);

    //! Set customer's Address Square.
    /*!
      \param addressSquare Customer's Address Square
      \sa getAddressSquare()
    */
    void setAddressSquare(QString addressSquare);

    //! Set customer's Address City.
    /*!
      \param addressCity Customer's Address City
      \sa getAddressCity()
    */
    void setAddressCity(QString addressCity);

    //! Set customer's Address State.
    /*!
      \param addressState Customer's Address State
      \sa getAddressState()
    */
    void setAddressState(QString addressState);

    //! Set customer's Address Postal Code.
    /*!
      \param addressPostalCode Customer's Address Postal Code
      \sa getAddressPostalCode()
    */
    void setAddressPostalCode(QString addressPostalCode);

private:
    QString name;
    QString phoneNumber;
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

#endif // CUSTOMER_H
