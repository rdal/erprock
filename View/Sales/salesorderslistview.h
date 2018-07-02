#ifndef SALESORDERSLISTVIEW_H
#define SALESORDERSLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "salesordercontroller.h"

namespace Ui {
    class SalesOrdersListView;
}

//!  View for sales order management
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for sales order management.
*/
class SalesOrdersListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of SalesOrdersListView.
    */
    explicit SalesOrdersListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~SalesOrdersListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all prices.
    /*!
    * This method retrieves all sales orders from database, and show them in a grid.
    */
    void listSalesOrders();

public slots:

    //! Add new sales order.
    /*!
    * This slot gets called when user clicks on "Add new sales order" button.
    */
    void onAddNewSalesOrder();

    //! Edit sales order.
    /*!
    * This slot gets called when user clicks on "Edit sales order" button.
    */
    void onEditSalesOrder();

    //! Remove sales order.
    /*!
    * This slot gets called when user clicks on "Remove sales order" button.
    */
    void onRemoveSalesOrder();


private:
    Ui::SalesOrdersListView *ui;
    IMainWindow *parentMainWindow;
    SalesOrderController *salesOrderController;
};

#endif // SALESORDERSLISTVIEW_H
