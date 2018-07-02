#ifndef TAXRATESLISTVIEW_H
#define TAXRATESLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "taxratecontroller.h"

namespace Ui {
    class TaxRatesListView;
}

//!  View for listing tax rates
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing tax rates.
*/
class TaxRatesListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of TaxRatesListView.
    */
    explicit TaxRatesListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~TaxRatesListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all providers.
    /*!
    * This method retrieves all tax rates from database, and show them in a grid.
    */
    void listTaxRates();

public slots:

    //! Add new tax rate.
    /*!
    * This slot gets called when user clicks on "Add new tax rate" button.
    */
    void onAddNewTaxRate();

    //! Edit tax rate.
    /*!
    * This slot gets called when user clicks on "Edit tax rate" button.
    */
    void onEditTaxRate();

    //! Remove tax rate.
    /*!
    * This slot gets called when user clicks on "Remove tax rate" button.
    */
    void onRemoveTaxRate();

private:
    Ui::TaxRatesListView *ui;
    IMainWindow *parentMainWindow;
    TaxRateController *taxRateController;
};

#endif // TAXRATESLISTVIEW_H
