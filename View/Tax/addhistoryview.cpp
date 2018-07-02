#include "addhistoryview.h"
#include "ui_addhistoryview.h"

#include <QMessageBox>

AddHistoryView::AddHistoryView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddHistoryView)
{
    ui->setupUi(this);

	this->parent = (HistoriesListView*)parent;
    init();

    QString title = QApplication::translate("AddHistoryView", "Add new History", 0);
    setWindowTitle(title);

    this->editingHistory = NULL;

}

AddHistoryView::AddHistoryView(History *history, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddHistoryView)
{
    ui->setupUi(this);

    this->parent = (HistoriesListView*)parent;
    init();

    QString title = QApplication::translate("AddHistoryView", "Edit History", 0);
    setWindowTitle(title);

    this->editingHistory = history;
    ui->historyNameLineEdit->setText(history->getName());
    
}


AddHistoryView::~AddHistoryView()
{
    delete ui;

	delete editingHistory;
}


void AddHistoryView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddHistory()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
	ui->historyNameLineEdit->setFocus();
}

void AddHistoryView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddHistoryView::proceedToAddHistory()
{
    QString name = ui->historyNameLineEdit->text();
	
    if(name.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill name field"),
                              QMessageBox::Ok);
    }
    else{

        		
		HistoriesController *historyController = new HistoriesController();
		                
		Utilities::StatusControl status = (this->editingHistory) ?
                                          historyController->updateHistory(new History(this->editingHistory->getId(), name)) :
                                          historyController->addHistory(new History(name));
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listHistories();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a tax rate registered with this name"),
                                      QMessageBox::Ok);
                break;
            }
            case Utilities::DB_NOT_CONNECTED:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("Database is not connected"),
                                      QMessageBox::Ok);
                break;
            }
            case Utilities::UNKNOWN_ERROR:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("Unknown error"),
                                      QMessageBox::Ok);
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void AddHistoryView::hideAndClearFieldsData()
{
    emit aboutToClose();
}