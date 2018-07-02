#ifndef TESTING_H
#define TESTING_H

#include <QObject>

//!  Unit Tests
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is for testing purposes.
*/
class Testing : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of Testing.
    */
    explicit Testing(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~Testing();

    //! Adds an user
    /*!
      This method runs an unit test, that verifies the process of inserting an user.
    */
    static void addUser();

    //! Updates an user
    /*!
      This method runs an unit test, that verifies the process of updating an user.
    */
    static void updateUser();

    //! Removes an user
    /*!
      This method runs an unit test, that verifies the process of removing an user.
    */
    static void removeUser();

    //! Get all user
    /*!
      This method runs an unit test, that verifies the process of getting all users.
    */
    static void getUsers();

    //! Adds a manufacturer
    /*!
      This method runs an unit test, that verifies the process of inserting a manufacturer.
    */
    static void addManufacturer();

    //! Updates a manufacturer
    /*!
      This method runs an unit test, that verifies the process of updating a manufacturer.
    */
    static void updateManufacturer();

    //! Removes a manufacturer
    /*!
      This method runs an unit test, that verifies the process of removing a manufacturer.
    */
    static void removeManufacturer();

    //! Adds a product category
    /*!
      This method runs an unit test, that verifies the process of inserting a product category.
    */
    static void addProductCategory();

    //! Updates a product category
    /*!
      This method runs an unit test, that verifies the process of updating a product category.
    */
    static void updateProductCategory();

    //! Removes a product category
    /*!
      This method runs an unit test, that verifies the process of removing a product category.
    */
    static void removeProductCategory();

    //! Adds a physical customer
    /*!
      This method runs an unit test, that verifies the process of inserting a physical customer.
    */
    static void addPhysicalCustomer();

    //! Updates a physical customer
    /*!
      This method runs an unit test, that verifies the process of updating a physical customer.
    */
    static void updatePhysicalCustomer();

    //! Removes a physical customer
    /*!
      This method runs an unit test, that verifies the process of removing a physical customer.
    */
    static void removePhysicalCustomer();

    //! Adds an enterprise customer
    /*!
      This method runs an unit test, that verifies the process of inserting an enterprise customer.
    */
    static void addEnterpriseCustomer();

    //! Updates an enterprise customer
    /*!
      This method runs an unit test, that verifies the process of updating an enterprise customer.
    */
    static void updateEnterpriseCustomer();

    //! Removes an enterprise customer
    /*!
      This method runs an unit test, that verifies the process of removing an enterprise customer.
    */
    static void removeEnterpriseCustomer();

    //! Adds a product origin
    /*!
      This method runs an unit test, that verifies the process of inserting a product origin.
    */
    static void addProductOrigin();

    //! Updates a product origin
    /*!
      This method runs an unit test, that verifies the process of updating a product origin.
    */
    static void updateProductOrigin();

    //! Removes a product origin
    /*!
      This method runs an unit test, that verifies the process of removing a product origin.
    */
    static void removeProductOrigin();

    //! Adds a cst icms
    /*!
      This method runs an unit test, that verifies the process of inserting a cst icms.
    */
    static void addCstIcms();

    //! Updates a cst icms
    /*!
      This method runs an unit test, that verifies the process of updating a cst icms.
    */
    static void updateCstIcms();

    //! Removes a cst icms
    /*!
      This method runs an unit test, that verifies the process of removing a cst icms.
    */
    static void removeCstIcms();

signals:

public slots:

};

#endif // TESTING_H
