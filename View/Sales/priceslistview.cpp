#include "priceslistview.h"
#include "ui_priceslistview.h"

#include <QMessageBox>

PricesListView::PricesListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PricesListView)
{
    ui->setupUi(this);

    connect(ui->addPricePushButton, SIGNAL(released()), this, SLOT(onAddNewPrice()));
    connect(ui->editPricePushButton, SIGNAL(released()), this, SLOT(onEditPrice()));
    connect(ui->removePricePushButton, SIGNAL(released()), this, SLOT(onRemovePrice()));

    priceController = new PriceController();
    listPrices();
}

PricesListView::~PricesListView()
{
    delete ui;

    delete this->priceController;
}

void PricesListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void PricesListView::listPrices()
{
    QLocale locale(QLocale::German);

    QList<Price*> *prices = priceController->getPrices();

    int count = prices->count();
    ui->pricesTableWidget->clearContents();
    ui->pricesTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        Price *price = prices->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->pricesTableWidget->setVerticalHeaderItem(i, verticalHeader);

        //Id
        QTableWidgetItem *idItem = new QTableWidgetItem();
        int idItemValue = price->getId();
        idItem->setText(QString::number(idItemValue));
        ui->pricesTableWidget->setItem(i, 0, idItem);

        //Related Product
        QTableWidgetItem *productItem = new QTableWidgetItem();
        QString productCode = price->getProductCode();
        QString productItemValue = priceController->getProductName(productCode);
        productItem->setText(productItemValue);
        ui->pricesTableWidget->setItem(i, 1, productItem);

        //Value
        QTableWidgetItem *valueItem = new QTableWidgetItem();
        double valueItemValue = price->getValue();
        QString valueItemValueStr = locale.toString(valueItemValue,'f',2);
        valueItem->setText(valueItemValueStr);
        ui->pricesTableWidget->setItem(i, 2, valueItem);

        //Store
        QTableWidgetItem *storeItem = new QTableWidgetItem();
        QString storeCnpj = price->getStoreCnpj();
        QString storeItemValue = priceController->getStoreName(storeCnpj);
        storeItem->setText(storeItemValue);
        ui->pricesTableWidget->setItem(i, 3, storeItem);

        //Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = price->getName();
        nameItem->setText(nameItemValue);
        ui->pricesTableWidget->setItem(i, 4, nameItem);
    }

    ui->pricesTableWidget->resizeColumnsToContents();
    ui->pricesTableWidget->selectRow(0);
    ui->pricesTableWidget->hideColumn(0);

    if(count == 0){
        ui->editPricePushButton->setEnabled(false);
    }
    else{
        ui->editPricePushButton->setEnabled(true);
    }

}

//============== PUBLIC SLOTS ===================

void PricesListView::onAddNewPrice()
{
    this->parentMainWindow->addFormAddPriceToMDI();
}

void PricesListView::onEditPrice()
{
    ui->pricesTableWidget->showColumn(0);
    QTableWidgetItem *item = ui->pricesTableWidget->selectedItems().at(0);
    ui->pricesTableWidget->hideColumn(0);

    int id = item->text().toInt();
    Price *price = priceController->getPriceById(id);
    this->parentMainWindow->addFormEditPriceToMDI(price);

}

void PricesListView::onRemovePrice()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this price?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        ui->pricesTableWidget->showColumn(0);
        QTableWidgetItem *item = ui->pricesTableWidget->selectedItems().at(0);
        ui->pricesTableWidget->hideColumn(0);
        int id = item->text().toInt();
        Utilities::StatusControl status = priceController->removePrice(id);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listPrices();
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
