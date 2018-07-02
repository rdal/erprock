#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>

//!  Account basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Account.
*/
class Account : public QObject
{
    Q_OBJECT
public:

    //! User Role
    /*! This enum is used to indicate the user role.*/
    enum AccountType {NOT_INFORMED,         /*!< Not informed.*/
                      ACTIVE,               /*!< Active. This is the main account for active accounts. */
                      PASSIVE,              /*!< Passive. This is the main account for passive accounts. */
                      REVENUE,              /*!< Revenue. This is the main account for revenue accounts.*/
                      DEDUCTIONS_RETURNS,   /*!< Deductions and Returns. This is the main account for deductions and returns accounts.*/
                      COSTS,                /*!< Costs. This is the main account for costs accounts.*/
                      OPERATING_EXPENSES    /*!< Operating expenses. This is the main account for revenue operating expenses.*/
                  };

    //! Default constructor.
    /*!
    * Create a new instance of Account.
    */
    explicit Account(QString code, QString name, AccountType type, bool reductive, QObject *parent = 0);

    //! Get account's code.
    /*!
      Return the account's code
      \return Returns the account's code
      \sa getName(), getType() and isReductive()
    */
    QString getCode();

    //! Get account's name.
    /*!
      Return the account's name
      \return Returns the account's name
      \sa getCode(), getType() and isReductive()
    */
    QString getName();

    //! Get account's type.
    /*!
      Return the account's type
      \return Returns the account's type
      \sa getCode(), getName() and isReductive()
    */
    AccountType getType();

    //! Verifies if this is a reductive account.
    /*!
      Return if the account is reductive or not
      \return Returns if the account is reductive or not
      \sa getCode(), getName() and getType()
    */
    bool isReductive();

    //! Set account's code.
    /*!
      \param code Account's code
      \sa setName(), setType() and setReductive()
    */
    void setCode(QString code);

    //! Set account's name.
    /*!
      \param name Account's name
      \sa setCode(), setType() and setReductive()
    */
    void setName(QString name);

    //! Set account's type.
    /*!
      \param type Account's type
      \sa setCode(), setName() and setReductive()
    */
    void setType(AccountType type);

    //! Set if the account is reductive or not
    /*!
      \param reductive If account's is reductive or not
      \sa setCode(), setName() and setType()
    */
    void setReductive(bool reductive);

private:

    QString code;
    QString name;
    AccountType type;
    bool reductive;
    
signals:
    
public slots:
    
};

#endif // ACCOUNT_H
