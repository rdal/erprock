#ifndef PURCHASESORDER_H
#define PURCHASESORDER_H

#include <QObject>
#include <QDateTime>

#include "purchaseproductorder.h"
#include "utilities.h"

//!  PurchasesOrder basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for PurchasesOrder.
*/
class PurchasesOrder : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of PurchasesOrder. Use this constructor when updating a new PurchasesOrder Object
    */
    explicit PurchasesOrder(int id, QList<PurchaseProductOrder*> *purchaseProductOrders, QString receipt, QDateTime date,
                            QString providerId, int paymentCondition, Utilities::PaymentForm paymentForm,
                            QString observation, double valuePaid, double cargo, QObject *parent = 0);

    //! Default constructor.
    /*!
    * Create a new instance of PurchasesOrder. Use this constructor when creating a new PurchasesOrder Object
    */
    explicit PurchasesOrder(QList<PurchaseProductOrder*> *purchaseProductOrders, QString receipt, QDateTime date,
                            QString providerId, int paymentCondition, Utilities::PaymentForm paymentForm,
                            QString observation, double valuePaid, double cargo, QObject *parent = 0);

    //! Get PurchasesOrder's id.
    /*!
      Return the PurchasesOrder's id
      \return Returns the PurchasesOrder's id
    */
    int getId();

    //! Get PurchasesOrder's related items.
    /*!
      Return the PurchasesOrder's related items
      \return Returns the PurchasesOrder's related items
      \sa setPurchaseProductOrders(), appendPurchaseProductOrder(), removePurchaseProductOrder() and removeAllPurchaseProductOrders()
    */
    QList<PurchaseProductOrder*> *getPurchaseProductOrders();

    //! Get PurchasesOrder's receipt.
    /*!
      Return the PurchasesOrder's receipt
      \return Returns the PurchasesOrder's receipt
      \sa setReceipt()
    */
    QString getReceipt();

    //! Get PurchasesOrder's date.
    /*!
      Return the PurchasesOrder's date
      \return Returns the PurchasesOrder's date
      \sa setDate()
    */
    QDateTime getDate();

    //! Get PurchasesOrder's date.
    /*!
      Return the PurchasesOrder's provider id
      \return Returns the PurchasesOrder's provider id
      \sa setProviderId()
    */
    QString getProviderId();

    //! Get PurchasesOrder's payment condition.
    /*!
      Return the PurchasesOrder's payment condition. This method tells in how many times the total value was divided.
      \return Returns the PurchasesOrder's payment condition
      \sa setPaymentCondition()
    */
    int getPaymentCondition();

    //! Get PurchasesOrder's payment form.
    /*!
      Return the PurchasesOrder's payment form
      \return Returns the PurchasesOrder's payment form. If the payment will be done with bank ticket, cache, etc.
      \sa setPaymentCondition() and getPaymentFormName()
    */
    Utilities::PaymentForm getPaymentForm();

    //! Get PurchasesOrder's observation.
    /*!
      Return the PurchasesOrder's observation. Something the user want to tell about this purchase order.
      \return Returns the PurchasesOrder's observation
      \sa setObservation()
    */
    QString getObservation();

    //! Get PurchasesOrder's value paid.
    /*!
      Return the PurchasesOrder's value paid
      \return Returns the PurchasesOrder's value paid
      \sa setValuePaid()
    */
    double getValuePaid();

    //! Get PurchasesOrder's cargo value.
    /*!
      Return the PurchasesOrder's cargo value
      \return Returns the PurchasesOrder's cargo value
      \sa setCargo()
    */
    double getCargo();

    //! Get PurchasesOrder's total value.
    /*!
      Return the PurchasesOrder's total value
      \return Returns the PurchasesOrder's total value
      \sa setValueTotal()
    */
    double getValueTotal();

    //! Set PurchasesOrder's related items.
    /*!
      \param purchaseProductOrders PurchasesOrder's related items
      \sa getPurchaseProductOrders(), appendPurchaseProductOrder(), removePurchaseProductOrder() and removeAllPurchaseProductOrders()
    */
    void setPurchaseProductOrders(QList<PurchaseProductOrder*> *purchaseProductOrders);

    //! Append a PurchasesOrder's related item.
    /*!
      \param purchaseProductOrder PurchasesOrder's related item
      \sa getPurchaseProductOrders(), setPurchaseProductOrders(), removePurchaseProductOrder() and removeAllPurchaseProductOrders()
    */
    void appendPurchaseProductOrder(PurchaseProductOrder *purchaseProductOrder);

    //! Remove a PurchasesOrder's related item.
    /*!
      \param purchaseProductOrder A PurchasesOrder's related item to be removed
      \sa getPurchaseProductOrders(), setPurchaseProductOrders(), appendPurchaseProductOrder() and removeAllPurchaseProductOrders()
    */
    void removePurchaseProductOrder(PurchaseProductOrder *purchaseProductOrder);

    //! Set PurchasesOrder's receipt.
    /*!
      \param receipt PurchasesOrder's receipt
      \sa getReceipt()
    */
    void setReceipt(QString receipt);

    //! Set PurchasesOrder's date.
    /*!
      \param date PurchasesOrder's date
      \sa getDate()
    */
    void setDate(QDateTime date);

    //! Set PurchasesOrder's provider id.
    /*!
      \param date PurchasesOrder's provider id
      \sa getProviderId()
    */
    void setProviderId(QString providerId);

    //! Set PurchasesOrder's payment condition. This method sets in how many times the total value was divided.
    /*!
      \param paymentCondition PurchasesOrder's receipt
      \sa getPaymentCondition()
    */
    void setPaymentCondition(int paymentCondition);

    //! Set PurchasesOrder's payment form. If the payment will be done with bank ticket, cache, etc.
    /*!
      \param paymentForm PurchasesOrder's payment form
      \sa getPaymentForm() and getPaymentFormName()
    */
    void setPaymentForm(Utilities::PaymentForm paymentForm);

    //! Set PurchasesOrder's observation. Something the user want to tell about this purchase order.
    /*!
      \param observation PurchasesOrder's observation
      \sa getObservation()
    */
    void setObservation(QString observation);

    //! Set PurchasesOrder's value paid.
    /*!
      \param valuePaid PurchasesOrder's value paid
      \sa getValuePaid()
    */
    void setValuePaid(double valuePaid);

    //! Set PurchasesOrder's cargo value.
    /*!
      \param cargo PurchasesOrder's cargo value
      \sa getCargo()
    */
    void setCargo(double cargo);

signals:

private:
    int id;
    QList<PurchaseProductOrder*> *purchaseProductOrders;
    QString receipt;
    QDateTime date;
    QString providerId;
    int paymentCondition; // Number of payments to get the total amount paid
    Utilities::PaymentForm paymentForm;
    QString observation;
    double valuePaid;
    double cargo;

public slots:

};

#endif // PURCHASESORDER_H
