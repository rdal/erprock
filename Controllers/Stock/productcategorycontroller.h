#ifndef PRODUCTCATEGORYCONTROLLER_H
#define PRODUCTCATEGORYCONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for product categories
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for product categories management.
*/
class ProductCategoryController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of ProductCategoryController.
    */
    explicit ProductCategoryController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ProductCategoryController();

    /*!
    Beforing adding a product category, this method checks if there is already a product categories with that id
    and if its name has less than 30 characters.
      \param productCategory The ProductCategory object to be added.
      \return Returns the Status Control of the operation.
      \sa updateProductCategory(), removeProductCategory(), getProductCategoryById() and getProductCategories()
    */
    Utilities::StatusControl addProductCategory(ProductCategory *productCategory);

    /*!
    Beforing updating a product category, this method checks if there is a product category with that id,
    and if its name has less than 100 characters.
      \param productCategory The ProductCategory object to be updated.
      \return Returns the Status Control of the operation.
      \sa addProductCategory(), removeProductCategory(), getProductCategoryById() and getProductCategories()
    */
    Utilities::StatusControl updateProductCategory(ProductCategory *productCategory);

    /*!
    Beforing removing an product category, this method checks if there is a product category with that id.
      \param id The id whose product category will be removed.
      \return Returns the Status Control of the operation.
      \sa addProductCategory(), updateProductCategory(), getProductCategoryById() and getProductCategories()
    */
    Utilities::StatusControl removeProductCategory(int id);

    /*!
    Get an product category by its id.
      \param id The ProductCategory id.
      \return Returns the product category object associated with the given id.
      \sa addProductCategory(), updateProductCategory(), removeProductCategory() and getProductCategories()
    */
    ProductCategory *getProductCategoryById(int id);

    /*!
    This method returns all the product categories that were previously stored at database.
      \return Returns all stored product categories.
      \sa addProductCategory(), updateProductCategory(), removeProductCategory() and getProductCategoryById()
    */
    QList<ProductCategory*> *getProductCategories();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // PRODUCTCATEGORYCONTROLLER_H
