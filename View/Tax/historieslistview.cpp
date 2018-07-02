#include "historieslistview.h"
#include "ui_historieslistview.h"

#include <QMessageBox>

HistoriesListView::HistoriesListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoriesListView)
{
    ui->setupUi(this);

	connect(ui->addHistoryPushButton, SIGNAL(released()), this, SLOT(onAddNewHistory()));
    connect(ui->editHistoryPushButton, SIGNAL(released()), this, SLOT(onEditHistory()));
    connect(ui->removeHistoryPushButton, SIGNAL(released()), this, SLOT(onRemoveHistory()));
		
	historiesController = new HistoriesController();
	listHistories();
	
}

HistoriesListView::~HistoriesListView()
{
    delete ui;
}

void HistoriesListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void HistoriesListView::listHistories()
{

	QList<History*> *histories = historiesController->getHistories();

    int count = histories->count();
    ui->historiesTableWidget->clearContents();
    ui->historiesTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        History *history = histories->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->historiesTableWidget->setVerticalHeaderItem(i, verticalHeader);

		// ID
        QTableWidgetItem *idItem = new QTableWidgetItem();
        int idItemValue = history->getId();
        idItem->setText(QString::number(idItemValue));
        ui->historiesTableWidget->setItem(i, 0, idItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = history->getName();
        nameItem->setText(nameItemValue);
        ui->historiesTableWidget->setItem(i, 1, nameItem);
		        
    }

	ui->historiesTableWidget->resizeColumnsToContents();
    ui->historiesTableWidget->selectRow(0);
	ui->historiesTableWidget->hideColumn(0);
	ui->historiesTableWidget->horizontalHeader()->setStretchLastSection(true);
	    

    if(count == 0){
        ui->editHistoryPushButton->setEnabled(false);
		ui->removeHistoryPushButton->setEnabled(false);
    }
    else{
        ui->editHistoryPushButton->setEnabled(true);
		ui->removeHistoryPushButton->setEnabled(true);
    }

	
}

//============== PUBLIC SLOTS ================
void HistoriesListView::onAddNewHistory()
{
    this->parentMainWindow->addFormAddHistoryToMDI();
}

void HistoriesListView::onEditHistory()
{
	ui->historiesTableWidget->showColumn(0);
    QTableWidgetItem *item = ui->historiesTableWidget->selectedItems().at(0);
	ui->historiesTableWidget->hideColumn(0);
	
	int id = item->text().toInt();
	History *history = historiesController->getHistoryById(id);
	this->parentMainWindow->addFormEditHistoryToMDI(history);
		

}

void HistoriesListView::onRemoveHistory()
{
	//ByMav
	 QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this History?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        ui->historiesTableWidget->showColumn(0);
        QTableWidgetItem *item = ui->historiesTableWidget->selectedItems().at(0);
        ui->historiesTableWidget->hideColumn(0);
        int id = item->text().toInt();
        Utilities::StatusControl status = historiesController->removeHistory(id);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listHistories();
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