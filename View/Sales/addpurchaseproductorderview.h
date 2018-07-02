#ifndef ADDPURCHASEPRODUCTORDERVIEW_H
#define ADDPURCHASEPRODUCTORDERVIEW_H

#include <QWidget>

#include "addpurchasesorderview.h"
#include "productslistview.h"
#include "productorigincontroller.h"
#include "csticmscontroller.h"
#include "cstipicontroller.h"
#include "cstpiscontroller.h"
#include "cstcofinscontroller.h"
#include "taxratecontroller.h"
#include "cfopslistview.h"

namespace Ui {
    class AddPurchaseProductOrderView;
}

//!  View for adding/updating purchase product orders
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating purchase product orders.
*/
class AddPurchaseProductOrderView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddPurchaseProductOrderView. When creating a new purchase product order, use this constructor.
    */
    explicit AddPurchaseProductOrderView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddPurchaseProductOrderView. When editing purchase product order use this constructor.
    */
    explicit AddPurchaseProductOrderView(PurchaseProductOrder *purchaseProductOrder, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddPurchaseProductOrderView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddPurchaseProductOrderView *ui;
    IMainWindow *parentMainWindow;
    AddPurchasesOrderView *parent;
    PurchaseProductOrder *editingPurchaseProductOrder;

    ProductsListView *productsListView;
    Product *chosenProduct;
    Product *previousChosenProduct;

    QList<PurchaseProductOrder*> *purchaseProductOrders;

    ProductOriginController *productOriginController;
    CstIcmsController *cstIcmsController;
    CstIpiController *cstIpiController;
    CstPisController *cstPisController;
    CstCofinsController *cstCofinsController;
    TaxRateController *taxRateController;

    CfopsListView *cfopsListView;
    Cfop *chosenCfop;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add purchase product order
    /*!
      This slot is called to proceed with the inclusion of the purchase product order, into database.
      \sa hideAndClearFieldsData() and openProductsWindow()
    */
    void proceedToAddPurchaseProductOrder();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddPurchaseProductOrder() and openProductsWindow()
    */
    void hideAndClearFieldsData();

    //! Choose a product
    /*!
      This slot opens an window to let user choose a product
      \sa proceedToAddPurchaseProductOrder() and hideAndClearFieldsData()
    */
    void openProductsWindow();

    //! Product chosen
    /*!
      This slot is called when a product is chosen
    */
    void onProductChosen();

    //! Choose a cfop
    /*!
      This slot opens an window to let user choose a cfop
      \sa onCfopChosen()
    */
    void openCfopsWindow();

    //! Cfop chosen
    /*!
      This slot is called when a cfop is chosen
      \sa openCfopsWindow()
    */
    void onCfopChosen();
};

#endif // ADDPURCHASEPRODUCTORDERVIEW_H
