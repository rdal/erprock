#ifndef ADDUSERVIEW_H
#define ADDUSERVIEW_H

#include <QWidget>
#include "userslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddUserView;
}

//!  View for adding/editing an user
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/editing an user.
*/
class AddUserView : public QWidget
{
    Q_OBJECT

public:
    //! Default constructor.
    /*!
    * Create a new instance of User. When creating a new User, use this constructor.
    */
    explicit AddUserView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of User. When editing user use this constructor.
    */
    explicit AddUserView(User *user, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddUserView();


    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddUserView *ui;
    IMainWindow *parentMainWindow;
    UsersListView *parent;
    User *editingUser;


signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add user
    /*!
      This slot is called to proceed with the inclusion of the user, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddUser();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddUser()
    */
    void hideAndClearFieldsData();
};

#endif // ADDUSERVIEW_H
