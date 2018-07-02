#ifndef HISTORIESLISTVIEW_H
#define HISTORIESLISTVIEW_H

#include <QWidget>
#include "imainwindow.h"
#include "historiescontroller.h"

namespace Ui {
class HistoriesListView;
}

//!  View for listing Histories
//ByMav
/*!
  This class is responsible for listing Histories.
*/
class HistoriesListView : public QWidget
{
    Q_OBJECT
    
public:
    explicit HistoriesListView(QWidget *parent = 0);
    ~HistoriesListView();

	void setParentMainWindow(IMainWindow *parentMainWindow);

    void listHistories();


public slots:

	void onAddNewHistory();
	void onEditHistory();
	void onRemoveHistory();
    
private:
    Ui::HistoriesListView *ui;

	IMainWindow* parentMainWindow;

	HistoriesController *historiesController;

};

#endif // HISTORIESLISTVIEW_H
