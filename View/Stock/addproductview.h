#ifndef ADDPRODUCTVIEW_H
#define ADDPRODUCTVIEW_H

#include <QWidget>

#include "productslistview.h"
#include "productcategorycontroller.h"
#include "manufacturercontroller.h"
#include "providercontroller.h"
#include "csticmscontroller.h"
#include "cstipicontroller.h"
#include "cstpiscontroller.h"
#include "cstcofinscontroller.h"
#include "taxratecontroller.h"
#include "imainwindow.h"
#include "cfopslistview.h"

namespace Ui {
    class AddProductView;
}

//!  View for adding/updating product
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating product.
*/
class AddProductView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of Product. When creating a new Product, use this constructor.
    */
    explicit AddProductView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of Product. When editing product use this constructor.
    */
    explicit AddProductView(Product *product, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddProductView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    Ui::AddProductView *ui;
    IMainWindow *parentMainWindow;
    ProductsListView *parent;
    Product *editingProduct;

    ProductCategoryController *productCategoryController;
    ManufacturerController *manufacturerController;
    ProviderController *providerController;

    CfopsListView *cfopsListView;
    Cfop *chosenCfop;

    CstIcmsController *cstIcmsController;
    CstIpiController *cstIpiController;
    CstPisController *cstPisController;
    CstCofinsController *cstCofinsController;

    TaxRateController *taxRateController;

    void init();

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add product
    /*!
      This slot is called to proceed with the inclusion of the product, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddProduct();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddProduct()
    */
    void hideAndClearFieldsData();

    //! Choose a cfop
    /*!
      This slot opens an window to let user choose a cfop
      \sa proceedToAddProduct() and hideAndClearFieldsData()
    */
    void openCfopsWindow();

    //! Cfop chosen
    /*!
      This slot is called when a cfop is chosen
    */
    void onCfopChosen();
};

#endif // ADDPRODUCTVIEW_H
