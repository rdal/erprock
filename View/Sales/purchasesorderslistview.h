#ifndef PURCHASESORDERSLISTVIEW_H
#define PURCHASESORDERSLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "purchasesordercontroller.h"

namespace Ui {
    class PurchasesOrdersListView;
}

//!  View for purchases order management
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for purchases order management.
*/
class PurchasesOrdersListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of PurchasesOrdersListView.
    */
    explicit PurchasesOrdersListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~PurchasesOrdersListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all prices.
    /*!
    * This method retrieves all purchases orders from database, and show them in a grid.
    */
    void listPurchasesOrders();

public slots:

    //! Add new purchases order.
    /*!
    * This slot gets called when user clicks on "Add new purchases order" button.
    */
    void onAddNewPurchasesOrder();

    //! Edit purchases order.
    /*!
    * This slot gets called when user clicks on "Edit purchases order" button.
    */
    void onEditPurchasesOrder();

    //! Remove purchases order.
    /*!
    * This slot gets called when user clicks on "Remove purchases order" button.
    */
    void onRemovePurchasesOrder();

private:
    Ui::PurchasesOrdersListView *ui;
    IMainWindow *parentMainWindow;
    PurchasesOrderController *purchasesOrderController;
};

#endif // PURCHASESORDERSLISTVIEW_H
