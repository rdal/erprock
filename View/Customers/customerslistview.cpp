#include "customerslistview.h"
#include "ui_customerslistview.h"
#include <QMessageBox>

CustomersListView::CustomersListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomersListView)
{
    ui->setupUi(this);

    connect(ui->addEnterpriseCustomerPushButton, SIGNAL(released()), this, SLOT(onAddNewEnterpriseCustomer()));
    connect(ui->editEnterpriseCustomerPushButton, SIGNAL(released()), this, SLOT(onEditEnterpriseCustomer()));
    connect(ui->removeEnterpriseCustomerPushButton, SIGNAL(released()), this, SLOT(onRemoveEnterpriseCustomer()));

    connect(ui->addPhysicalCustomerPushButton, SIGNAL(released()), this, SLOT(onAddNewPhysicalCustomer()));
    connect(ui->editPhysicalCustomerPushButton, SIGNAL(released()), this, SLOT(onEditPhysicalCustomer()));
    connect(ui->removePhysicalCustomerPushButton, SIGNAL(released()), this, SLOT(onRemovePhysicalCustomer()));

    customerController = new CustomerController();
    listEnterpriseCustomers();
    listPhysicalCustomers();
}

CustomersListView::~CustomersListView()
{
    delete ui;

    delete customerController;
}

void CustomersListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void CustomersListView::listEnterpriseCustomers()
{
    QList<EnterpriseCustomer*> *enterpriseCustomers = customerController->getEnterpriseCustomers();

    int count = enterpriseCustomers->count();
    ui->enterpriseCustomerTableWidget->clearContents();
    ui->enterpriseCustomerTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        EnterpriseCustomer *enterpriseCustomer = enterpriseCustomers->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->enterpriseCustomerTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // CNPJ
        QTableWidgetItem *cnpjItem = new QTableWidgetItem();
        QString cnpjItemValue = enterpriseCustomer->getCnpj();
        cnpjItem->setText(cnpjItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 0, cnpjItem);

        // State Number
        QTableWidgetItem *stateNumberItem = new QTableWidgetItem();
        QString stateNumberItemValue = enterpriseCustomer->getStateNumber();
        stateNumberItem->setText(stateNumberItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 1, stateNumberItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = enterpriseCustomer->getName();
        nameItem->setText(nameItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 2, nameItem);

        // Fantasy Name
        QTableWidgetItem *fantasyNameItem = new QTableWidgetItem();
        QString fantasyNameItemValue = enterpriseCustomer->getFantasyName();
        fantasyNameItem->setText(fantasyNameItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 3, fantasyNameItem);

        // Phone Number
        QTableWidgetItem *phoneNumberItem = new QTableWidgetItem();
        QString phoneNumberItemValue = enterpriseCustomer->getPhoneNumber();
        phoneNumberItem->setText(phoneNumberItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 4, phoneNumberItem);

        // Fax Number
        QTableWidgetItem *faxNumberItem = new QTableWidgetItem();
        QString faxNumberItemValue = enterpriseCustomer->getFaxNumber();
        faxNumberItem->setText(faxNumberItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 5, faxNumberItem);

        // Contact Name
        QTableWidgetItem *contactNameItem = new QTableWidgetItem();
        QString contactNameItemValue = enterpriseCustomer->getContactName();
        contactNameItem->setText(contactNameItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 6, contactNameItem);

        // Email
        QTableWidgetItem *emailItem = new QTableWidgetItem();
        QString emailItemValue = enterpriseCustomer->getEmail();
        emailItem->setText(emailItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 7, emailItem);

        // Address Street
        QTableWidgetItem *addressStreetItem = new QTableWidgetItem();
        QString addressStreetItemValue = enterpriseCustomer->getAddressStreet();
        addressStreetItem->setText(addressStreetItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 8, addressStreetItem);

        // Address Number
        QTableWidgetItem *addressNumberItem = new QTableWidgetItem();
        int addressNumberItemValue = enterpriseCustomer->getAddressNumber();
        addressNumberItem->setText(QString::number(addressNumberItemValue));
        ui->enterpriseCustomerTableWidget->setItem(i, 9, addressNumberItem);

        // Address Complement
        QTableWidgetItem *addressComplementItem = new QTableWidgetItem();
        QString addressComplementItemValue = enterpriseCustomer->getAddressComplement();
        addressComplementItem->setText(addressComplementItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 10, addressComplementItem);

        // Address Square
        QTableWidgetItem *addressSquareItem = new QTableWidgetItem();
        QString addressSquareItemValue = enterpriseCustomer->getAddressSquare();
        addressSquareItem->setText(addressSquareItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 11, addressSquareItem);

        // Address City
        QTableWidgetItem *addressCityItem = new QTableWidgetItem();
        QString addressCityItemValue = enterpriseCustomer->getAddressCity();
        addressCityItem->setText(addressCityItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 12, addressCityItem);

        // Address State
        QTableWidgetItem *addressStateItem = new QTableWidgetItem();
        QString addressStateItemValue = enterpriseCustomer->getAddressState();
        addressStateItem->setText(addressStateItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 13, addressStateItem);

        // Address Postal Code
        QTableWidgetItem *addressPostalCodeItem = new QTableWidgetItem();
        QString addressPostalCodeItemValue = enterpriseCustomer->getAddressPostalCode();
        addressPostalCodeItem->setText(addressPostalCodeItemValue);
        ui->enterpriseCustomerTableWidget->setItem(i, 14, addressPostalCodeItem);
    }

    ui->enterpriseCustomerTableWidget->resizeColumnsToContents();
    ui->enterpriseCustomerTableWidget->selectRow(0);

    if(count == 0){
        ui->editEnterpriseCustomerPushButton->setEnabled(false);
    }
    else{
        ui->editEnterpriseCustomerPushButton->setEnabled(true);
    }
}

void CustomersListView::listPhysicalCustomers()
{
    QList<PhysicalCustomer*> *physicalCustomers = customerController->getPhysicalCustomers();

    int count = physicalCustomers->count();
    ui->physicalCustomerTableWidget->clearContents();
    ui->physicalCustomerTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        PhysicalCustomer *physicalCustomer = physicalCustomers->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->physicalCustomerTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // CPF
        QTableWidgetItem *cpfItem = new QTableWidgetItem();
        QString cpfItemValue = physicalCustomer->getCpf();
        cpfItem->setText(cpfItemValue);
        ui->physicalCustomerTableWidget->setItem(i, 0, cpfItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = physicalCustomer->getName();
        nameItem->setText(nameItemValue);
        ui->physicalCustomerTableWidget->setItem(i, 1, nameItem);

        // Birth Date
        QTableWidgetItem *birthDateItem = new QTableWidgetItem();
        QDateTime birthDateItemValue = physicalCustomer->getBirthDate();
        birthDateItem->setText(birthDateItemValue.toString(PhysicalCustomer::DATE_FORMAT));
        ui->physicalCustomerTableWidget->setItem(i, 2, birthDateItem);

        // Phone Number
        QTableWidgetItem *phoneNumberItem = new QTableWidgetItem();
        QString phoneNumberItemValue = physicalCustomer->getPhoneNumber();
        phoneNumberItem->setText(phoneNumberItemValue);
        ui->physicalCustomerTableWidget->setItem(i, 3, phoneNumberItem);

        // Email
        QTableWidgetItem *emailItem = new QTableWidgetItem();
        QString emailItemValue = physicalCustomer->getEmail();
        emailItem->setText(emailItemValue);
        ui->physicalCustomerTableWidget->setItem(i, 4, emailItem);

        // Address Street
        QTableWidgetItem *addressStreetItem = new QTableWidgetItem();
        QString addressStreetItemValue = physicalCustomer->getAddressStreet();
        addressStreetItem->setText(addressStreetItemValue);
        ui->physicalCustomerTableWidget->setItem(i, 5, addressStreetItem);

        // Address Number
        QTableWidgetItem *addressNumberItem = new QTableWidgetItem();
        int addressNumberItemValue = physicalCustomer->getAddressNumber();
        addressNumberItem->setText(QString::number(addressNumberItemValue));
        ui->physicalCustomerTableWidget->setItem(i, 6, addressNumberItem);

        // Address Complement
        QTableWidgetItem *addressComplementItem = new QTableWidgetItem();
        QString addressComplementItemValue = physicalCustomer->getAddressComplement();
        addressComplementItem->setText(addressComplementItemValue);
        ui->physicalCustomerTableWidget->setItem(i, 7, addressComplementItem);

        // Address Square
        QTableWidgetItem *addressSquareItem = new QTableWidgetItem();
        QString addressSquareItemValue = physicalCustomer->getAddressSquare();
        addressSquareItem->setText(addressSquareItemValue);
        ui->physicalCustomerTableWidget->setItem(i, 8, addressSquareItem);

        // Address City
        QTableWidgetItem *addressCityItem = new QTableWidgetItem();
        QString addressCityItemValue = physicalCustomer->getAddressCity();
        addressCityItem->setText(addressCityItemValue);
        ui->physicalCustomerTableWidget->setItem(i, 9, addressCityItem);

        // Address State
        QTableWidgetItem *addressStateItem = new QTableWidgetItem();
        QString addressStateItemValue = physicalCustomer->getAddressState();
        addressStateItem->setText(addressStateItemValue);
        ui->physicalCustomerTableWidget->setItem(i, 10, addressStateItem);

        // Address Postal Code
        QTableWidgetItem *addressPostalCodeItem = new QTableWidgetItem();
        QString addressPostalCodeItemValue = physicalCustomer->getAddressPostalCode();
        addressPostalCodeItem->setText(addressPostalCodeItemValue);
        ui->physicalCustomerTableWidget->setItem(i, 11, addressPostalCodeItem);
    }

    ui->physicalCustomerTableWidget->resizeColumnsToContents();
    ui->physicalCustomerTableWidget->selectRow(0);

    if(count == 0){
        ui->editPhysicalCustomerPushButton->setEnabled(false);
    }
    else{
        ui->editPhysicalCustomerPushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void CustomersListView::onAddNewEnterpriseCustomer()
{
    this->parentMainWindow->addFormAddEnterpriseCustomerToMDI();
}

void CustomersListView::onEditEnterpriseCustomer()
{
    QTableWidgetItem *item = ui->enterpriseCustomerTableWidget->selectedItems().at(0);
    QString cnpj = item->text();
    EnterpriseCustomer *enterpriseCustomer = (EnterpriseCustomer*)customerController->getCustomerById(cnpj);
    this->parentMainWindow->addFormEditEnterpriseCustomerToMDI(enterpriseCustomer);
}

void CustomersListView::onRemoveEnterpriseCustomer()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this customer?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->enterpriseCustomerTableWidget->selectedItems().at(0);
        QString cnpj = item->text();
        Utilities::StatusControl status = customerController->removeCustomer(cnpj);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listEnterpriseCustomers();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered CNPJ doesn't belong to any customer of database"),
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

void CustomersListView::onAddNewPhysicalCustomer()
{
    this->parentMainWindow->addFormAddPhysicalCustomerToMDI();
}

void CustomersListView::onEditPhysicalCustomer()
{
    QTableWidgetItem *item = ui->physicalCustomerTableWidget->selectedItems().at(0);
    QString cpf = item->text();
    PhysicalCustomer *physicalCustomer = (PhysicalCustomer*)customerController->getCustomerById(cpf);
    this->parentMainWindow->addFormEditPhysicalCustomerToMDI(physicalCustomer);
}

void CustomersListView::onRemovePhysicalCustomer()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this customer?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->physicalCustomerTableWidget->selectedItems().at(0);
        QString cpf = item->text();
        Utilities::StatusControl status = customerController->removeCustomer(cpf);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listPhysicalCustomers();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered CNPJ doesn't belong to any customer of database"),
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
