#ifndef ADDENTERPRISECUSTOMERVIEW_H
#define ADDENTERPRISECUSTOMERVIEW_H

#include <QWidget>
#include "customerslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddEnterpriseCustomerView;
}

//!  View for adding/updating enterprise customer
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating enterprise customer.
*/
class AddEnterpriseCustomerView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of EnterpriseCustomer. When creating a new enterprise customer, use this constructor.
    */
    explicit AddEnterpriseCustomerView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of EnterpriseCustomer. When editing enterprise customer use this constructor.
    */
    explicit AddEnterpriseCustomerView(EnterpriseCustomer *enterpriseCustomer, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddEnterpriseCustomerView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddEnterpriseCustomerView *ui;
    IMainWindow *parentMainWindow;
    CustomersListView *parent;
    EnterpriseCustomer *editingEnterpriseCustomer;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:
    //! Proceed to add enterprise customer
    /*!
      This slot is called to proceed with the inclusion of the enterprise customer, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddEnterpriseCustomer();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddEnterpriseCustomer()
    */
    void hideAndClearFieldsData();
};

#endif // ADDENTERPRISECUSTOMERVIEW_H
