#ifndef PRODUCTSLISTVIEW_H
#define PRODUCTSLISTVIEW_H

#include <QWidget>
#include "productcontroller.h"
#include "productcategorycontroller.h"
#include "manufacturercontroller.h"
#include "imainwindow.h"

namespace Ui {
    class ProductsListView;
}

//!  View for listing products
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing products.
*/
class ProductsListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of ProductsListView.
    */
    explicit ProductsListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ProductsListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! Set Window Mode
    /*!
      \param windowMode Window mode
      \sa setProductObjectChosen()
    */
    void setWindowMode(Utilities::ItemsListWindowMode windowMode);

    //! List all products.
    /*!
    * This method retrieves all products from database, and show them in a grid.
    */
    void listProducts();

    //! Set chosen Object.
    /*!
    * This method sets a given Product Object as the chosen one.
    * CHOOSE_PRODUCT Window Mode must be set.
    * \sa setWindowMode()
    */
    void setProductObjectChosen(Product *&localChosenProduct);

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close.
    */
    void aboutToClose();

public slots:

    //! Add new product.
    /*!
    * This slot gets called when user clicks on "Add new product" button.
    */
    void onAddNewProduct();

    //! Edit product.
    /*!
    * This slot gets called when user clicks on "Edit product" button.
    */
    void onEditProduct();

    //! Remove product.
    /*!
    * This slot gets called when user clicks on "Remove product" button.
    */
    void onRemoveProduct();

    //! Choose product.
    /*!
    * This slot gets called when user clicks twice on a certain product.
    * CHOOSE_PRODUCT Window Mode must be set to get this behavior
    */
    void onChooseProduct();

private:
    Ui::ProductsListView *ui;
    IMainWindow *parentMainWindow;
    ProductController *productController;
    ProductCategoryController *productCategoryController;
    ManufacturerController *manufacturerController;

    Utilities::ItemsListWindowMode windowMode;
    Product *chosenProduct;
};

#endif // PRODUCTSLISTVIEW_H
