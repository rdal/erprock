#ifndef ADDCSTICMSVIEW_H
#define ADDCSTICMSVIEW_H

#include <QWidget>
#include "csticmsslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddCstIcmsView;
}

//!  View for adding/updating CST ICMS
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating CST ICMS.
*/
class AddCstIcmsView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddCstIcmsView. When creating a new CST ICMS, use this constructor.
    */
    explicit AddCstIcmsView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddCstIcmsView. When editing CST ICMS use this constructor.
    */
    explicit AddCstIcmsView(CstIcms *cstIcms, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddCstIcmsView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddCstIcmsView *ui;
    IMainWindow *parentMainWindow;
    CstIcmssListView *parent;
    CstIcms *editingCstIcms;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add CST ICMS
    /*!
      This slot is called to proceed with the inclusion of the CST ICMS, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddCstIcms();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddCstIcms()
    */
    void hideAndClearFieldsData();
};

#endif // ADDCSTICMSVIEW_H
