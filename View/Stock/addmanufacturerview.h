#ifndef ADDMANUFACTURERVIEW_H
#define ADDMANUFACTURERVIEW_H

#include <QWidget>
#include "manufacturerslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddManufacturerView;
}

//!  View for adding/updating manufaturer
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating manufaturer.
*/
class AddManufacturerView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of Manufacturer. When creating a new manufacturer, use this constructor.
    */
    explicit AddManufacturerView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of Manufacturer. When editing manufacturer use this constructor.
    */
    explicit AddManufacturerView(Manufacturer *manufacturer, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddManufacturerView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddManufacturerView *ui;
    IMainWindow *parentMainWindow;
    ManufacturersListView *parent;
    Manufacturer *editingManufacturer;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:
    //! Proceed to add manufacturer
    /*!
      This slot is called to proceed with the inclusion of the manufacturer, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddManufacturer();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddManufacturer()
    */
    void hideAndClearFieldsData();
};

#endif // ADDMANUFACTURERVIEW_H
