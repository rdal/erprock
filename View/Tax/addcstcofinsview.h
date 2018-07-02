#ifndef ADDCSTCOFINSVIEW_H
#define ADDCSTCOFINSVIEW_H

#include <QWidget>
#include "cstcofinsslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddCstCofinsView;
}

//!  View for adding/updating CST COFINS
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating CST COFINS.
*/
class AddCstCofinsView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddCstCofinsView. When creating a new CST COFINS, use this constructor.
    */
    explicit AddCstCofinsView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddCstCofinsView. When editing CST COFINS use this constructor.
    */
    explicit AddCstCofinsView(CstCofins *cstCofins, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddCstCofinsView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddCstCofinsView *ui;
    IMainWindow *parentMainWindow;
    CstCofinssListView *parent;
    CstCofins *editingCstCofins;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add CST COFINS
    /*!
      This slot is called to proceed with the inclusion of the CST COFINS, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddCstCofins();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddCstCofins()
    */
    void hideAndClearFieldsData();
};

#endif // ADDCSTCOFINSVIEW_H
