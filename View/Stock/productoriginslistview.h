#ifndef PRODUCTORIGINSLISTVIEW_H
#define PRODUCTORIGINSLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "productorigincontroller.h"

namespace Ui {
    class ProductOriginsListView;
}

//!  View for listing product origins
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing product origins.
*/
class ProductOriginsListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of ProductOriginsListView.
    */
    explicit ProductOriginsListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~ProductOriginsListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! List all providers.
    /*!
    * This method retrieves all product origins from database, and show them in a grid.
    */
    void listProductOrigins();

public slots:

    //! Add new product origin.
    /*!
    * This slot gets called when user clicks on "Add new product origin" button.
    */
    void onAddNewProductOrigin();

    //! Edit product origin.
    /*!
    * This slot gets called when user clicks on "Edit product origin" button.
    */
    void onEditProductOrigin();

    //! Remove product origin.
    /*!
    * This slot gets called when user clicks on "Remove product origin" button.
    */
    void onRemoveProductOrigin();

private:
    Ui::ProductOriginsListView *ui;
    IMainWindow *parentMainWindow;
    ProductOriginController *productOriginController;
};

#endif // PRODUCTORIGINSLISTVIEW_H
