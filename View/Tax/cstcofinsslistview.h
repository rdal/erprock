#ifndef CSTCOFINSSLISTVIEW_H
#define CSTCOFINSSLISTVIEW_H

#include <QWidget>

#include "imainwindow.h"
#include "cstcofinscontroller.h"

namespace Ui {
    class CstCofinssListView;
}

//!  View for listing cst cofins
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing cst cofins.
*/
class CstCofinssListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of CstCofinssListView.
    */
    explicit CstCofinssListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CstCofinssListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all providers.
    /*!
    * This method retrieves all cst cofins from database, and show them in a grid.
    */
    void listCstCofinss();

public slots:

    //! Add new cst cofins.
    /*!
    * This slot gets called when user clicks on "Add new cst cofins" button.
    */
    void onAddNewCstCofins();

    //! Edit cst cofins.
    /*!
    * This slot gets called when user clicks on "Edit cst cofins" button.
    */
    void onEditCstCofins();

    //! Remove cst cofins.
    /*!
    * This slot gets called when user clicks on "Remove cst cofins" button.
    */
    void onRemoveCstCofins();

private:
    Ui::CstCofinssListView *ui;
    IMainWindow *parentMainWindow;
    CstCofinsController *cstCofinsController;

};

#endif // CSTCOFINSSLISTVIEW_H
