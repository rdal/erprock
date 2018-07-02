#ifndef ADDPURCHASESORDERVIEW_H
#define ADDPURCHASESORDERVIEW_H

#include <QWidget>

#include "purchasesorderslistview.h"
#include "providercontroller.h"

namespace Ui {
    class AddPurchasesOrderView;
}

//!  View for adding/updating purchases orders
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating purchases orders.
*/
class AddPurchasesOrderView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddPurchasesOrderView. When creating a new purchases order, use this constructor.
    */
    explicit AddPurchasesOrderView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddPurchasesOrderView. When editing purchases order use this constructor.
    */
    explicit AddPurchasesOrderView(PurchasesOrder *purchasesOrder, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddPurchasesOrderView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    void listPurchaseProductOrders();

    //! Updates the purchase product order's list
    /*!
      Add a new purchase product order to the items list
      \param purchaseProductOrder The new purchase product order to be added
    */
    void appendPurchaseProductOrder(PurchaseProductOrder *purchaseProductOrder);

private:
    void init();

    Ui::AddPurchasesOrderView *ui;
    IMainWindow *parentMainWindow;
    PurchasesOrdersListView *parent;
    PurchasesOrder *editingPurchasesOrder;
    PurchasesOrderController *purchasesOrderController;
    ProviderController *providerController;

    QList <PurchaseProductOrder*> *purchaseProductOrders;

    double totalValue;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add purchases order
    /*!
      This slot is called to proceed with the inclusion of the purchases order, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddPurchasesOrder();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddPurchasesOrder()
    */
    void hideAndClearFieldsData();

    void onAddNewPurchaseProductOrder();

    void onEditPurchaseProductOrder();

    void onRemovePurchaseProductOrder();

    void onCargoValueChanged(double val);
};

#endif // ADDPURCHASESORDERVIEW_H
