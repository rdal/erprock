#ifndef STORECONTROLLER_H
#define STORECONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for stores
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for stores management.
*/
class StoreController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of StoreController.
    */
    explicit StoreController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~StoreController();

    /*!
    Beforing adding a store, this method checks if there is already a store with that CNPJ,
    if its name has less than 100 characters, and if the given CNPJ is valid.
      \param store The Store object to be added.
      \return Returns the Status Control of the operation.
      \sa updateStore(), removeStore(), getStoreByCNPJ() and getStores()
    */
    Utilities::StatusControl addStore(Store *store);

    /*!
    Beforing updating a store, this method checks if there is a store with that CNPJ,
    and if its name has less than 100 characters.
      \param store The Store object to be updated.
      \return Returns the Status Control of the operation.
      \sa addStore(), removeStore(), getStoreByCNPJ() and getStores()
    */
    Utilities::StatusControl updateStore(Store *store);

    /*!
    Beforing removing an store, this method checks if there is a store with that CNPJ.
      \param cnpj The cnpj whose store will be removed.
      \return Returns the Status Control of the operation.
      \sa addStore(), updateStore(), getStoreByCNPJ() and getStores()
    */
    Utilities::StatusControl removeStore(QString cnpj);

    /*!
    Get an store by its CNPJ.
      \param cnpj The Store's CNPJ.
      \return Returns the store object associated with the given CNPJ.
      \sa addStore(), updateStore(), removeStore() and getStores()
    */
    Store *getStoreByCNPJ(QString cnpj);

    /*!
    This method returns all the stores that were previously stored at database.
      \return Returns all stored stores.
      \sa addStore(), updateStore(), removeStore() and getStoreByCNPJ()
    */
    QList<Store*> *getStores();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // STORECONTROLLER_H
