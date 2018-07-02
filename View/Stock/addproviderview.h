#ifndef ADDPROVIDERVIEW_H
#define ADDPROVIDERVIEW_H

#include <QWidget>
#include "providerslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddProviderView;
}

//!  View for adding/updating provider
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating provider.
*/
class AddProviderView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddProviderView. When creating a new provider, use this constructor.
    */
    explicit AddProviderView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddProviderView. When editing provider use this constructor.
    */
    explicit AddProviderView(Provider *provider, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddProviderView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddProviderView *ui;
    IMainWindow *parentMainWindow;
    ProvidersListView *parent;
    Provider *editingProvider;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:
    //! Proceed to add provider
    /*!
      This slot is called to proceed with the inclusion of the provider, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddProvider();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddProvider()
    */
    void hideAndClearFieldsData();
};

#endif // ADDPROVIDERVIEW_H
