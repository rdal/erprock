#ifndef ACCOUNTSCONTROLLER_H
#define ACCOUNTSCONTROLLER_H

#include <QObject>
#include "databasecontroller.h"
#include "utilities.h"

//!  Controller for accounts
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for accounts management.
*/
class AccountsController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of AccountController.
    */
    explicit AccountsController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AccountsController();

    /*!
    Beforing adding an account, this method checks if there is already an account with that code and
    if his name has less than 100 characters.
      \param account The Account object to be added.
      \return Returns the Status Control of the operation.
      \sa updateAccount(), removeAccount(), getAccountByCode(), getAccounts(), getSyntheticAccounts() and getAccountTypes()
    */
    Utilities::StatusControl addAccount(Account *account);

    /*!
    Beforing updating an account, this method checks if there is an account with that code,
    and if his name has less than 100 characters.
      \param code The original account code that is being modified.
      \param account The Account object to be updated.
      \return Returns the Status Control of the operation.
      \sa addAccount(), removeAccount(), getAccountByCode(), getAccounts(), getSyntheticAccounts() and getAccountTypes()
    */
    Utilities::StatusControl updateAccount(QString code, Account *account);

    /*!
    Beforing removing an account, this method checks if there is an account with that code.
      \param code The code whose account will be removed.
      \return Returns the Status Control of the operation.
      \sa addAccount(), updateAccount(), getAccountByCode(), getAccounts(), getSyntheticAccounts() and getAccountTypes()
    */
    Utilities::StatusControl removeAccount(QString code);

    /*!
    Get an account by his code.
      \param code The Account's code.
      \return Returns the account object associated with the given code.
      \sa addAccount(), updateAccount(), removeAccount(), getAccounts(), getSyntheticAccounts() and getAccountTypes()
    */
    Account *getAccountByCode(QString code);

    /*!
    This method returns all the accounts that were previously stored at database.
      \return Returns all stored accounts.
      \sa addAccount(), updateAccount(), removeAccount(), getAccountByCode(), getSyntheticAccounts() and getAccountTypes()
    */
    QList<Account*> *getAccounts();

    QList<Account*> *getAnalyticAccounts();

    /*!
    This method returns all synthetic accounts that were previously stored at database.
      \return Returns all synthetic accounts.
      \sa addAccount(), updateAccount(), removeAccount(), getAccountByCode(), getAccounts() and getAccountTypes()
    */
    QList<Account*> *getSyntheticAccounts();

    /*!
    This method returns all the account's role that were previously stored at database.
      \return Returns all stored account's roles.
      \sa addAccount(), updateAccount(), removeAccount(), getAccountByCode(), getAccounts() and getSyntheticAccounts()
    */
    QStringList *getAccountTypes();

private:

    DatabaseController *dbController;
    
signals:
    
public slots:
    
};

#endif // ACCOUNTSCONTROLLER_H
