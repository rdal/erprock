#ifndef CFOPSLISTVIEW_H
#define CFOPSLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "cfopcontroller.h"

namespace Ui {
    class CfopsListView;
}

//!  View for listing cfops
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for listing cfops.
*/
class CfopsListView : public QWidget
{
    Q_OBJECT

public:

    //! Default constructor.
    /*!
    * Create a new instance of CfopsListView.
    */
    explicit CfopsListView(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~CfopsListView();

    //! Set parent MainWindow. When a dialog is opened, it may be necessary to do some actions at the window who called it.
    //! Actions like refreshing a list of users or setting the current user logged in, when this dialog is about to close.
    /*!
      \param parentMainWindow Parent MainWindow
    */
    void setParentMainWindow(IMainWindow *parentMainWindow);

    //! Set Window Mode
    /*!
      \param windowMode Window mode
      \sa setCfopObjectChosen()
    */
    void setWindowMode(Utilities::ItemsListWindowMode windowMode);

    //! List all providers.
    /*!
    * This method retrieves all cfops from database, and show them in a grid.
    */
    void listCfops();

    //! Set chosen Object.
    /*!
    * This method sets a given Cfop Object as the chosen one.
    * CHOOSE_ITEM Window Mode must be set.
    * \sa setWindowMode()
    */
    void setCfopObjectChosen(Cfop *&localChosenCfop);

signals:
    //! About to close
    /*!
      Emit this signal when the dialog is about to close.
    */
    void aboutToClose();

public slots:

    //! Add new cfop.
    /*!
    * This slot gets called when user clicks on "Add new cfop" button.
    */
    void onAddNewCfop();

    //! Edit cfop.
    /*!
    * This slot gets called when user clicks on "Edit cfop" button.
    */
    void onEditCfop();

    //! Remove cfop.
    /*!
    * This slot gets called when user clicks on "Remove cfop" button.
    */
    void onRemoveCfop();

    //! Import into database.
    /*!
    * This slot is executed when an user tries to import a file that contains all CFOP's database.
    * The CFOP's table will be completly erased before importing the new CFOP's definition.
    */
    void onImportIntoDB();

    //! Choose cfop.
    /*!
    * This slot gets called when user clicks twice on a certain cfop.
    * CHOOSE_ITEM Window Mode must be set to get this behavior
    */
    void onChooseCfop();

private:
    Ui::CfopsListView *ui;
    IMainWindow *parentMainWindow;
    CfopController *cfopController;

    Utilities::ItemsListWindowMode windowMode;
    Cfop *chosenCfop;
};

#endif // CFOPSLISTVIEW_H
