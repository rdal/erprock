#ifndef UTILITIES_H
#define UTILITIES_H

#include <QObject>
#include <QStringList>

#ifdef Q_OS_MAC
#define RESOURCES_FOLDER "/Contents/Resources/"
#include <CoreFoundation/CFBundle.h>
#elif (defined Q_OS_WIN)
#define RESOURCES_FOLDER ""
#endif

//!  Utilities class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class has several utilities methods, for general purpose. It is intended to ease some developing aspects.
*/
class Utilities : public QObject
{
    Q_OBJECT
public:

    //! Status Control
    /*! This enum is used to indicate types of errors (or no error), to be handled by UI.*/
    enum StatusControl {NO_ERR, /*!< No Error. */
                        UNKNOWN_ERROR, /*!< Unknown error. */
                        DB_NOT_CONNECTED, /*!< This error happens when database is not connected. */
                        ALREADY_EXISTS, /*!< This error happens when the object already exists. */
                        ALREADY_EXISTS_NAME, /*!< This error happens when the object name is already stored. */
                        BAR_CODE_ALREADY_EXISTS, /*!< This error happens when the object's bar code is already stored. */
                        DOESNT_EXIST, /*!< This error happens when the object does not exist. */
                        INVALID_ID, /*!< This error tells that some id is invalid. */
                        ACTION_FORBIDDEN, /*!< This error tells that some action is invalid. */
                        EMPTY /*!< This error tells that some container is empty. */
                    };

    //! Items List Window Mode
    /*! This enum is used to indicate the window mode to be set*/
    enum ItemsListWindowMode{
        DEFAULT, /*!< This is the default mode, with buttons to manage items */
        CHOOSE_ITEM /*!< In this mode, user can use the window to choose an item. */
    };

    //! Payment Form
    /*! This enum is used to indicate which payment form will be used.*/
    enum PaymentForm{MONEY = 1,     /*!< Payment with money. */
                     VISA,          /*!< Payment with Visa Credit Card. */
                     MASTERCARD,    /*!< Payment with MasterCard Credit Card. */
                     DINERS,        /*!< Payment with Diners Credit Card. */
                     AMEX,          /*!< Payment with America Express Credit Card. */
                     BANK_TICKET    /*!< Payment with bak ticket. */
                 };



    //! Default constructor.
    /*!
    * Create a new instance of Utilities.
    */
    explicit Utilities(QObject *parent = 0);

    /*!
      Return the bundle path
      \return Returns the bundle path from where we can access other directories related to the project.
      \sa getResourcesPath() and getAppPath()
    */
    static QString getBundlePath();

    /*!
      Return the resource path
      \return Returns the path where the resource files are located.
              An example of a resource file is the config file for setting the database up.
      \sa getAppPath() and getBundlePath()
    */
    static QString getResourcesPath();

    /*!
    Removes dots and dash from CPF.
      \param str The User's CPF to get stripped.
      \return The result CPF value.
    */
    static QString stripCPFChars(QString str);

    /*!
    This method checks the CPF format.
      \return Returns if it is valid or not.
    */
    static bool isCpfValid(QString cpfStr);

    /*!
    Removes dots, slash and dash from CNPJ.
      \param str The CNPJ to get stripped.
      \return The result CNPJ value.
    */
    static QString stripCNPJChars(QString str);

    /*!
    This method checks the CNPJ format.
      \param str The CNPJ to be evaluated.
      \return Returns if it is valid or not.
    */
    static bool isCNPJValid(QString str);

    /*!
    This method gets the default store CNPJ
      \return Returns the default store CNPJ
    */
    QString getDefaultCNPJ();

////    /*!
////    This method gets the default customer account
////      \return Returns the default customer account
////    */
////    QString getDefaultCustomerAccount();

//    /*!
//    This method gets the default provider account
//      \return Returns the default provider account
//    */
//    QString getDefaultProviderAccount();

////    /*!
////    This method gets the default cash account
////      \return Returns the default cash account
////    */
////    QString getDefaultCashAccount();

//    /*!
//    This method gets the default icms to recover account
//      \return Returns the default customer account
//    */
//    QString getDefaultIcmsToRecoverAccount();

//    /*!
//    This method gets the default pis to recover account
//      \return Returns the default provider account
//    */
//    QString getDefaultPisToRecoverAccount();

//    /*!
//    This method gets the default cofins to recover account
//      \return Returns the default cash account
//    */
//    QString getDefaultCofinsToRecoverAccount();

//    /*!
//    This method gets the default product stock account
//      \return Returns the default product stock account
//    */
//    QString getDefaultProductStockAccount();

//    /*!
//    This method gets the default debtor account sale account
//      \return Returns the default debtor account sale account
//    */
//    QString getDefaultDebtorSaleAccount();

//    /*!
//    This method gets the default creditor account sale account
//      \return Returns the default creditor account sale account
//    */
//    QString getDefaultCreditorSaleAccount();

//    /*!
//    This method gets the default imcs in sales debtor account
//      \return Returns the default imcs in sales debtor account
//    */
//    QString getDefaultIcmsInSalesDebtorAccount();

//    /*!
//    This method gets the default imcs in sales debtor account
//      \return Returns the default imcs in sales debtor account
//    */
//    QString getDefaultIcmsInSalesCreditorAccount();

//    /*!
//    This method gets the default pis in sales debtor account
//      \return Returns the default pis in sales debtor account
//    */
//    QString getDefaultPisInSalesDebtorAccount();

//    /*!
//    This method gets the default pis in sales debtor account
//      \return Returns the default pis in sales debtor account
//    */
//    QString getDefaultPisInSalesCreditorAccount();

//    /*!
//    This method gets the default cofins in sales debtor account
//      \return Returns the default cofins in sales debtor account
//    */
//    QString getDefaultCofinsInSalesDebtorAccount();

//    /*!
//    This method gets the default cofins in sales debtor account
//      \return Returns the default cofins in sales debtor account
//    */
//    QString getDefaultCofinsInSalesCreditorAccount();

//    /*!
//    This method gets the default goods shipping debtor account
//      \return Returns the default goods shipping debtor account
//    */
//    QString getDefaultGoodsShippingDebtorAccount();

//    /*!
//    This method gets the default goods shipping creditor account
//      \return Returns the default goods shipping creditor account
//    */
//    QString getDefaultGoodsShippingCreditorAccount();

//    /*!
//    This method gets the buy product history id
//      \return Returns the buy product history id
//    */
//    int getBuyProductHistoryId();

//    /*!
//    This method gets the tax credit history id
//      \return Returns the tax credit history id
//    */
//    int getTaxCreditHistoryId();

//    /*!
//    This method gets the sale history id
//      \return Returns the sale history id
//    */
//    int getSaleHistoryId();

//    /*!
//    This method gets the icms in sales' history id
//      \return Returns the icms in sales' history id
//    */
//    int getIcmsInSalesHistoryId();

//    /*!
//    This method gets the pis in sales' history id
//      \return Returns the pis in sales' history id
//    */
//    int getPisInSalesHistoryId();

//    /*!
//    This method gets the cofins in sales' history id
//      \return Returns the cofins in sales' history id
//    */
//    int getCofinsInSalesHistoryId();

//    /*!
//    This method gets the cofins in sales' history id
//      \return Returns the cofins in sales' history id
//    */
//    int getGoodsShippingHistoryId();

    //! Get payment form name.
    /*!
      Return the payment form name
      \param str The payment form identifier
      \return Returns the payment form name. Whether payment will be done with bank ticket, cache, etc.
    */
    static QString getPaymentFormName(PaymentForm paymentForm);

signals:

public slots:

};

#endif // UTILITIES_H
