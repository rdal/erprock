#ifndef CSTIPISLISTVIEW_H
#define CSTIPISLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "cstipicontroller.h"

namespace Ui {
    class CstIpisListView;
}

//!  View for listing cst pis
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing cst pis.
*/
class CstIpisListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of CstIpisListView.
    */
    explicit CstIpisListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CstIpisListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all providers.
    /*!
    * This method retrieves all cst pis from database, and show them in a grid.
    */
    void listCstIpis();

public slots:

    //! Add new cst pis.
    /*!
    * This slot gets called when user clicks on "Add new cst pis" button.
    */
    void onAddNewCstIpi();

    //! Edit cst pis.
    /*!
    * This slot gets called when user clicks on "Edit cst pis" button.
    */
    void onEditCstIpi();

    //! Remove cst pis.
    /*!
    * This slot gets called when user clicks on "Remove cst pis" button.
    */
    void onRemoveCstIpi();

private:
    Ui::CstIpisListView *ui;
    IMainWindow *parentMainWindow;
    CstIpiController *cstIpiController;
};

#endif // CSTIPISLISTVIEW_H
