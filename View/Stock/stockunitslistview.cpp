#include "stockunitslistview.h"
#include "ui_stockunitslistview.h"

#include <QMessageBox>

StockUnitsListView::StockUnitsListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockUnitsListView)
{
    ui->setupUi(this);

    connect(ui->addStockUnitPushButton, SIGNAL(released()), this, SLOT(onAddNewStockUnit()));
    connect(ui->editStockUnitPushButton, SIGNAL(released()), this, SLOT(onEditStockUnit()));
    connect(ui->removeStockUnitPushButton, SIGNAL(released()), this, SLOT(onRemoveStockUnit()));

    stockUnitController = new StockUnitController();
    listStockUnits();
}

StockUnitsListView::~StockUnitsListView()
{
    delete ui;

    delete stockUnitController;
}

void StockUnitsListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void StockUnitsListView::listStockUnits()
{
    QList<StockUnit*> *stockUnits = stockUnitController->getStockUnits();

    int count = stockUnits->count();
    ui->stockUnitsTableWidget->clearContents();
    ui->stockUnitsTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        StockUnit *stockUnit = stockUnits->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->stockUnitsTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Id
        QTableWidgetItem *idItem = new QTableWidgetItem();
        int idItemValue = stockUnit->getId();
        idItem->setText(QString::number(idItemValue));
        ui->stockUnitsTableWidget->setItem(i, 0, idItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = stockUnit->getName();
        nameItem->setText(nameItemValue);
        ui->stockUnitsTableWidget->setItem(i, 1, nameItem);
    }

    ui->stockUnitsTableWidget->resizeColumnsToContents();
    ui->stockUnitsTableWidget->selectRow(0);

    if(count == 0){
        ui->editStockUnitPushButton->setEnabled(false);
    }
    else{
        ui->editStockUnitPushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void StockUnitsListView::onAddNewStockUnit()
{
    this->parentMainWindow->addFormAddStockUnitToMDI();
}

void StockUnitsListView::onEditStockUnit()
{
    QTableWidgetItem *item = ui->stockUnitsTableWidget->selectedItems().at(0);
    int id = item->text().toInt();
    StockUnit *stockUnit = stockUnitController->getStockUnitById(id);
    this->parentMainWindow->addFormEditStockUnitToMDI(stockUnit);
}

void StockUnitsListView::onRemoveStockUnit()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this stock unit?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->stockUnitsTableWidget->selectedItems().at(0);
        int id = item->text().toInt();
        Utilities::StatusControl status = stockUnitController->removeStockUnit(id);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listStockUnits();
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
