#ifndef PRICE_H
#define PRICE_H

#include <QObject>

//!  Price basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Price.
*/
class Price : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of Price. Use this constructor when updating a new Price Object
    */
    explicit Price(int id, QString productCode, double value, QString storeCnpj, QString name, QObject *parent = 0);


    //! Default constructor.
    /*!
    * Create a new instance of Price. Use this constructor when creating a new Price Object
    */
    explicit Price(QString productCode, double value, QString storeCnpj, QString name, QObject *parent = 0);

    //! Get Price's id.
    /*!
      Return the Price's id
      \return Returns the Price's id
    */
    int getId();

    //! Get Price's product code.
    /*!
      Return the Price's product code
      \return Returns the Price's product code
    */
    QString getProductCode();

    //! Get Price's store CNPJ.
    /*!
      Return the Price's store CNPJ
      \return Returns the Price's store CNPJ
      \sa setStoreCnpj()
    */
    QString getStoreCnpj();

    //! Get Price's value.
    /*!
      Return the Price's value
      \return Returns the Price's value
      \sa setValue()
    */
    double getValue();

    //! Get Price's name.
    /*!
      Return the Price's name
      \return Returns the Price's name
      \sa setname()
    */
    QString getName();

    //! Set Price's product code.
    /*!
      \param productCode Price's product code
      \sa getProductCode()
    */
    void setProductCode(QString productCode);

    //! Set Price's store cnpj.
    /*!
      \param storeCnpj Price's store cnpj
      \sa getStoreCnpj()
    */
    void setStoreCnpj(QString storeCnpj);

    //! Set Price's value.
    /*!
      \param value Price's value
      \sa getValue()
    */
    void setValue(double value);

    //! Set Price's name.
    /*!
      \param value Price's name
      \sa getName()
    */
    void setName(QString name);

private:

    int id;
    QString productCode;
    QString storeCnpj;
    double value;
    QString name;

signals:

public slots:

};

#endif // PRICE_H
