#ifndef ADDCSTIPIVIEW_H
#define ADDCSTIPIVIEW_H

#include <QWidget>
#include "cstipislistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddCstIpiView;
}

//!  View for adding/updating CST IPI
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating CST IPI.
*/
class AddCstIpiView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddCstIpiView. When creating a new CST IPI, use this constructor.
    */
    explicit AddCstIpiView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddCstIpiView. When editing CST IPI use this constructor.
    */
    explicit AddCstIpiView(CstIpi *cstIpi, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddCstIpiView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddCstIpiView *ui;
    IMainWindow *parentMainWindow;
    CstIpisListView *parent;
    CstIpi *editingCstIpi;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add CST IPI
    /*!
      This slot is called to proceed with the inclusion of the CST IPI, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddCstIpi();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddCstIpi()
    */
    void hideAndClearFieldsData();
};

#endif // ADDCSTIPIVIEW_H
