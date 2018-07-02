#ifndef PRICECONTROLLER_H
#define PRICECONTROLLER_H

#include <QObject>
#include "databasecontroller.h"
#include "utilities.h"

//!  Controller for prices
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for prices management.
*/
class PriceController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of PriceController.
    */
    explicit PriceController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~PriceController();

    /*!
    Beforing adding a price, this method checks if there is already a price with that name,
    if his name has less than 50 characters, etc.
      \param price The Price object to be added.
      \return Returns the Status Control of the operation.
      \sa updatePrice(), removePrice(), getPriceById(), getPriceByName(), getPrices(), getProductName() and getStoreName()
    */
    Utilities::StatusControl addPrice(Price *price);

    /*!
    Beforing updating a price, this method checks if there is a price with that name,
    and if his name has less than 50 characters.
      \param price The Price object to be updated.
      \return Returns the Status Control of the operation.
      \sa addPrice(), removePrice(), getPriceById(), getPriceByName(), getPrices(), getProductName() and getStoreName()
    */
    Utilities::StatusControl updatePrice(Price *price);

    /*!
    Remove a price by its id.
      \param id The id whose price will be removed.
      \return Returns the Status Control of the operation.
      \sa addPrice(), updatePrice(), getPriceById(), getPriceByName(), getPrices(), getProductName() and getStoreName()
    */
    Utilities::StatusControl removePrice(int id);

    /*!
    Get a price by its id.
      \param id The Price's id.
      \return Returns the price object associated with the given id.
      \sa addPrice(), updatePrice(), removePrice(), getPriceByName(), getPrices(), getProductName() and getStoreName()
    */
    Price *getPriceById(int id);

    /*!
    Get a price by its name.
      \param name The Price's name.
      \return Returns the price object associated with the given name.
      \sa addPrice(), updatePrice(), removePrice(), getPriceById(), getPrices(), getProductName() and getStoreName()
    */
    Price *getPriceByName(QString name);

    Price *getPriceByProductCode(QString productCode);

    /*!
    This method returns all the prices that were previously stored at database.
      \return Returns all stored prices.
      \sa addPrice(), updatePrice(), removePrice(), getPriceById(), getPriceByName(), getProductName() and getStoreName()
    */
    QList<Price*> *getPrices();

    /*!
    This method returns the product's name by its code.
      \param productCode The Product's code.
      \return Returns the product name.
      \sa addPrice(), updatePrice(), removePrice(), getPriceById(), getPriceByName(), getPrices() and getStoreName()
    */
    QString getProductName(QString productCode);

    /*!
    This method returns the store's name by its cnpj.
      \param cnpj The Store's cnpj.
      \return Returns the Store name.
      \sa addPrice(), updatePrice(), removePrice(), getPriceById(), getPriceByName(), getPrices() and getProductName()
    */
    QString getStoreName(QString storeCnpj);

private:

    DatabaseController *dbController;

signals:

public slots:

};

#endif // PRICECONTROLLER_H
