#ifndef ADDSALEPRODUCTORDERVIEW_H
#define ADDSALEPRODUCTORDERVIEW_H

#include <QWidget>

#include "addsalesorderview.h"
#include "productslistview.h"

namespace Ui {
    class AddSaleProductOrderView;
}

//!  View for adding/updating sale product orders
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating sale product orders.
*/
class AddSaleProductOrderView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddSaleProductOrderView. When creating a new sale product order, use this constructor.
    */
    explicit AddSaleProductOrderView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddSaleProductOrderView. When editing sale product order use this constructor.
    */
    explicit AddSaleProductOrderView(SaleProductOrder *saleProductOrder, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddSaleProductOrderView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddSaleProductOrderView *ui;
    IMainWindow *parentMainWindow;
    AddSalesOrderView *parent;
    SaleProductOrder *editingSaleProductOrder;

    ProductsListView *productsListView;
    Product *chosenProduct;
    Product *previousChosenProduct;
    PriceController *priceController;

    QList<SaleProductOrder*> *saleProductOrders;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add sale product order
    /*!
      This slot is called to proceed with the inclusion of the sale product order, into database.
      \sa hideAndClearFieldsData() and openProductsWindow()
    */
    void proceedToAddSaleProductOrder();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddSaleProductOrder() and openProductsWindow()
    */
    void hideAndClearFieldsData();

    //! Choose a product
    /*!
      This slot opens an window to let user choose a product
      \sa proceedToAddSaleProductOrder() and hideAndClearFieldsData()
    */
    void openProductsWindow();

    //! Product chosen
    /*!
      This slot is called when a product is chosen
    */
    void onProductChosen();
};

#endif // ADDSALEPRODUCTORDERVIEW_H
