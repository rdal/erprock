#include "entrieslistview.h"
#include "ui_entrieslistview.h"

#include <QMessageBox>

EntriesListView::EntriesListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntriesListView)
{
    ui->setupUi(this);

    connect(ui->addEntryPushButton, SIGNAL(released()), this, SLOT(onAddNewEntry()));
    connect(ui->editEntryPushButton, SIGNAL(released()), this, SLOT(onEditEntry()));
    connect(ui->removeEntryPushButton, SIGNAL(released()), this, SLOT(onRemoveEntry()));

    entriesController = new EntriesController();
    historiesController = new HistoriesController();
    accountsController = new AccountsController();
    storeController = new StoreController();
    listEntries();
}

EntriesListView::~EntriesListView()
{
    delete ui;

    delete entriesController;
    delete historiesController;
    delete accountsController;
    delete storeController;
}

void EntriesListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void EntriesListView::listEntries()
{
    QLocale locale(QLocale::German);

    QList<Entry*> *entries = entriesController->getEntries();

    int count = entries->count();
    ui->entriesTableWidget->clearContents();
    ui->entriesTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        Entry *entry = entries->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->entriesTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Id
        QTableWidgetItem *idItem = new QTableWidgetItem();
        int idItemValue = entry->getId();
        idItem->setText(QString::number(idItemValue));
        ui->entriesTableWidget->setItem(i, 0, idItem);

        // Date
        QTableWidgetItem *dateItem = new QTableWidgetItem();
        QDateTime dateItemValue = entry->getDate();
        dateItem->setText(dateItemValue.toString());
        ui->entriesTableWidget->setItem(i, 1, dateItem);

        // Store
        QTableWidgetItem *storeItem = new QTableWidgetItem();
        QString storeItemValue = entry->getStoreCnpj();
        Store *store = storeController->getStoreByCNPJ(storeItemValue);
        storeItem->setText(store->getName());
        ui->entriesTableWidget->setItem(i, 2, storeItem);

        // Debtor Account
        QTableWidgetItem *debtorAccountItem = new QTableWidgetItem();
        QString debtorAccountItemValue = entry->getDebtorAccount();
        Account *debtorAccount = accountsController->getAccountByCode(debtorAccountItemValue);
        debtorAccountItem->setText(debtorAccount->getName());
        ui->entriesTableWidget->setItem(i, 3, debtorAccountItem);

        // Creditor Account
        QTableWidgetItem *creditorAccountItem = new QTableWidgetItem();
        QString creditorAccountItemValue = entry->getCreditorAccount();
        Account *creditorAccount = accountsController->getAccountByCode(creditorAccountItemValue);
        creditorAccountItem->setText(creditorAccount->getName());
        ui->entriesTableWidget->setItem(i, 4, creditorAccountItem);

        // Value
        QTableWidgetItem *valueItem = new QTableWidgetItem();
        double valueItemValue = entry->getValue();
        QString valueItemValueStr = locale.toString(valueItemValue,'f',2);
        valueItem->setText(valueItemValueStr);
        ui->entriesTableWidget->setItem(i, 5, valueItem);

        // History
        QTableWidgetItem *historyItem = new QTableWidgetItem();
        int historyId = entry->getHistory();
        History *history = historiesController->getHistoryById(historyId);
        QString historyItemValue = history->getName();
        historyItem->setText(historyItemValue);
        ui->entriesTableWidget->setItem(i, 6, historyItem);

        // Complement
        QTableWidgetItem *complementItem = new QTableWidgetItem();
        QString complementItemValue = entry->getComplement();
        complementItem->setText(complementItemValue);
        ui->entriesTableWidget->setItem(i, 7, complementItem);
    }

    ui->entriesTableWidget->resizeColumnsToContents();
    ui->entriesTableWidget->selectRow(0);

    if(count == 0){
        ui->editEntryPushButton->setEnabled(false);
    }
    else{
        ui->editEntryPushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ===================

void EntriesListView::onAddNewEntry()
{
    this->parentMainWindow->addFormAddEntryToMDI();
}

void EntriesListView::onEditEntry()
{
    ui->entriesTableWidget->showColumn(0);
    QTableWidgetItem *item = ui->entriesTableWidget->selectedItems().at(0);
    ui->entriesTableWidget->hideColumn(0);

    int id = item->text().toInt();
    Entry *entry = entriesController->getEntryById(id);
    this->parentMainWindow->addFormEditEntryToMDI(entry);

}

void EntriesListView::onRemoveEntry()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this entry?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        ui->entriesTableWidget->showColumn(0);
        QTableWidgetItem *item = ui->entriesTableWidget->selectedItems().at(0);
        ui->entriesTableWidget->hideColumn(0);
        int id = item->text().toInt();
        Utilities::StatusControl status = entriesController->removeEntry(id);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listEntries();
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
