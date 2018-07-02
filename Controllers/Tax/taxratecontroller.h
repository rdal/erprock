#ifndef TAXRATECONTROLLER_H
#define TAXRATECONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for tax rates
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for product tax rates.
*/
class TaxRateController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of TaxRateController.
    */
    explicit TaxRateController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~TaxRateController();

    /*!
    Beforing adding a tax rate, this method checks if there is already a tax rate with that name
    and if its name has less than 30 characters.
      \param taxRate The TaxRate object to be added.
      \return Returns the Status Control of the operation.
      \sa updateTaxRate(), removeTaxRate(), getTaxRateByName() and getTaxRates()
    */
    Utilities::StatusControl addTaxRate(TaxRate *taxRate);

    /*!
    Beforing updating a tax rate, this method checks if there is a tax rate with that name,
    and if its name has less than 100 characters.
      \param name The name whose tax rate will be updated.
      \param taxRate The TaxRate object to be updated.
      \return Returns the Status Control of the operation.
      \sa addTaxRate(), removeTaxRate(), getTaxRateByName() and getTaxRates()
    */
    Utilities::StatusControl updateTaxRate(QString name, TaxRate *taxRate);

    /*!
    Beforing removing an tax rate, this method checks if there is a tax rate with that name.
      \param name The name whose tax rate will be removed.
      \return Returns the Status Control of the operation.
      \sa addTaxRate(), updateTaxRate(), getTaxRateByName() and getTaxRates()
    */
    Utilities::StatusControl removeTaxRate(QString name);

    /*!
    Get a tax rate by its name.
      \param name The TaxRate name.
      \return Returns the tax rate object associated with the given name.
      \sa addTaxRate(), updateTaxRate(), removeTaxRate() and getTaxRates()
    */
    TaxRate *getTaxRateByName(QString name);

    /*!
    This method returns all the tax rates that were previously stored at database.
      \return Returns all stored tax rates.
      \sa addTaxRate(), updateTaxRate(), removeTaxRate() and getTaxRateByName()
    */
    QList<TaxRate*> *getTaxRates();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // TAXRATECONTROLLER_H
