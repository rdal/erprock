#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

#include "usercontroller.h"
#include "imainwindow.h"

namespace Ui {
    class Login;
}

//!  View for logging users in
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for logging an user into the software.
*/
class Login : public QDialog
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of Login.
    */
    explicit Login(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~Login();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    UserController *userController;
    IMainWindow *parentMainWindow;

public slots:

    //! Processes login.
    /*!
    * This slot gets called when an user clicks on a button that starts the login process.
    */
    void processLogin();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
