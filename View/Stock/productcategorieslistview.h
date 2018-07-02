#ifndef PRODUCTCATEGORIESLISTVIEW_H
#define PRODUCTCATEGORIESLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "productcategorycontroller.h"

namespace Ui {
    class ProductCategoriesListView;
}

//!  View for listing product categories
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing product categories.
*/
class ProductCategoriesListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of ProductCategoriesListView.
    */
    explicit ProductCategoriesListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ProductCategoriesListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all providers.
    /*!
    * This method retrieves all product categories from database, and show them in a grid.
    */
    void listProductCategories();

public slots:

    //! Add new product category.
    /*!
    * This slot gets called when user clicks on "Add new product category" button.
    */
    void onAddNewProductCategory();

    //! Edit product category.
    /*!
    * This slot gets called when user clicks on "Edit product category" button.
    */
    void onEditProductCategory();

    //! Remove product category.
    /*!
    * This slot gets called when user clicks on "Remove product category" button.
    */
    void onRemoveProductCategory();

private:
    Ui::ProductCategoriesListView *ui;
    IMainWindow *parentMainWindow;
    ProductCategoryController *productCategoryController;
};

#endif // PRODUCTCATEGORIESLISTVIEW_H
