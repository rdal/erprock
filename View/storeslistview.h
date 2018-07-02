#ifndef STORESLISTVIEW_H
#define STORESLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "storecontroller.h"

namespace Ui {
    class StoresListView;
}

//!  View for listing stores
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing stores.
*/
class StoresListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of StoresListView.
    */
    explicit StoresListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~StoresListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all stores.
    /*!
    * This method retrieves all stores from database, and show them in a grid.
    */
    void listStores();

public slots:

    //! Add new store.
    /*!
    * This slot gets called when user clicks on "Add new store" button.
    */
    void onAddNewStore();

    //! Edit store.
    /*!
    * This slot gets called when user clicks on "Edit store" button.
    */
    void onEditStore();

    //! Remove store.
    /*!
    * This slot gets called when user clicks on "Remove store" button.
    */
    void onRemoveStore();

private:
    Ui::StoresListView *ui;
    IMainWindow *parentMainWindow;
    StoreController *storeController;
};

#endif // STORESLISTVIEW_H
