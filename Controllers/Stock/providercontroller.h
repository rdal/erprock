#ifndef PROVIDERCONTROLLER_H
#define PROVIDERCONTROLLER_H

#include <QObject>
#include "utilities.h"
#include "databasecontroller.h"

//!  Controller for providers
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for providers management.
*/
class ProviderController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of ProviderController.
    */
    explicit ProviderController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ProviderController();

    /*!
    Beforing adding a provider, this method checks if there is already a provider with that CNPJ,
    if its name has less than 100 characters, and if the given CNPJ is valid.
      \param provider The Provider object to be added.
      \return Returns the Status Control of the operation.
      \sa updateProvider(), removeProvider(), getProviderByCNPJ() and getProviders()
    */
    Utilities::StatusControl addProvider(Provider *provider);

    /*!
    Beforing updating a provider, this method checks if there is a provider with that CNPJ,
    and if its name has less than 100 characters.
      \param provider The Provider object to be updated.
      \return Returns the Status Control of the operation.
      \sa addProvider(), removeProvider(), getProviderByCNPJ() and getProviders()
    */
    Utilities::StatusControl updateProvider(Provider *provider);

    /*!
    Beforing removing an provider, this method checks if there is a provider with that CNPJ.
      \param cnpj The cnpj whose provider will be removed.
      \return Returns the Status Control of the operation.
      \sa addProvider(), updateProvider(), getProviderByCNPJ() and getProviders()
    */
    Utilities::StatusControl removeProvider(QString cnpj);

    /*!
    Get an provider by its CNPJ.
      \param cnpj The Provider's CNPJ.
      \return Returns the provider object associated with the given CNPJ.
      \sa addProvider(), updateProvider(), removeProvider() and getProviders()
    */
    Provider *getProviderByCNPJ(QString cnpj);

    /*!
    This method returns all the providers that were previously stored at database.
      \return Returns all stored providers.
      \sa addProvider(), updateProvider(), removeProvider() and getProviderByCNPJ()
    */
    QList<Provider*> *getProviders();

private:
    DatabaseController *dbController;

signals:

public slots:

};

#endif // PROVIDERCONTROLLER_H
