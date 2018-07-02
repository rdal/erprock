#include "addentryview.h"
#include "ui_addentryview.h"
#include <QMessageBox>

AddEntryView::AddEntryView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddEntryView)
{
    ui->setupUi(this);

    this->parent = (EntriesListView*)parent;
    init();

    QString title = QApplication::translate("AddEntryView", "Add new Entry", 0);
    setWindowTitle(title);

    this->editingEntry = NULL;
}

AddEntryView::AddEntryView(Entry *entry, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddEntryView)
{
    ui->setupUi(this);

    this->parent = (EntriesListView*)parent;
    init();

    QString title = QApplication::translate("AddEntryView", "Edit Entry", 0);
    setWindowTitle(title);

    this->editingEntry = entry;

    //Date
    ui->dateDateEdit->setDateTime(entry->getDate());

    // Store
    QString storeCnpj = entry->getStoreCnpj();
    int idxStoreCnpj = ui->storeComboBox->findData(QVariant(storeCnpj));
    ui->storeComboBox->setCurrentIndex(idxStoreCnpj);

    // Debtor Account
    QString debtorAccount = entry->getDebtorAccount();
    int idxDebtorAccount = ui->debtorAccountComboBox->findData(QVariant(debtorAccount));
    ui->debtorAccountComboBox->setCurrentIndex(idxDebtorAccount);

    // Creditor Account
    QString creditorAccount = entry->getCreditorAccount();
    int idxCreditorAccount = ui->creditorAccountComboBox->findData(QVariant(creditorAccount));
    ui->creditorAccountComboBox->setCurrentIndex(idxCreditorAccount);

    // Value
    ui->valueDoubleSpinBox->setValue(entry->getValue());

    // History
    int history = entry->getHistory();
    int idxHistory = ui->historyComboBox->findData(QVariant(history));
    ui->historyComboBox->setCurrentIndex(idxHistory);

    // Complement
    ui->complementPlainTextEdit->setPlainText(entry->getComplement());

}

AddEntryView::~AddEntryView()
{
    delete ui;

    delete editingEntry;
}

void AddEntryView::init()
{
    //============ Date ==============
    ui->dateDateEdit->setDateTime(QDateTime::currentDateTime());

    //============ Store =============
    StoreController *storeController = new StoreController();
    QList<Store*> *storeObjects = storeController->getStores();

    ui->storeComboBox->clear();
    ui->storeComboBox->addItem(QApplication::translate("AddEntryView", "-- Select a store", 0), QVariant(""));

    int storesCount = storeObjects->count();
    for(int i=0; i<storesCount; i++)
    {
        QString name = ((Store*)storeObjects->at(i))->getName();
        ui->storeComboBox->addItem(name, QVariant(storeObjects->at(i)->getCNPJ()));
    }

    //======== Debtor Account =========
    AccountsController *accountsController = new AccountsController();
    QList<Account*> *accountObjects = accountsController->getAnalyticAccounts();

    ui->debtorAccountComboBox->clear();
    ui->debtorAccountComboBox->addItem(QApplication::translate("AddEntryView", "-- Select an account", 0), QVariant(""));

    int accountsCount = accountObjects->count();
    for(int i=0; i<accountsCount; i++)
    {
        QString name = ((Account*)accountObjects->at(i))->getName();
        ui->debtorAccountComboBox->addItem(accountObjects->at(i)->getCode() + " - " + name, QVariant(accountObjects->at(i)->getCode()));
    }

    //======== Creditor Account =========
    ui->creditorAccountComboBox->clear();
    ui->creditorAccountComboBox->addItem(QApplication::translate("AddEntryView", "-- Select an account", 0), QVariant(""));

    for(int i=0; i<accountsCount; i++)
    {
        QString name = ((Account*)accountObjects->at(i))->getName();
        ui->creditorAccountComboBox->addItem(accountObjects->at(i)->getCode() + " - " + name, QVariant(accountObjects->at(i)->getCode()));
    }

    //============ History =============
    HistoriesController *historyController = new HistoriesController();
    QList<History*> *historyObjects = historyController->getHistories();

    ui->historyComboBox->clear();
    ui->historyComboBox->addItem(QApplication::translate("AddEntryView", "-- Select a history", 0), QVariant(""));

    int historiesCount = historyObjects->count();
    for(int i=0; i<historiesCount; i++)
    {
        QString name = ((History*)historyObjects->at(i))->getName();
        ui->historyComboBox->addItem(name, QVariant(historyObjects->at(i)->getId()));
    }
    //==================================

    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddEntry()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));

    delete storeController;
    delete accountsController;
    delete historyController;
}

void AddEntryView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddEntryView::proceedToAddEntry()
{
    QDateTime date = ui->dateDateEdit->dateTime();
    QString storeCnpj = ui->storeComboBox->itemData(ui->storeComboBox->currentIndex()).toString();
    QString debtorAccount = ui->debtorAccountComboBox->itemData(ui->debtorAccountComboBox->currentIndex()).toString();
    QString creditorAccount = ui->creditorAccountComboBox->itemData(ui->creditorAccountComboBox->currentIndex()).toString();
    double value = ui->valueDoubleSpinBox->value();
    int historyId = ui->historyComboBox->itemData(ui->historyComboBox->currentIndex()).toInt();
    QString complement = ui->complementPlainTextEdit->toPlainText();

    if(storeCnpj.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select a store related to this entry."),
                              QMessageBox::Ok);
    }
    else if(debtorAccount.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select a debtor account related to this entry."),
                              QMessageBox::Ok);
    }
    else if(creditorAccount.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select a creditor account related to this entry."),
                              QMessageBox::Ok);
    }
    else if(historyId == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("You must select a history."),
                              QMessageBox::Ok);
    }
    else{


        EntriesController *entryController = new EntriesController();

        Utilities::StatusControl status = (this->editingEntry) ?
                                          entryController->updateEntry(new Entry(this->editingEntry->getId(), date, storeCnpj, debtorAccount, creditorAccount, value, historyId, complement)) :
                                          entryController->addEntry(new Entry(date, storeCnpj, debtorAccount, creditorAccount, value, historyId, complement));
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listEntries();
                emit aboutToClose();
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

void AddEntryView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
