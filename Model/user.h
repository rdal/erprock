#ifndef USER_H
#define USER_H

#include <QObject>

//!  User basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for User.
*/
class User : public QObject
{
    Q_OBJECT
public:
    //! User Role
    /*! This enum is used to indicate the user role.*/
    enum UserRole {MANAGER, /*!< Manager. This is the super user of the system */
                   SUPERVISOR, /*!< Supervisor. Almost everything is granted to this user, except core system operations. */
                   STOCK, /*!< Stock. This user has access to everything that deals with stock module. */
                   SELLER, /*!< Seller.*/
                   CASH /*!< Cash. */
                  };

    //! Default constructor.
    /*!
    * Create a new instance of User.
    */
    explicit User(QString cpf, UserRole role, QString name, QString password, QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~User();

    //! Get user's CPF.
    /*!
      Return the user's CPF
      \return Returns the user's CPF
      \sa getRole(), getName() and getPassword()
    */
    QString getCpf();

    //! Get user's Role.
    /*!
      Return the user's Role
      \return Returns the user's Role
      \sa getCpf(), getName() and getPassword()
    */
    UserRole getRole();

    //! Get user's Name.
    /*!
      Return the user's Name
      \return Returns the user's Name
      \sa getCpf(), getRole() and getPassword()
    */
    QString getName();

    //! Get user's Password.
    /*!
      Return the user's Password
      \return Returns the user's Password
      \sa getCpf(), getRole() and getName()
    */
    QString getPassword();


    //! Set user's CPF.
    /*!
      \param cpf User's CPF
      \sa setRole(), setName() and setPassword()
    */
    void setCpf(QString cpf);

    //! Set user's Role.
    /*!
      \param role User's Role
      \sa setCpf(), setName() and setPassword()
    */
    void setRole(UserRole role);

    //! Set user's Name.
    /*!
      \param name User's Name
      \sa setCpf(), setRole() and setPassword()
    */
    void setName(QString name);

    //! Set user's Password.
    /*!
      \param password User's Password
      \sa setCpf(), setRole() and setName()
    */
    void setPassword(QString password);

private:
    QString cpf;
    UserRole role;
    QString name;
    QString password;

signals:

public slots:

};

#endif // USER_H
