#ifndef STOCKUNITSLISTVIEW_H
#define STOCKUNITSLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "stockunitcontroller.h"

namespace Ui {
    class StockUnitsListView;
}

//!  View for listing stock units
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing stock units.
*/
class StockUnitsListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of StockUnitsListView.
    */
    explicit StockUnitsListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~StockUnitsListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all providers.
    /*!
    * This method retrieves all stock units from database, and show them in a grid.
    */
    void listStockUnits();

public slots:

    //! Add new stock unit.
    /*!
    * This slot gets called when user clicks on "Add new stock unit" button.
    */
    void onAddNewStockUnit();

    //! Edit stock unit.
    /*!
    * This slot gets called when user clicks on "Edit stock unit" button.
    */
    void onEditStockUnit();

    //! Remove stock unit.
    /*!
    * This slot gets called when user clicks on "Remove stock unit" button.
    */
    void onRemoveStockUnit();

private:
    Ui::StockUnitsListView *ui;
    IMainWindow *parentMainWindow;
    StockUnitController *stockUnitController;
};

#endif // STOCKUNITSLISTVIEW_H
