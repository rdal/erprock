#ifndef ACCOUNTSLISTVIEW_H
#define ACCOUNTSLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"

#include "accountscontroller.h"

namespace Ui {
class AccountsListView;
}

//!  View for accounts management
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for accounts management.
*/
class AccountsListView : public QWidget
{
    Q_OBJECT
    
public:

    //! Default constructor.
    /*!
    * Create a new instance of AccountsListView.
    */
    explicit AccountsListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AccountsListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all accounts.
    /*!
    * This method retrieves all accounts from database, and show them in a grid.
    */
    void listAccounts();

public slots:

    //! Add new account.
    /*!
    * This slot gets called when account clicks on "Add new account" button.
    */
    void onAddNewAccount();

    //! Edit account.
    /*!
    * This slot gets called when account clicks on "Edit account" button.
    */
    void onEditAccount();

    //! Remove account.
    /*!
    * This slot gets called when account clicks on "Remove account" button.
    */
    void onRemoveAccount();
    
private:
    Ui::AccountsListView *ui;
    IMainWindow *parentMainWindow;
    AccountsController *accountsController;
};

#endif // ACCOUNTSLISTVIEW_H
