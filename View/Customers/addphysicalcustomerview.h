#ifndef ADDPHYSICALCUSTOMERVIEW_H
#define ADDPHYSICALCUSTOMERVIEW_H

#include <QWidget>
#include "customerslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddPhysicalCustomerView;
}

//!  View for adding/updating physical customer
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating physical customer.
*/
class AddPhysicalCustomerView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of PhysicalCustomer. When creating a new physical customer, use this constructor.
    */
    explicit AddPhysicalCustomerView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of EnterpriseCustomer. When editing enterprise customer use this constructor.
    */
    explicit AddPhysicalCustomerView(PhysicalCustomer *physicalCustomer, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddPhysicalCustomerView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddPhysicalCustomerView *ui;
    IMainWindow *parentMainWindow;
    CustomersListView *parent;
    PhysicalCustomer *editingPhysicalCustomer;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:
    //! Proceed to add physical customer
    /*!
      This slot is called to proceed with the inclusion of the physical customer, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddPhysicalCustomer();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddPhysicalCustomer()
    */
    void hideAndClearFieldsData();
};

#endif // ADDPHYSICALCUSTOMERVIEW_H
