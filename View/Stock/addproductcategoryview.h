#ifndef ADDPRODUCTCATEGORYVIEW_H
#define ADDPRODUCTCATEGORYVIEW_H

#include <QWidget>
#include "productcategorieslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddProductCategoryView;
}

//!  View for adding/updating product category
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating product category.
*/
class AddProductCategoryView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddProductCategoryView. When creating a new ProductCategory, use this constructor.
    */
    explicit AddProductCategoryView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddProductCategoryView. When editing product category use this constructor.
    */
    explicit AddProductCategoryView(ProductCategory *productCategory, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddProductCategoryView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddProductCategoryView *ui;
    IMainWindow *parentMainWindow;
    ProductCategoriesListView *parent;
    ProductCategory *editingProductCategory;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add product category
    /*!
      This slot is called to proceed with the inclusion of the product category, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddProductCategory();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddProductCategory()
    */
    void hideAndClearFieldsData();
};

#endif // ADDPRODUCTCATEGORYVIEW_H
