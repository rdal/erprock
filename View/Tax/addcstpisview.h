#ifndef ADDCSTPISVIEW_H
#define ADDCSTPISVIEW_H

#include <QWidget>
#include "cstpisslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddCstPisView;
}

//!  View for adding/updating CST PIS
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating CST PIS.
*/
class AddCstPisView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddCstPisView. When creating a new CST PIS, use this constructor.
    */
    explicit AddCstPisView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddCstPisView. When editing CST PIS use this constructor.
    */
    explicit AddCstPisView(CstPis *cstPis, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddCstPisView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddCstPisView *ui;
    IMainWindow *parentMainWindow;
    CstPissListView *parent;
    CstPis *editingCstPis;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add CST PIS
    /*!
      This slot is called to proceed with the inclusion of the CST PIS, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddCstPis();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddCstPis()
    */
    void hideAndClearFieldsData();
};

#endif // ADDCSTPISVIEW_H
