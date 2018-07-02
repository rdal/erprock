#ifndef CUSTOMERCONTROLLER_H
#define CUSTOMERCONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for customers
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for customers management.
*/
class CustomerController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of CustomerController.
    */
    explicit CustomerController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CustomerController();

    /*!
    Beforing adding a customer, this method checks if there is already a customer with that CPF/CNPJ,
    if its name has less than 100 characters, and if the given CPF/CNPJ is valid.
      \param customer The Customer object to be added.
      \return Returns the Status Control of the operation.
      \sa updateCustomer(), removeCustomer(), getCustomerById(), getEnterpriseCustomers() and getPhysicalCustomers()
    */
    Utilities::StatusControl addCustomer(Customer *customer);

    /*!
    Beforing updating a customer, this method checks if there is a customer with that CPF/CNPJ,
    and if its name has less than 100 characters.
      \param customer The Customer object to be updated.
      \return Returns the Status Control of the operation.
      \sa addCustomer(), removeCustomer(), getCustomerById(), getEnterpriseCustomers() and getPhysicalCustomers()
    */
    Utilities::StatusControl updateCustomer(Customer *customer);

    /*!
    Beforing removing an customer, this method checks if there is a customer with that CPF/CNPJ.
      \param id The id whose customer will be removed.
      \return Returns the Status Control of the operation.
      \sa addCustomer(), updateCustomer(), getCustomerById(), getEnterpriseCustomers() and getPhysicalCustomers()
    */
    Utilities::StatusControl removeCustomer(QString id);

    /*!
    Get an customer by its id.
      \param id The Customer's id.
      \return Returns the customer object associated with the given id.
      \sa addCustomer(), updateCustomer(), removeCustomer(), getEnterpriseCustomers() and getPhysicalCustomers()
    */
    Customer *getCustomerById(QString id);

    /*!
    This method returns all the customers that were previously stored at database.
      \return Returns all stored customers.
      \sa addCustomer(), updateCustomer(), removeCustomer(), getCustomerById() and getEnterpriseCustomers()
    */
    QList<PhysicalCustomer*> *getPhysicalCustomers();

    /*!
    This method returns all the customers that were previously stored at database.
      \return Returns all stored customers.
      \sa addCustomer(), updateCustomer(), removeCustomer(), getCustomerById() and getPhysicalCustomers()
    */
    QList<EnterpriseCustomer*> *getEnterpriseCustomers();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // CUSTOMERCONTROLLER_H
