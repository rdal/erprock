#ifndef ENTRIESLISTVIEW_H
#define ENTRIESLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "entriescontroller.h"
#include "historiescontroller.h"
#include "accountscontroller.h"
#include "storecontroller.h"

namespace Ui {
class EntriesListView;
}

//!  View for listing entries
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing entries.
*/
class EntriesListView : public QWidget
{
    Q_OBJECT
    
public:

    //! Default constructor.
    /*!
    * Create a new instance of EntriesListView.
    */
    explicit EntriesListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~EntriesListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all providers.
    /*!
    * This method retrieves all entries from database, and show them in a grid.
    */
    void listEntries();

public slots:

    //! Add new entry.
    /*!
    * This slot gets called when user clicks on "Add new entry" button.
    */
    void onAddNewEntry();

    //! Edit entry.
    /*!
    * This slot gets called when user clicks on "Edit entry" button.
    */
    void onEditEntry();

    //! Remove entry.
    /*!
    * This slot gets called when user clicks on "Remove entry" button.
    */
    void onRemoveEntry();
    
private:
    Ui::EntriesListView *ui;
    IMainWindow *parentMainWindow;
    EntriesController *entriesController;
    HistoriesController *historiesController;
    AccountsController *accountsController;
    StoreController *storeController;
};

#endif // ENTRIESLISTVIEW_H
