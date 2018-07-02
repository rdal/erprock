#ifndef ADDENTRYVIEW_H
#define ADDENTRYVIEW_H

#include <QWidget>
#include "entrieslistview.h"
#include "imainwindow.h"

namespace Ui {
class AddEntryView;
}

class AddEntryView : public QWidget
{
    Q_OBJECT
    
public:
    explicit AddEntryView(QWidget *parent = 0);
    explicit AddEntryView(Entry *entry, QWidget *parent = 0);
    ~AddEntryView();
    void setParentMainWindow(IMainWindow *parentMainWindow);
    
private:
    void init();

    Ui::AddEntryView *ui;
    IMainWindow *parentMainWindow;
    EntriesListView *parent;
    Entry *editingEntry;

signals:
    void aboutToClose();


public slots:
    void proceedToAddEntry();

    void hideAndClearFieldsData();
};

#endif // ADDENTRYVIEW_H
