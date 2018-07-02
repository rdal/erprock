#ifndef MANUFACTURERSLISTVIEW_H
#define MANUFACTURERSLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "manufacturercontroller.h"

namespace Ui {
    class ManufacturersListView;
}

//!  View for listing manufacturers
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing manufacturers.
*/
class ManufacturersListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of ManufacturersListView.
    */
    explicit ManufacturersListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ManufacturersListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all manufacturers.
    /*!
    * This method retrieves all manufacturers from database, and show them in a grid.
    */
    void listManufacturers();

public slots:

    //! Add new manufacturer.
    /*!
    * This slot gets called when user clicks on "Add new manufacturer" button.
    */
    void onAddNewManufacturer();

    //! Edit manufacturer.
    /*!
    * This slot gets called when user clicks on "Edit manufacturer" button.
    */
    void onEditManufacturer();

    //! Remove manufacturer.
    /*!
    * This slot gets called when user clicks on "Remove manufacturer" button.
    */
    void onRemoveManufacturer();

private:
    Ui::ManufacturersListView *ui;
    IMainWindow *parentMainWindow;
    ManufacturerController *manufacturerController;
};

#endif // MANUFACTURERSLISTVIEW_H
