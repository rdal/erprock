#ifndef ADDSALESORDERVIEW_H
#define ADDSALESORDERVIEW_H

#include <QWidget>

#include "salesorderslistview.h"
#include "customercontroller.h"
#include "pricecontroller.h"

namespace Ui {
    class AddSalesOrderView;
}

//!  View for adding/updating sales orders
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating sales orders.
*/
class AddSalesOrderView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddSalesOrderView. When creating a new sales order, use this constructor.
    */
    explicit AddSalesOrderView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddSalesOrderView. When editing sales order use this constructor.
    */
    explicit AddSalesOrderView(SalesOrder *salesOrder, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddSalesOrderView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    void listSaleProductOrders();

    //! Updates the sale product order's list
    /*!
      Add a new sale product order to the items list
      \param saleProductOrder The new sale product order to be added
    */
    void appendSaleProductOrder(SaleProductOrder *saleProductOrder);

private:
    void init();

    Ui::AddSalesOrderView *ui;
    IMainWindow *parentMainWindow;
    SalesOrdersListView *parent;
    SalesOrder *editingSalesOrder;
    CustomerController *customerController;
    SalesOrderController *salesOrderController;
    PriceController *priceController;

    QList <SaleProductOrder*> *saleProductOrders;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add sales order
    /*!
      This slot is called to proceed with the inclusion of the sales order, into database.
      \sa hideAndClearFieldsData() and showPhysicalCustomersList()
    */
    void proceedToAddSalesOrder();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddSalesOrder() and showPhysicalCustomersList()
    */
    void hideAndClearFieldsData();

    //! Updates the physical customer's list
    /*!
      When the physical customers radio button is toggled, we check if it is on or off, depending on the value,
      we load up the list of physical customers
      \param checked Tells if the button is checked or not
      \sa proceedToAddSalesOrder() and hideAndClearFieldsData()
    */
    void showPhysicalCustomersList(bool checked);

    //! Updates the enterprise customer's list
    /*!
      When the enterprise customers radio button is toggled, we check if it is on or off, depending on the value,
      we load up the list of enterprise customers
      \param checked Tells if the button is checked or not
      \sa proceedToAddSalesOrder() and hideAndClearFieldsData()
    */
    void showEnterpriseCustomersList(bool checked);

    void onAddNewSaleProductOrder();

    void onEditSaleProductOrder();

    void onRemoveSaleProductOrder();
};

#endif // ADDSALESORDERVIEW_H
