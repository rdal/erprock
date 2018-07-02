#ifndef PRODUCTORIGINCONTROLLER_H
#define PRODUCTORIGINCONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for product origins
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for product origins management.
*/
class ProductOriginController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of ProductOriginController.
    */
    explicit ProductOriginController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ProductOriginController();

    /*!
    Beforing adding a product origin, this method checks if there is already a product origins with that code
    and if its name has less than 30 characters.
      \param productOrigin The ProductOrigin object to be added.
      \return Returns the Status Control of the operation.
      \sa updateProductOrigin(), removeProductOrigin(), getProductOriginByCode() and getProductOrigins()
    */
    Utilities::StatusControl addProductOrigin(ProductOrigin *productOrigin);

    /*!
    Beforing updating a product origin, this method checks if there is a product origin with that code,
    and if its name has less than 100 characters.
      \param code The code whose product origin will be updated.
      \param productOrigin The ProductOrigin object to be updated.
      \return Returns the Status Control of the operation.
      \sa addProductOrigin(), removeProductOrigin(), getProductOriginByCode() and getProductOrigins()
    */
    Utilities::StatusControl updateProductOrigin(QString code, ProductOrigin *productOrigin);

    /*!
    Beforing removing an product origin, this method checks if there is a product origin with that code.
      \param code The code whose product origin will be removed.
      \return Returns the Status Control of the operation.
      \sa addProductOrigin(), updateProductOrigin(), getProductOriginByCode() and getProductOrigins()
    */
    Utilities::StatusControl removeProductOrigin(QString code);

    /*!
    Get an product origin by its code.
      \param code The ProductOrigin code.
      \return Returns the product origin object associated with the given code.
      \sa addProductOrigin(), updateProductOrigin(), removeProductOrigin() and getProductOrigins()
    */
    ProductOrigin *getProductOriginByCode(QString code);

    /*!
    This method returns all the product origins that were previously stored at database.
      \return Returns all stored product origins.
      \sa addProductOrigin(), updateProductOrigin(), removeProductOrigin() and getProductOriginByCode()
    */
    QList<ProductOrigin*> *getProductOrigins();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // PRODUCTORIGINCONTROLLER_H
