#ifndef SALESORDER_H
#define SALESORDER_H

#include <QObject>
#include <QDateTime>

#include "saleproductorder.h"
#include "customer.h"
#include "utilities.h"

//!  SalesOrder basic class
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is the data model for SalesOrder.
*/
class SalesOrder : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of SalesOrder. Use this constructor when updating a new SalesOrder Object
    */
    explicit SalesOrder(int id, QList<SaleProductOrder*> *saleProductOrders, QString receipt, QDateTime date,
                        int paymentCondition, Utilities::PaymentForm paymentForm, double discount, QString observation,
                        double valuePaid, QString customerId, QObject *parent = 0);

    //! Default constructor.
    /*!
    * Create a new instance of SalesOrder. Use this constructor when creating a new SalesOrder Object
    */
    explicit SalesOrder(QList<SaleProductOrder*> *saleProductOrders, QString receipt, int paymentCondition,
                        Utilities::PaymentForm paymentForm, double discount, QString observation, double valuePaid,
                        QString customerId, QObject *parent = 0);

    //! Get SaleOrder's id.
    /*!
      Return the SaleOrder's id
      \return Returns the SaleOrder's id
    */
    int getId();

    //! Get SaleOrder's related items.
    /*!
      Return the SaleOrder's related items
      \return Returns the SaleOrder's related items
      \sa setSaleProductOrders(), appendSaleProductOrder(), removeSaleProductOrder() and removeAllSaleProductOrders()
    */
    QList<SaleProductOrder*> *getSaleProductOrders();

    //! Get SaleOrder's receipt.
    /*!
      Return the SaleOrder's receipt
      \return Returns the SaleOrder's receipt
      \sa setReceipt()
    */
    QString getReceipt();

    //! Get SaleOrder's date.
    /*!
      Return the SaleOrder's date
      \return Returns the SaleOrder's date
      \sa setDate()
    */
    QDateTime getDate();

    //! Get SaleOrder's payment condition.
    /*!
      Return the SaleOrder's payment condition. This method tells in how many times the total value was divided.
      \return Returns the SaleOrder's payment condition
      \sa setPaymentCondition()
    */
    int getPaymentCondition();

    //! Get SaleOrder's payment form.
    /*!
      Return the SaleOrder's payment form
      \return Returns the SaleOrder's payment form. If the payment will be done with bank ticket, cache, etc.
      \sa setPaymentCondition() and getPaymentFormName()
    */
    Utilities::PaymentForm getPaymentForm();

//    //! Get SaleOrder's payment form name.
//    /*!
//      Return the SaleOrder's payment form name
//      \return Returns the SaleOrder's payment form name. If the payment will be done with bank ticket, cache, etc.
//      \sa setPaymentCondition() and getPaymentForm()
//    */
//    QString getPaymentFormName(Utilities::PaymentForm paymentForm);

    //! Get SaleOrder's discount.
    /*!
      Return the SaleOrder's discount
      \return Returns the SaleOrder's discount
      \sa setDiscount()
    */
    double getDiscount();

    //! Get SaleOrder's observation.
    /*!
      Return the SaleOrder's observation. Something the user want to tell about this sale order.
      \return Returns the SaleOrder's observation
      \sa setObservation()
    */
    QString getObservation();

    //! Get SaleOrder's value paid.
    /*!
      Return the SaleOrder's value paid
      \return Returns the SaleOrder's value paid
      \sa setValuePaid()
    */
    double getValuePaid();

    //! Get SaleOrder's total value.
    /*!
      Return the SaleOrder's total value
      \return Returns the SaleOrder's total value
      \sa setValueTotal()
    */
    double getValueTotal();

    //! Get SaleOrder's customer id.
    /*!
      Return the SaleOrder's customer id
      \return Returns the SaleOrder's customer id
      \sa setCustomerId()
    */
    QString getCustomerId();

    //! Set SaleOrder's related items.
    /*!
      \param saleProductOrders SaleOrder's related items
      \sa getSaleProductOrders(), appendSaleProductOrder(), removeSaleProductOrder() and removeAllSaleProductOrders()
    */
    void setSaleProductOrders(QList<SaleProductOrder*> *saleProductOrders);

    //! Append a SaleOrder's related item.
    /*!
      \param saleProductOrder SaleOrder's related item
      \sa getSaleProductOrders(), setSaleProductOrders(), removeSaleProductOrder() and removeAllSaleProductOrders()
    */
    void appendSaleProductOrder(SaleProductOrder *saleProductOrder);

    //! Remove a SaleOrder's related item.
    /*!
      \param saleProductOrder A SaleOrder's related item to be removed
      \sa getSaleProductOrders(), setSaleProductOrders(), appendSaleProductOrder() and removeAllSaleProductOrders()
    */
    void removeSaleProductOrder(SaleProductOrder *saleProductOrder);

    //! Set SaleOrder's receipt.
    /*!
      \param receipt SaleOrder's receipt
      \sa getReceipt()
    */
    void setReceipt(QString receipt);

    //! Set SaleOrder's date.
    /*!
      \param date SaleOrder's date
      \sa getDate()
    */
    void setDate(QDateTime date);

    //! Set SaleOrder's payment condition. This method sets in how many times the total value was divided.
    /*!
      \param paymentCondition SaleOrder's receipt
      \sa getPaymentCondition()
    */
    void setPaymentCondition(int paymentCondition);

    //! Set SaleOrder's payment form. If the payment will be done with bank ticket, cache, etc.
    /*!
      \param paymentForm SaleOrder's payment form
      \sa getPaymentForm() and getPaymentFormName()
    */
    void setPaymentForm(Utilities::PaymentForm paymentForm);

    //! Set SaleOrder's discount.
    /*!
      \param discount SaleOrder's discount
      \sa getDiscount()
    */
    void setDiscount(double discount);

    //! Set SaleOrder's observation. Something the user want to tell about this sale order.
    /*!
      \param observation SaleOrder's observation
      \sa getObservation()
    */
    void setObservation(QString observation);

    //! Set SaleOrder's value paid.
    /*!
      \param valuePaid SaleOrder's value paid
      \sa getValuePaid()
    */
    void setValuePaid(double valuePaid);

    //! Set SaleOrder's customer id.
    /*!
      \param customerId SaleOrder's customer id
      \sa getCustomerId()
    */
    void setCustomerId(QString customerId);

private:
    int id;
    QList<SaleProductOrder*> *saleProductOrders;
    QString receipt;
    QDateTime date;
    int paymentCondition; // Number of payments to get the total amount paid
    Utilities::PaymentForm paymentForm;
    double discount;
    QString observation;
    double valuePaid;
    QString customerId;

signals:

public slots:

};

#endif // SALESORDER_H
