#ifndef SALESORDERCONTROLLER_H
#define SALESORDERCONTROLLER_H

#include <QObject>
#include "databasecontroller.h"
#include "utilities.h"

//!  Controller for Sales Orders
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for Sales Orders management.
*/
class SalesOrderController : public QObject
{
    Q_OBJECT
public:

    //! Default constructor.
    /*!
    * Create a new instance of SalesOrderController.
    */
    explicit SalesOrderController(QObject *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~SalesOrderController();

    //! Creates a new instance of SaleProductOrder, with the productCode and its quantity.
    /*!
      Returns the a instance of SaleProductOrder
      \return Returns the new instance of SaleProductOrder
    */
    SaleProductOrder *createNewSaleProductOrder(QString productCode, int quantity);

    /*!
    Beforing adding a sales order, this method checks if there is already a sales order with that name,
    if his name has less than 50 characters, etc.
      \param salesOrder The SalesOrder object to be added.
      \param receipt The original receipt, in case it is being updated
      \return Returns the Status Control of the operation.
      \sa removeSalesOrder(), getSalesOrderById(), getSalesOrderByReceipt(), getSalesOrderByDateRange() and getSalesOrders()
    */
    Utilities::StatusControl storeSalesOrder(SalesOrder *salesOrder, QString receipt="");

//    /*!
//    Beforing updating a sales order, this method checks if there is a sales order with that name,
//    and if his name has less than 50 characters.
//      \param salesOrder The SalesOrder object to be updated.
//      \return Returns the Status Control of the operation.
//      \sa addSalesOrder(), removeSalesOrder(), getSalesOrderById(), getSalesOrderByReceipt(), getSalesOrderByDateRange() and getSalesOrders()
//    */
//    Utilities::StatusControl updateSalesOrder(SalesOrder *salesOrder);

    /*!
    Remove a sales order by its id.
      \param id The id whose sales order will be removed.
      \param removeRelatedEntries If it needs to remove the related entries.
      \return Returns the Status Control of the operation.
      \sa addSalesOrder(), getSalesOrderById(), getSalesOrderByReceipt(), getSalesOrderByDateRange() and getSalesOrders()
    */
    Utilities::StatusControl removeSalesOrder(int id, bool removeRelatedEntries = false);

    /*!
    Get a sales order by its id.
      \param id The SalesOrder's id.
      \return Returns the sales order object associated with the given id.
      \sa addSalesOrder(), removeSalesOrder(), getSalesOrderByReceipt(), getSalesOrderByDateRange() and getSalesOrders()
    */
    SalesOrder *getSalesOrderById(int id);

    /*!
    Get a sales order by its receipt.
      \param receipt The SalesOrder's receipt.
      \return Returns the sales order object associated with the given receipt.
      \sa addSalesOrder(), removeSalesOrder(), getSalesOrderById(), getSalesOrderByDateRange() and getSalesOrders()
    */
    SalesOrder *getSalesOrderByReceipt(QString receipt);

    /*!
    Get all sales orders by a date range.
      \param startDate The start SalesOrder's date range.
      \param endDate The end SalesOrder's date range.
      \return Returns the sales orders objects associated with the given date range.
      \sa addSalesOrder(), removeSalesOrder(), getSalesOrderById(), getSalesOrderByReceipt(), getSalesOrderByDateRange() and getSalesOrders()
    */
    QList<SalesOrder*> *getSalesOrderByDateRange(QDateTime startDate, QDateTime endDate);

    /*!
    This method returns all the sales orders that were previously stored at database.
      \return Returns all stored sales orders.
      \sa addSalesOrder(), removeSalesOrder(), getSalesOrderById(), getSalesOrderByReceipt() and getSalesOrderByDateRange()
    */
    QList<SalesOrder*> *getSalesOrders();

    QList<SaleProductOrder*> *getSaleProductOrdersBySalesOrderId(int id);

    SaleProductOrder *getSaleProductOrderById(int id);

private:

    DatabaseController *dbController;

signals:

public slots:

};

#endif // SALESORDERCONTROLLER_H
