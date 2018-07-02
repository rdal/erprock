#include "storeslistview.h"
#include "ui_storeslistview.h"
#include <QMessageBox>

StoresListView::StoresListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StoresListView)
{
    ui->setupUi(this);

    connect(ui->addStorePushButton, SIGNAL(released()), this, SLOT(onAddNewStore()));
    connect(ui->editStorePushButton, SIGNAL(released()), this, SLOT(onEditStore()));
    connect(ui->removeStorePushButton, SIGNAL(released()), this, SLOT(onRemoveStore()));

    storeController = new StoreController();
    listStores();
}

StoresListView::~StoresListView()
{
    delete ui;

    delete storeController;
}

void StoresListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void StoresListView::listStores()
{
    QList<Store*> *stores = storeController->getStores();

    int count = stores->count();
    ui->storesTableWidget->clearContents();
    ui->storesTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        Store *store = stores->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->storesTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // CNPJ
        QTableWidgetItem *cnpjItem = new QTableWidgetItem();
        QString cnpjItemValue = store->getCNPJ();
        cnpjItem->setText(cnpjItemValue);
        ui->storesTableWidget->setItem(i, 0, cnpjItem);

        // State Number
        QTableWidgetItem *stateNumberItem = new QTableWidgetItem();
        QString stateNumberItemValue = store->getStateNumber();
        stateNumberItem->setText(stateNumberItemValue);
        ui->storesTableWidget->setItem(i, 1, stateNumberItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = store->getName();
        nameItem->setText(nameItemValue);
        ui->storesTableWidget->setItem(i, 2, nameItem);

        // Fantasy Name
        QTableWidgetItem *fantasyNameItem = new QTableWidgetItem();
        QString fantasyNameItemValue = store->getFantasyName();
        fantasyNameItem->setText(fantasyNameItemValue);
        ui->storesTableWidget->setItem(i, 3, fantasyNameItem);

        // Phone Number
        QTableWidgetItem *phoneNumberItem = new QTableWidgetItem();
        QString phoneNumberItemValue = store->getPhoneNumber();
        phoneNumberItem->setText(phoneNumberItemValue);
        ui->storesTableWidget->setItem(i, 4, phoneNumberItem);

        // Fax Number
        QTableWidgetItem *faxNumberItem = new QTableWidgetItem();
        QString faxNumberItemValue = store->getFaxNumber();
        faxNumberItem->setText(faxNumberItemValue);
        ui->storesTableWidget->setItem(i, 5, faxNumberItem);

        // Contact Name
        QTableWidgetItem *contactNameItem = new QTableWidgetItem();
        QString contactNameItemValue = store->getContactName();
        contactNameItem->setText(contactNameItemValue);
        ui->storesTableWidget->setItem(i, 6, contactNameItem);

        // Email
        QTableWidgetItem *emailItem = new QTableWidgetItem();
        QString emailItemValue = store->getEmail();
        emailItem->setText(emailItemValue);
        ui->storesTableWidget->setItem(i, 7, emailItem);

        // Address Street
        QTableWidgetItem *addressStreetItem = new QTableWidgetItem();
        QString addressStreetItemValue = store->getAddressStreet();
        addressStreetItem->setText(addressStreetItemValue);
        ui->storesTableWidget->setItem(i, 8, addressStreetItem);

        // Address Number
        QTableWidgetItem *addressNumberItem = new QTableWidgetItem();
        int addressNumberItemValue = store->getAddressNumber();
        addressNumberItem->setText(QString::number(addressNumberItemValue));
        ui->storesTableWidget->setItem(i, 9, addressNumberItem);

        // Address Complement
        QTableWidgetItem *addressComplementItem = new QTableWidgetItem();
        QString addressComplementItemValue = store->getAddressComplement();
        addressComplementItem->setText(addressComplementItemValue);
        ui->storesTableWidget->setItem(i, 10, addressComplementItem);

        // Address Square
        QTableWidgetItem *addressSquareItem = new QTableWidgetItem();
        QString addressSquareItemValue = store->getAddressSquare();
        addressSquareItem->setText(addressSquareItemValue);
        ui->storesTableWidget->setItem(i, 11, addressSquareItem);

        // Address City
        QTableWidgetItem *addressCityItem = new QTableWidgetItem();
        QString addressCityItemValue = store->getAddressCity();
        addressCityItem->setText(addressCityItemValue);
        ui->storesTableWidget->setItem(i, 12, addressCityItem);

        // Address State
        QTableWidgetItem *addressStateItem = new QTableWidgetItem();
        QString addressStateItemValue = store->getAddressState();
        addressStateItem->setText(addressStateItemValue);
        ui->storesTableWidget->setItem(i, 13, addressStateItem);

        // Address Postal Code
        QTableWidgetItem *addressPostalCodeItem = new QTableWidgetItem();
        QString addressPostalCodeItemValue = store->getAddressPostalCode();
        addressPostalCodeItem->setText(addressPostalCodeItemValue);
        ui->storesTableWidget->setItem(i, 14, addressPostalCodeItem);
    }

    ui->storesTableWidget->resizeColumnsToContents();
    ui->storesTableWidget->selectRow(0);

    if(count == 0){
        ui->editStorePushButton->setEnabled(false);
    }
    else{
        ui->editStorePushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void StoresListView::onAddNewStore()
{
    this->parentMainWindow->addFormAddStoreToMDI();
}

void StoresListView::onEditStore()
{
    QTableWidgetItem *item = ui->storesTableWidget->selectedItems().at(0);
    QString cnpj = item->text();
    Store *store = storeController->getStoreByCNPJ(cnpj);
    this->parentMainWindow->addFormEditStoreToMDI(store);
}

void StoresListView::onRemoveStore()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this store?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->storesTableWidget->selectedItems().at(0);
        QString cnpj = item->text();
        Utilities::StatusControl status = storeController->removeStore(cnpj);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listStores();
                break;
            }
            case Utilities::ACTION_FORBIDDEN:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("You cannot remove the store you are currently using"),
                                      QMessageBox::Ok);
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered CNPJ doesn't belong to any store of database"),
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
