#include "providerslistview.h"
#include "ui_providerslistview.h"
#include <QMessageBox>

ProvidersListView::ProvidersListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProvidersListView)
{
    ui->setupUi(this);

    connect(ui->addProviderpushButton, SIGNAL(released()), this, SLOT(onAddNewProvider()));
    connect(ui->editProviderpushButton, SIGNAL(released()), this, SLOT(onEditProvider()));
    connect(ui->removeProviderpushButton, SIGNAL(released()), this, SLOT(onRemoveProvider()));

    providerController = new ProviderController();
    listProviders();
}

ProvidersListView::~ProvidersListView()
{
    delete ui;

    //parentMainWindow = NULL;
    delete providerController;
}

void ProvidersListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void ProvidersListView::listProviders()
{
    QList<Provider*> *providers = providerController->getProviders();

    int count = providers->count();
    ui->providersTableWidget->clearContents();
    ui->providersTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        Provider *provider = providers->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->providersTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // CNPJ
        QTableWidgetItem *cnpjItem = new QTableWidgetItem();
        QString cnpjItemValue = provider->getCNPJ();
        cnpjItem->setText(cnpjItemValue);
        ui->providersTableWidget->setItem(i, 0, cnpjItem);

        // State Number
        QTableWidgetItem *stateNumberItem = new QTableWidgetItem();
        QString stateNumberItemValue = provider->getStateNumber();
        stateNumberItem->setText(stateNumberItemValue);
        ui->providersTableWidget->setItem(i, 1, stateNumberItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = provider->getName();
        nameItem->setText(nameItemValue);
        ui->providersTableWidget->setItem(i, 2, nameItem);

        // Fantasy Name
        QTableWidgetItem *fantasyNameItem = new QTableWidgetItem();
        QString fantasyNameItemValue = provider->getFantasyName();
        fantasyNameItem->setText(fantasyNameItemValue);
        ui->providersTableWidget->setItem(i, 3, fantasyNameItem);

        // Phone Number
        QTableWidgetItem *phoneNumberItem = new QTableWidgetItem();
        QString phoneNumberItemValue = provider->getPhoneNumber();
        phoneNumberItem->setText(phoneNumberItemValue);
        ui->providersTableWidget->setItem(i, 4, phoneNumberItem);

        // Fax Number
        QTableWidgetItem *faxNumberItem = new QTableWidgetItem();
        QString faxNumberItemValue = provider->getFaxNumber();
        faxNumberItem->setText(faxNumberItemValue);
        ui->providersTableWidget->setItem(i, 5, faxNumberItem);

        // Contact Name
        QTableWidgetItem *contactNameItem = new QTableWidgetItem();
        QString contactNameItemValue = provider->getContactName();
        contactNameItem->setText(contactNameItemValue);
        ui->providersTableWidget->setItem(i, 6, contactNameItem);

        // Email
        QTableWidgetItem *emailItem = new QTableWidgetItem();
        QString emailItemValue = provider->getEmail();
        emailItem->setText(emailItemValue);
        ui->providersTableWidget->setItem(i, 7, emailItem);

        // Address Street
        QTableWidgetItem *addressStreetItem = new QTableWidgetItem();
        QString addressStreetItemValue = provider->getAddressStreet();
        addressStreetItem->setText(addressStreetItemValue);
        ui->providersTableWidget->setItem(i, 8, addressStreetItem);

        // Address Number
        QTableWidgetItem *addressNumberItem = new QTableWidgetItem();
        int addressNumberItemValue = provider->getAddressNumber();
        addressNumberItem->setText(QString::number(addressNumberItemValue));
        ui->providersTableWidget->setItem(i, 9, addressNumberItem);

        // Address Complement
        QTableWidgetItem *addressComplementItem = new QTableWidgetItem();
        QString addressComplementItemValue = provider->getAddressComplement();
        addressComplementItem->setText(addressComplementItemValue);
        ui->providersTableWidget->setItem(i, 10, addressComplementItem);

        // Address Square
        QTableWidgetItem *addressSquareItem = new QTableWidgetItem();
        QString addressSquareItemValue = provider->getAddressSquare();
        addressSquareItem->setText(addressSquareItemValue);
        ui->providersTableWidget->setItem(i, 11, addressSquareItem);

        // Address City
        QTableWidgetItem *addressCityItem = new QTableWidgetItem();
        QString addressCityItemValue = provider->getAddressCity();
        addressCityItem->setText(addressCityItemValue);
        ui->providersTableWidget->setItem(i, 12, addressCityItem);

        // Address State
        QTableWidgetItem *addressStateItem = new QTableWidgetItem();
        QString addressStateItemValue = provider->getAddressState();
        addressStateItem->setText(addressStateItemValue);
        ui->providersTableWidget->setItem(i, 13, addressStateItem);

        // Address Postal Code
        QTableWidgetItem *addressPostalCodeItem = new QTableWidgetItem();
        QString addressPostalCodeItemValue = provider->getAddressPostalCode();
        addressPostalCodeItem->setText(addressPostalCodeItemValue);
        ui->providersTableWidget->setItem(i, 14, addressPostalCodeItem);
    }

    ui->providersTableWidget->resizeColumnsToContents();
    ui->providersTableWidget->selectRow(0);

    if(count == 0){
        ui->editProviderpushButton->setEnabled(false);
    }
    else{
        ui->editProviderpushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void ProvidersListView::onAddNewProvider()
{
    this->parentMainWindow->addFormAddProviderToMDI();
}

void ProvidersListView::onEditProvider()
{
    QTableWidgetItem *item = ui->providersTableWidget->selectedItems().at(0);
    QString cnpj = item->text();
    Provider *provider = providerController->getProviderByCNPJ(cnpj);
    this->parentMainWindow->addFormEditProviderToMDI(provider);
}

void ProvidersListView::onRemoveProvider()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this provider?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->providersTableWidget->selectedItems().at(0);
        QString cnpj = item->text();
        Utilities::StatusControl status = providerController->removeProvider(cnpj);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listProviders();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered CNPJ doesn't belong to any provider of database"),
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
