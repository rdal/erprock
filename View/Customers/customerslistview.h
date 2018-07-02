#ifndef CUSTOMERSLISTVIEW_H
#define CUSTOMERSLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "customercontroller.h"

namespace Ui {
    class CustomersListView;
}

//!  View for adding/updating customers
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating customers.
*/
class CustomersListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of CustomersListView.
    */
    explicit CustomersListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CustomersListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all enterprise customers.
    /*!
    * This method retrieves all enterprise customers from database, and show them in a grid.
    */
    void listEnterpriseCustomers();

    //! List all physical customers.
    /*!
    * This method retrieves all physical customers from database, and show them in a grid.
    */
    void listPhysicalCustomers();

public slots:

    //! Add new enterprise customer.
    /*!
    * This slot gets called when user clicks on "Add new enterprise customer" button.
    */
    void onAddNewEnterpriseCustomer();

    //! Edit enterprise customer.
    /*!
    * This slot gets called when user clicks on "Edit enterprise customer" button.
    */
    void onEditEnterpriseCustomer();

    //! Remove enterprise customer.
    /*!
    * This slot gets called when user clicks on "Remove enterprise customer" button.
    */
    void onRemoveEnterpriseCustomer();

    //! Add new physical customer.
    /*!
    * This slot gets called when user clicks on "Add new physical customer" button.
    */
    void onAddNewPhysicalCustomer();

    //! Edit physical customer.
    /*!
    * This slot gets called when user clicks on "Edit physical customer" button.
    */
    void onEditPhysicalCustomer();

    //! Remove physical customer.
    /*!
    * This slot gets called when user clicks on "Remove physical customer" button.
    */
    void onRemovePhysicalCustomer();

private:
    Ui::CustomersListView *ui;
    IMainWindow *parentMainWindow;
    CustomerController *customerController;
};

#endif // CUSTOMERSLISTVIEW_H
