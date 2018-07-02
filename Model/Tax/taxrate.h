#ifndef TAXRATE_H
#define TAXRATE_H

#include <QObject>

//!  Tax Rate basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Tax Rate.
*/
class TaxRate : public QObject
{
    Q_OBJECT
public:

    //! Constructor.
    /*!
    * Create a new instance of TaxRate.
    */
    explicit TaxRate(QString name, double value, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~TaxRate();

    //! Get the name of tax rate.
    /*!
      Return the name of tax rate
      \return Returns the name of tax rate
      \sa setName()
    */
    QString getName();

    //! Get the name of tax rate.
    /*!
      Return the value of tax rate
      \return Returns the value of tax rate
      \sa setValue()
    */
    double getValue();

    //! Set the name of tax rate.
    /*!
      \param name The name of tax rate
      \sa getName()
    */
    void setName(QString name);

    //! Set the value of tax rate.
    /*!
      \param value The Value of tax rate
      \sa getValue()
    */
    void setValue(double value);

private:
    QString name;
    double value;

signals:

public slots:

};

#endif // TAXRATE_H
