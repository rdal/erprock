#ifndef ADDPRICEVIEW_H
#define ADDPRICEVIEW_H

#include <QWidget>
#include <QMdiSubWindow>

#include "priceslistview.h"
#include "imainwindow.h"
#include "productslistview.h"

namespace Ui {
    class AddPriceView;
}

//!  View for adding/updating prices
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating prices.
*/
class AddPriceView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddPriceView. When creating a new price, use this constructor.
    */
    explicit AddPriceView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddPriceView. When editing price use this constructor.
    */
    explicit AddPriceView(Price *price, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddPriceView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddPriceView *ui;
    IMainWindow *parentMainWindow;
    PricesListView *parent;
    Price *editingPrice;

    ProductsListView *productsListView;
    Product *chosenProduct;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add price
    /*!
      This slot is called to proceed with the inclusion of the price, into database.
      \sa hideAndClearFieldsData() and openProductsWindow()
    */
    void proceedToAddPrice();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddPrice() and openProductsWindow()
    */
    void hideAndClearFieldsData();

    //! Choose a product
    /*!
      This slot opens an window to let user choose a product
      \sa proceedToAddPrice() and hideAndClearFieldsData()
    */
    void openProductsWindow();

    //! Product chosen
    /*!
      This slot is called when a product is chosen
    */
    void onProductChosen();
};

#endif // ADDPRICEVIEW_H
