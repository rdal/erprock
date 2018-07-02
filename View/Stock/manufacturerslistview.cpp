#include "manufacturerslistview.h"
#include "ui_manufacturerslistview.h"
#include <QMessageBox>

ManufacturersListView::ManufacturersListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManufacturersListView)
{
    ui->setupUi(this);

    connect(ui->addManufacturerpushButton, SIGNAL(released()), this, SLOT(onAddNewManufacturer()));
    connect(ui->editManufacturerpushButton, SIGNAL(released()), this, SLOT(onEditManufacturer()));
    connect(ui->removeManufacturerpushButton, SIGNAL(released()), this, SLOT(onRemoveManufacturer()));

    manufacturerController = new ManufacturerController();
    listManufacturers();
}

ManufacturersListView::~ManufacturersListView()
{
    delete ui;

    //parentMainWindow = NULL;
    delete manufacturerController;
}

void ManufacturersListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void ManufacturersListView::listManufacturers()
{
    QList<Manufacturer*> *manufacturers = manufacturerController->getManufacturers();

    int count = manufacturers->count();
    ui->manufacturersTableWidget->clearContents();
    ui->manufacturersTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        Manufacturer *manufacturer = manufacturers->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->manufacturersTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // CNPJ
        QTableWidgetItem *cnpjItem = new QTableWidgetItem();
        QString cnpjItemValue = manufacturer->getCNPJ();
        cnpjItem->setText(cnpjItemValue);
        ui->manufacturersTableWidget->setItem(i, 0, cnpjItem);

        // State Number
        QTableWidgetItem *stateNumberItem = new QTableWidgetItem();
        QString stateNumberItemValue = manufacturer->getStateNumber();
        stateNumberItem->setText(stateNumberItemValue);
        ui->manufacturersTableWidget->setItem(i, 1, stateNumberItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = manufacturer->getName();
        nameItem->setText(nameItemValue);
        ui->manufacturersTableWidget->setItem(i, 2, nameItem);

        // Fantasy Name
        QTableWidgetItem *fantasyNameItem = new QTableWidgetItem();
        QString fantasyNameItemValue = manufacturer->getFantasyName();
        fantasyNameItem->setText(fantasyNameItemValue);
        ui->manufacturersTableWidget->setItem(i, 3, fantasyNameItem);

        // Phone Number
        QTableWidgetItem *phoneNumberItem = new QTableWidgetItem();
        QString phoneNumberItemValue = manufacturer->getPhoneNumber();
        phoneNumberItem->setText(phoneNumberItemValue);
        ui->manufacturersTableWidget->setItem(i, 4, phoneNumberItem);

        // Fax Number
        QTableWidgetItem *faxNumberItem = new QTableWidgetItem();
        QString faxNumberItemValue = manufacturer->getFaxNumber();
        faxNumberItem->setText(faxNumberItemValue);
        ui->manufacturersTableWidget->setItem(i, 5, faxNumberItem);

        // Contact Name
        QTableWidgetItem *contactNameItem = new QTableWidgetItem();
        QString contactNameItemValue = manufacturer->getContactName();
        contactNameItem->setText(contactNameItemValue);
        ui->manufacturersTableWidget->setItem(i, 6, contactNameItem);

        // Email
        QTableWidgetItem *emailItem = new QTableWidgetItem();
        QString emailItemValue = manufacturer->getEmail();
        emailItem->setText(emailItemValue);
        ui->manufacturersTableWidget->setItem(i, 7, emailItem);

        // Address Street
        QTableWidgetItem *addressStreetItem = new QTableWidgetItem();
        QString addressStreetItemValue = manufacturer->getAddressStreet();
        addressStreetItem->setText(addressStreetItemValue);
        ui->manufacturersTableWidget->setItem(i, 8, addressStreetItem);

        // Address Number
        QTableWidgetItem *addressNumberItem = new QTableWidgetItem();
        int addressNumberItemValue = manufacturer->getAddressNumber();
        addressNumberItem->setText(QString::number(addressNumberItemValue));
        ui->manufacturersTableWidget->setItem(i, 9, addressNumberItem);

        // Address Complement
        QTableWidgetItem *addressComplementItem = new QTableWidgetItem();
        QString addressComplementItemValue = manufacturer->getAddressComplement();
        addressComplementItem->setText(addressComplementItemValue);
        ui->manufacturersTableWidget->setItem(i, 10, addressComplementItem);

        // Address Square
        QTableWidgetItem *addressSquareItem = new QTableWidgetItem();
        QString addressSquareItemValue = manufacturer->getAddressSquare();
        addressSquareItem->setText(addressSquareItemValue);
        ui->manufacturersTableWidget->setItem(i, 11, addressSquareItem);

        // Address City
        QTableWidgetItem *addressCityItem = new QTableWidgetItem();
        QString addressCityItemValue = manufacturer->getAddressCity();
        addressCityItem->setText(addressCityItemValue);
        ui->manufacturersTableWidget->setItem(i, 12, addressCityItem);

        // Address State
        QTableWidgetItem *addressStateItem = new QTableWidgetItem();
        QString addressStateItemValue = manufacturer->getAddressState();
        addressStateItem->setText(addressStateItemValue);
        ui->manufacturersTableWidget->setItem(i, 13, addressStateItem);

        // Address Postal Code
        QTableWidgetItem *addressPostalCodeItem = new QTableWidgetItem();
        QString addressPostalCodeItemValue = manufacturer->getAddressPostalCode();
        addressPostalCodeItem->setText(addressPostalCodeItemValue);
        ui->manufacturersTableWidget->setItem(i, 14, addressPostalCodeItem);
    }

    ui->manufacturersTableWidget->resizeColumnsToContents();
    ui->manufacturersTableWidget->selectRow(0);

    if(count == 0){
        ui->editManufacturerpushButton->setEnabled(false);
    }
    else{
        ui->editManufacturerpushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void ManufacturersListView::onAddNewManufacturer()
{
    this->parentMainWindow->addFormAddManufacturerToMDI();
}

void ManufacturersListView::onEditManufacturer()
{
    QTableWidgetItem *item = ui->manufacturersTableWidget->selectedItems().at(0);
    QString cnpj = item->text();
    Manufacturer *manufacturer = manufacturerController->getManufacturerByCNPJ(cnpj);
    this->parentMainWindow->addFormEditManufacturerToMDI(manufacturer);
}

void ManufacturersListView::onRemoveManufacturer()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this manufacturer?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->manufacturersTableWidget->selectedItems().at(0);
        QString cnpj = item->text();
        Utilities::StatusControl status = manufacturerController->removeManufacturer(cnpj);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listManufacturers();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered CNPJ doesn't belong to any manufacturer of database"),
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
