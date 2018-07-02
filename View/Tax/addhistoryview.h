#ifndef ADDHISTORYVIEW_H
#define ADDHISTORYVIEW_H

#include <QWidget>
#include "historieslistview.h"
#include "imainwindow.h"

namespace Ui {
class AddHistoryView;
}

class AddHistoryView : public QWidget
{
    Q_OBJECT
    
public:
    explicit AddHistoryView(QWidget *parent = 0);
	explicit AddHistoryView(History *history, QWidget *parent = 0);
    ~AddHistoryView();
    void setParentMainWindow(IMainWindow *parentMainWindow);

private:
	void init();

    Ui::AddHistoryView *ui;
	IMainWindow *parentMainWindow;
    HistoriesListView *parent;
    History *editingHistory;

signals:
    void aboutToClose();


public slots:
    void proceedToAddHistory();

    void hideAndClearFieldsData();

};

#endif // ADDHISTORYVIEW_H
