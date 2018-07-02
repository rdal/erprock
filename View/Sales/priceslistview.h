#ifndef PRICESLISTVIEW_H
#define PRICESLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"

#include "pricecontroller.h"

namespace Ui {
    class PricesListView;
}

//!  View for price management
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for price management.
*/
class PricesListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of PricesListView.
    */
    explicit PricesListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~PricesListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all prices.
    /*!
    * This method retrieves all prices from database, and show them in a grid.
    */
    void listPrices();

public slots:

    //! Add new price.
    /*!
    * This slot gets called when user clicks on "Add new price" button.
    */
    void onAddNewPrice();

    //! Edit price.
    /*!
    * This slot gets called when user clicks on "Edit price" button.
    */
    void onEditPrice();

    //! Remove price.
    /*!
    * This slot gets called when user clicks on "Remove price" button.
    */
    void onRemovePrice();

private:
    Ui::PricesListView *ui;
    IMainWindow *parentMainWindow;
    PriceController *priceController;
};

#endif // PRICESLISTVIEW_H
