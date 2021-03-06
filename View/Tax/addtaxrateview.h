#ifndef ADDTAXRATEVIEW_H
#define ADDTAXRATEVIEW_H

#include <QWidget>
#include "taxrateslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddTaxRateView;
}

//!  View for adding/updating tax rates
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating tax rates.
*/
class AddTaxRateView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddTaxRateView. When creating a new tax rate, use this constructor.
    */
    explicit AddTaxRateView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddTaxRateView. When editing tax rate use this constructor.
    */
    explicit AddTaxRateView(TaxRate *taxRate, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddTaxRateView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddTaxRateView *ui;
    IMainWindow *parentMainWindow;
    TaxRatesListView *parent;
    TaxRate *editingTaxRate;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add tax rate
    /*!
      This slot is called to proceed with the inclusion of the tax rate, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddTaxRate();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddTaxRate()
    */
    void hideAndClearFieldsData();
};

#endif // ADDTAXRATEVIEW_H
