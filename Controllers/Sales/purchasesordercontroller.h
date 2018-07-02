#ifndef PURCHASESORDERCONTROLLER_H
#define PURCHASESORDERCONTROLLER_H

#include <QObject>

#include "databasecontroller.h"

//!  Controller for Purchases Orders
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for Purchases Orders management.
*/
class PurchasesOrderController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of PurchasesOrderController.
    */
    explicit PurchasesOrderController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~PurchasesOrderController();

//    //! Creates a new instance of PurchaseProductOrder, with the productCode and its quantity.
//    /*!
//      \param productCode The PurchasesOrder's product code, to be added.
//      \param quantity The PurchasesOrder's product quantity
//      \param productOriginCode The PurchasesOrder's product origin
//      \param unitPrice The PurchasesOrder's product price
//      Returns the a instance of PurchaseProductOrder
//      \return Returns the new instance of PurchaseProductOrder
//    */
//    PurchaseProductOrder *createNewPurchaseProductOrder(QString productCode, int quantity, QChar productOriginCode, double unitPrice);

    /*!
    Beforing adding a purchases order, this method checks if there is already a purchases order with that receipt,
    and provider id.
      \param purchasesOrder The PurchasesOrder object to be added.
      \param receipt The original receipt, in case it is being updated
      \return Returns the Status Control of the operation.
      \sa removePurchasesOrder(), getPurchasesOrderById(), getPurchasesOrderByReceipt(), getPurchasesOrderByDateRange() and getPurchasesOrders()
    */
    Utilities::StatusControl storePurchasesOrder(PurchasesOrder *purchasesOrder, QString receipt="");

    /*!
    Remove a purchases order by its id.
      \param id The id whose purchases order will be removed.
      \param removeRelatedEntries If it needs to remove the related entries.
      \return Returns the Status Control of the operation.
      \sa addPurchasesOrder(), getPurchasesOrderById(), getPurchasesOrderByReceipt(), getPurchasesOrderByDateRange() and getPurchasesOrders()
    */
    Utilities::StatusControl removePurchasesOrder(int id, bool removeRelatedEntries = false);

    /*!
    Get a purchases order by its id.
      \param id The PurchasesOrder's id.
      \return Returns the purchases order object associated with the given id.
      \sa addPurchasesOrder(), removePurchasesOrder(), getPurchasesOrderByReceipt(), getPurchasesOrderByDateRange() and getPurchasesOrders()
    */
    PurchasesOrder *getPurchasesOrderById(int id);

    /*!
    Get a purchases order by its receipt.
      \param receipt The PurchasesOrder's receipt.
      \return Returns the purchases order object associated with the given receipt.
      \sa addPurchasesOrder(), removePurchasesOrder(), getPurchasesOrderById(), getPurchasesOrderByDateRange() and getPurchasesOrders()
    */
    PurchasesOrder *getPurchasesOrderByReceipt(QString receipt);

    /*!
    Get all purchases orders by a date range.
      \param startDate The start PurchasesOrder's date range.
      \param endDate The end PurchasesOrder's date range.
      \return Returns the purchases orders objects associated with the given date range.
      \sa addPurchasesOrder(), removePurchasesOrder(), getPurchasesOrderById(), getPurchasesOrderByReceipt(), getPurchasesOrderByDateRange() and getPurchasesOrders()
    */
    QList<PurchasesOrder*> *getPurchasesOrderByDateRange(QDateTime startDate, QDateTime endDate);

    /*!
    This method returns all the purchases orders that were previously stored at database.
      \return Returns all stored purchases orders.
      \sa addPurchasesOrder(), removePurchasesOrder(), getPurchasesOrderById(), getPurchasesOrderByReceipt() and getPurchasesOrderByDateRange()
    */
    QList<PurchasesOrder*> *getPurchasesOrders();

    QList<PurchaseProductOrder*> *getPurchaseProductOrdersByPurchasesOrderId(int id);

    PurchaseProductOrder *getPurchaseProductOrderById(int id);

private:

    DatabaseController *dbController;

signals:

public slots:

};

#endif // PURCHASESORDERCONTROLLER_H
