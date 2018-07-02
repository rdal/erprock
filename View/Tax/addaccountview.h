#ifndef ADDACCOUNTVIEW_H
#define ADDACCOUNTVIEW_H

#include <QWidget>
#include "accountslistview.h"
#include "imainwindow.h"

namespace Ui {
class AddAccountView;
}

//!  View for adding/editing an account
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/editing an account.
*/
class AddAccountView : public QWidget
{
    Q_OBJECT
    
public:

    //! Default constructor.
    /*!
    * Create a new instance of Account. When creating a new Account, use this constructor.
    */
    explicit AddAccountView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of Account. When editing account use this constructor.
    */
    explicit AddAccountView(Account *account, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddAccountView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);
private:
    bool isCodeFormatValid(QString code);
    void init();

    Ui::AddAccountView *ui;
    IMainWindow *parentMainWindow;
    AccountsListView *parent;
    Account *editingAccount;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add account
    /*!
      This slot is called to proceed with the inclusion of the account, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddAccount();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddAccount()
    */
    void hideAndClearFieldsData();

    //! Formats the code for accounts format
    /*!
      This slot is called to format the code accordingly to the accounts format.
    */
    void formatAccountCode(QString text);

    //! Changes the text field mask code
    /*!
      This slot is called to change the mask code of the input text field, accordingly with the parent account.
    */
    void changeMaskCode(int index);

    void adjustCodeLineEditCursor(QString txt);

};

#endif // ADDACCOUNTVIEW_H
