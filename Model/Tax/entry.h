#ifndef ENTRY_H
#define ENTRY_H

#include <QObject>
#include <QDateTime>

//!  History basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for Entry.
*/
class Entry : public QObject
{
    Q_OBJECT
public:

    //! Constructor.
    /*!
    * Create a new instance of Entry. Use this constructor when updating a new Entry Object.
    */
    explicit Entry(int id, QDateTime date, QString storeCnpj, QString debtorAccount, QString creditorAccount, double value, int historyId, QString complement, QObject *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of Entry. Use this constructor when creating a new Entry Object.
    */
    explicit Entry(QDateTime date, QString storeCnpj, QString debtorAccount, QString creditorAccount, double value, int historyId, QString complement, QObject *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of Entry. Use this constructor when updating a new Entry Object, for a purchase or sale order.
    */
    explicit Entry(int id, QDateTime date, QString storeCnpj, QString debtorAccount, QString creditorAccount, double value, int historyId, QString complement, int purchaseOrder, int saleOrder, QObject *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of Entry. Use this constructor when creating a new Entry Object, for a purchase or sale order.
    */
    explicit Entry(QDateTime date, QString storeCnpj, QString debtorAccount, QString creditorAccount, double value, int historyId, QString complement, int purchaseOrder, int saleOrder, QObject *parent = 0);

    //! Get Entry's id.
    /*!
      Return the Entry's id
      \return Returns the Entry's id
    */
    int getId();

    //! Get Entry's date.
    /*!
      Return the Entry's date
      \return Returns the Entry's date
      \sa setDate()
    */
    QDateTime getDate();

    //! Get Entry's store cnpj.
    /*!
      Return the Entry's store cnpj
      \return Returns the Entry's store cnpj
      \sa setStoreCnpj()
    */
    QString getStoreCnpj();

    //! Get Entry's debtor account code.
    /*!
      Return the Entry's debtor account code
      \return Returns the Entry's debtor account code
      \sa setDebtorAccount()
    */
    QString getDebtorAccount();

    //! Get Entry's creditor account code.
    /*!
      Return the Entry's creditor account code
      \return Returns the Entry's creditor account code
      \sa setCreditorAccount()
    */
    QString getCreditorAccount();

    //! Get Entry's value.
    /*!
      Return the Entry's value
      \return Returns the Entry's value
      \sa setValue()
    */
    double getValue();

    //! Get Entry's history.
    /*!
      Return the Entry's history
      \return Returns the Entry's history
      \sa setHistory()
    */
    int getHistory();

    //! Get Entry's complement.
    /*!
      Return the Entry's complement
      \return Returns the Entry's complement
      \sa setComplement()
    */
    QString getComplement();

    //! Get Entry's purchase order id.
    /*!
      Return the Entry's purchase order id
      \return Returns the Entry's purchase order id
      \sa setPurchaseOrderId()
    */
    int getPurchaseOrderId();

    //! Get Entry's sale order id.
    /*!
      Return the Entry's sale order id
      \return Returns the Entry's sale order id
      \sa setSaleOrderId()
    */
    int getSaleOrderId();

    //! Set Entry's date.
    /*!
      \param date Entry's date
      \sa getDate()
    */
    void setDate(QDateTime date);

    //! Set Entry's store cnpj.
    /*!
      \param storeCnpj Entry's store cnpj
      \sa getStoreCnpj()
    */
    void setStoreCnpj(QString storeCnpj);

    //! Set Entry's debtor account.
    /*!
      \param debtorAccount Entry's debtor account
      \sa getDebtorAccount()
    */
    void setDebtorAccount(QString debtorAccount);

    //! Set Entry's creditor account.
    /*!
      \param debtorAccount Entry's creditor account
      \sa getCreditorAccount()
    */
    void setCreditorAccount(QString creditorAccount);

    //! Set Entry's value.
    /*!
      \param value Entry's value
      \sa getValue()
    */
    void setValue(double value);

    //! Set Entry's history.
    /*!
      \param historyId Entry's history
      \sa getHistory()
    */
    void setHistory(int historyId);

    //! Set Entry's complement.
    /*!
      \param complement Entry's complement
      \sa getComplement()
    */
    void setComplement(QString complement);

    //! Set Entry's purchase order id.
    /*!
      \param historyId Entry's purchase order id
      \sa getPurchaseOrderId()
    */
    void setPurchaseOrderId(int purchaseId);

    //! Set Entry's sale order id.
    /*!
      \param historyId Entry's sale order id
      \sa getSaleOrderId()
    */
    void setSaleOrderId(int saleId);

private:

    int id;
    QDateTime date;
    QString storeCnpj;
    QString debtorAccount;
    QString creditorAccount;
    double value;
    int historyId;
    QString complement;
    int purchaseOrderId;
    int saleOrderId;
    
signals:
    
public slots:
    
};

#endif // ENTRY_H
