#ifndef PRODUCTCONTROLLER_H
#define PRODUCTCONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for products
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for products management.
*/
class ProductController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of ProductController.
    */
    explicit ProductController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ProductController();

    /*!
    Beforing adding a product, this method checks if there is already a product with that code
    and if its name has less than 100 characters.
      \param product The Product object to be added.
      \return Returns the Status Control of the operation.
      \sa updateProduct(), removeProduct(), getProductByCode() getProducts() and getQuantityByCode()
    */
    Utilities::StatusControl addProduct(Product *product);

    /*!
    Beforing updating a product, this method checks if there is a product with that code,
    and if its name has less than 100 characters.
      \param code The code whose product will be updated.
      \param product The Product object to be updated.
      \return Returns the Status Control of the operation.
      \sa addProduct(), removeProduct(), getProductByCode() and getProducts() and getQuantityByCode()
    */
    Utilities::StatusControl updateProduct(QString code, Product *product);

    /*!
    Beforing removing an product, this method checks if there is a product with that code.
      \param code The code whose product will be removed.
      \return Returns the Status Control of the operation.
      \sa addProduct(), updateProduct(), getProductByCode() getProducts() and getQuantityByCode()
    */
    Utilities::StatusControl removeProduct(QString code);

    /*!
    Get an product by its code.
      \param code The Product code.
      \return Returns the product object associated with the given code.
      \sa addProduct(), updateProduct(), removeProduct() getProducts() and getQuantityByCode()
    */
    Product *getProductByCode(QString code);

    /*!
    This method returns all the products that were previously stored at database.
      \return Returns all stored products.
      \sa addProduct(), updateProduct(), removeProduct(), getProductByCode() and getQuantityByCode()
    */
    QList<Product*> *getProducts();

    /*!
    Get an products quantity by its code.
      \param code The Product code.
      \return Returns the products quantity associated with the given code.
      \sa addProduct(), updateProduct(), removeProduct(), getProductByCode() and getProducts()
    */
    int getQuantityByCode(QString code);

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // PRODUCTCONTROLLER_H
