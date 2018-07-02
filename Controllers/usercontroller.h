#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include "databasecontroller.h"
#include "utilities.h"

//!  Controller for system users
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for system users management.
*/
class UserController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of UserController.
    */
    explicit UserController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~UserController();

    /*!
    Beforing adding an user, this method checks if there is already an user with that CPF,
    if his name has less than 100 characters, and if the given CPF is valid.
      \param user The User object to be added.
      \return Returns the Status Control of the operation.
      \sa updateUser(), removeUser(), getUserByCPF(), getUsers(), getUserRoleName() and getUsersRoles()
    */
    Utilities::StatusControl addUser(User *user);

    /*!
    Beforing updating an user, this method checks if there is an user with that CPF,
    and if his name has less than 100 characters.
      \param user The User object to be updated.
      \return Returns the Status Control of the operation.
      \sa addUser(), removeUser(), getUserByCPF(), getUsers(), getUserRoleName() and getUsersRoles()
    */
    Utilities::StatusControl updateUser(User *user);

    /*!
    Beforing removing an user, this method checks if there is an user with that CPF.
      \param cpf The cpf whose user will be removed.
      \return Returns the Status Control of the operation.
      \sa addUser(), updateUser(), getUserByCPF(), getUsers(), getUserRoleName() and getUsersRoles()
    */
    Utilities::StatusControl removeUser(QString cpf);

    /*!
    Get an user by his CPF.
      \param cpf The User's CPF.
      \return Returns the user object associated with the given CPF.
      \sa addUser(), updateUser(), removeUser(), getUsers(), getUserRoleName() and getUsersRoles()
    */
    User *getUserByCPF(QString cpf);

    /*!
    This method returns all the users that were previously stored at database.
      \return Returns all stored users.
      \sa addUser(), updateUser(), removeUser(), getUserByCPF(), getUserRoleName() and getUsersRoles()
    */
    QList<User*> *getUsers();

    /*!
    This method returns the user's role name by its id.
      \param role The User's role id.
      \return Returns the role name.
      \sa addUser(), updateUser(), removeUser(), getUserByCPF(), getUsers() and getUsersRoles()
    */
    QString getUserRoleName(User::UserRole role);

    /*!
    This method returns all the user's role that were previously stored at database.
      \return Returns all stored user's roles.
      \sa addUser(), updateUser(), removeUser(), getUserByCPF(), getUsers() and getUserRoleName()
    */
    QStringList *getUsersRoles();

    /*!
    Validates the user login.
      \param cpf The User's CPF.
      \param password The User's encrypted password.
      \return Returns true if the credentials match, otherwise return false.
    */
    bool validateLogin(QString cpf, QString password);

private:

    DatabaseController *dbController;

signals:

public slots:

};

#endif // USERCONTROLLER_H
