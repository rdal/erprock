#ifndef ADDSTOCKUNITVIEW_H
#define ADDSTOCKUNITVIEW_H

#include <QWidget>
#include "stockunitslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddStockUnitView;
}

//!  View for adding/updating stock unit
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating stock unit.
*/
class AddStockUnitView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddStockUnitView. When creating a new StockUnit, use this constructor.
    */
    explicit AddStockUnitView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddStockUnitView. When editing stock unit use this constructor.
    */
    explicit AddStockUnitView(StockUnit *stockUnit, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddStockUnitView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddStockUnitView *ui;
    IMainWindow *parentMainWindow;
    StockUnitsListView *parent;
    StockUnit *editingStockUnit;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add stock unit
    /*!
      This slot is called to proceed with the inclusion of the stock unit, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddStockUnit();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddStockUnit()
    */
    void hideAndClearFieldsData();
};

#endif // ADDSTOCKUNITVIEW_H
