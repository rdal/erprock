#ifndef ADDCFOPVIEW_H
#define ADDCFOPVIEW_H

#include <QWidget>
#include "cfopslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddCfopView;
}

//!  View for adding/updating cfops
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating cfops.
*/
class AddCfopView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddCfopView. When creating a new cfop, use this constructor.
    */
    explicit AddCfopView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddCfopView. When editing cfop use this constructor.
    */
    explicit AddCfopView(Cfop *cfop, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddCfopView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddCfopView *ui;
    IMainWindow *parentMainWindow;
    CfopsListView *parent;
    Cfop *editingCfop;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add cfop
    /*!
      This slot is called to proceed with the inclusion of the cfop, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddCfop();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddCfop()
    */
    void hideAndClearFieldsData();
};

#endif // ADDCFOPVIEW_H
