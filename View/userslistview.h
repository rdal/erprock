#ifndef USERSLISTVIEW_H
#define USERSLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"

#include "usercontroller.h"

namespace Ui {
    class UsersListView;
}

//!  View for user management
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for user management.
*/
class UsersListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of UsersListView.
    */
    explicit UsersListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~UsersListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all users.
    /*!
    * This method retrieves all users from database, and show them in a grid.
    */
    void listUsers();

public slots:

    //! Add new user.
    /*!
    * This slot gets called when user clicks on "Add new user" button.
    */
    void onAddNewUser();

    //! Edit user.
    /*!
    * This slot gets called when user clicks on "Edit user" button.
    */
    void onEditUser();

    //! Remove user.
    /*!
    * This slot gets called when user clicks on "Remove user" button.
    */
    void onRemoveUser();

private:

    Ui::UsersListView *ui;
    IMainWindow *parentMainWindow;
    UserController *userController;
};

#endif // USERSLISTVIEW_H
