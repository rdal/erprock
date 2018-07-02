#include "taxrateslistview.h"
#include "ui_taxrateslistview.h"

#include <QMessageBox>

TaxRatesListView::TaxRatesListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaxRatesListView)
{
    ui->setupUi(this);

    connect(ui->addTaxRatePushButton, SIGNAL(released()), this, SLOT(onAddNewTaxRate()));
    connect(ui->editTaxRatePushButton, SIGNAL(released()), this, SLOT(onEditTaxRate()));
    connect(ui->removeTaxRatePushButton, SIGNAL(released()), this, SLOT(onRemoveTaxRate()));

    taxRateController = new TaxRateController();
    listTaxRates();
}

TaxRatesListView::~TaxRatesListView()
{
    delete ui;

    delete taxRateController;
}

void TaxRatesListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void TaxRatesListView::listTaxRates()
{
    QList<TaxRate*> *taxRates = taxRateController->getTaxRates();

    int count = taxRates->count();
    ui->taxRatesTableWidget->clearContents();
    ui->taxRatesTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        TaxRate *taxRate = taxRates->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->taxRatesTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = taxRate->getName();
        nameItem->setText(nameItemValue);
        ui->taxRatesTableWidget->setItem(i, 0, nameItem);

        // Value
        QTableWidgetItem *valueItem = new QTableWidgetItem();
        double valueItemValue = taxRate->getValue();
        valueItem->setText(QString::number(valueItemValue));
        ui->taxRatesTableWidget->setItem(i, 1, valueItem);
    }

    ui->taxRatesTableWidget->resizeColumnsToContents();
    ui->taxRatesTableWidget->selectRow(0);

    if(count == 0){
        ui->editTaxRatePushButton->setEnabled(false);
    }
    else{
        ui->editTaxRatePushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void TaxRatesListView::onAddNewTaxRate()
{
    this->parentMainWindow->addFormAddTaxRateToMDI();
}

void TaxRatesListView::onEditTaxRate()
{
    QTableWidgetItem *item = ui->taxRatesTableWidget->selectedItems().at(0);
    QString name = item->text();
    TaxRate *taxRate = taxRateController->getTaxRateByName(name);
    this->parentMainWindow->addFormEditTaxRateToMDI(taxRate);
}

void TaxRatesListView::onRemoveTaxRate()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this Tax Rate?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->taxRatesTableWidget->selectedItems().at(0);
        QString name = item->text();
        Utilities::StatusControl status = taxRateController->removeTaxRate(name);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listTaxRates();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered name doesn't belong to any Tax Rate of database"),
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
