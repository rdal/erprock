#ifndef PROVIDERSLISTVIEW_H
#define PROVIDERSLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "providercontroller.h"

namespace Ui {
    class ProvidersListView;
}

//!  View for listing providers
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing providers.
*/
class ProvidersListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of ProvidersListView.
    */
    explicit ProvidersListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ProvidersListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all providers.
    /*!
    * This method retrieves all providers from database, and show them in a grid.
    */
    void listProviders();

public slots:

    //! Add new provider.
    /*!
    * This slot gets called when user clicks on "Add new provider" button.
    */
    void onAddNewProvider();

    //! Edit provider.
    /*!
    * This slot gets called when user clicks on "Edit provider" button.
    */
    void onEditProvider();

    //! Remove provider.
    /*!
    * This slot gets called when user clicks on "Remove provider" button.
    */
    void onRemoveProvider();

private:
    Ui::ProvidersListView *ui;
    IMainWindow *parentMainWindow;
    ProviderController *providerController;
};

#endif // PROVIDERSLISTVIEW_H
