#ifndef ADDPRODUCTORIGINVIEW_H
#define ADDPRODUCTORIGINVIEW_H

#include <QWidget>
#include "productoriginslistview.h"
#include "imainwindow.h"

namespace Ui {
    class AddProductOriginView;
}

//!  View for adding/updating product origin
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for adding/updating product origin.
*/
class AddProductOriginView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of AddProductOriginView. When creating a new ProductOrigin, use this constructor.
    */
    explicit AddProductOriginView(QWidget *parent = 0);

    //! Constructor.
    /*!
    * Create a new instance of AddProductOriginView. When editing product origin use this constructor.
    */
    explicit AddProductOriginView(ProductOrigin *productOrigin, QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~AddProductOriginView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
    void init();

    Ui::AddProductOriginView *ui;
    IMainWindow *parentMainWindow;
    ProductOriginsListView *parent;
    ProductOrigin *editingProductOrigin;

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close. So, the MainWindow that have subscribed to it, via setParentMainWindow(), can perform some action.
      \sa setParentMainWindow()
    */
    void aboutToClose();

public slots:

    //! Proceed to add product origin
    /*!
      This slot is called to proceed with the inclusion of the product origin, into database.
      \sa hideAndClearFieldsData()
    */
    void proceedToAddProductOrigin();

    //! Hides the dialog
    /*!
      Closes the dialog and clear all fields.
      \sa proceedToAddProductOrigin()
    */
    void hideAndClearFieldsData();
};

#endif // ADDPRODUCTORIGINVIEW_H
