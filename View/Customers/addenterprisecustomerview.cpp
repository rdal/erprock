#include "addenterprisecustomerview.h"
#include "ui_addenterprisecustomerview.h"

#include <QMessageBox>

AddEnterpriseCustomerView::AddEnterpriseCustomerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddEnterpriseCustomerView)
{
    ui->setupUi(this);

    this->parent = (CustomersListView*)parent;
    init();

    QString title = QApplication::translate("AddEnterpriseCustomerView", "Add new enterprise customer", 0);
    setWindowTitle(title);
    ui->cnpjLineEdit->setReadOnly(false);

    this->editingEnterpriseCustomer = NULL;
}

AddEnterpriseCustomerView::AddEnterpriseCustomerView(EnterpriseCustomer *enterpriseCustomer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddEnterpriseCustomerView)
{
    ui->setupUi(this);

    this->parent = (CustomersListView*)parent;
    init();

    QString title = QApplication::translate("AddEnterpriseCustomerView", "Edit enterprise customer", 0);
    setWindowTitle(title);
    ui->cnpjLineEdit->setReadOnly(true);

    this->editingEnterpriseCustomer = enterpriseCustomer;

    ui->cnpjLineEdit->setText(enterpriseCustomer->getCnpj());
    ui->stateNumberLineEdit->setText(enterpriseCustomer->getStateNumber());
    ui->nameLineEdit->setText(enterpriseCustomer->getName());
    ui->fantasyNameLineEdit->setText(enterpriseCustomer->getFantasyName());
    ui->phoneNumberLineEdit->setText(enterpriseCustomer->getPhoneNumber());
    ui->faxNumberLineEdit->setText(enterpriseCustomer->getFaxNumber());
    ui->contactNameLineEdit->setText(enterpriseCustomer->getContactName());
    ui->emailLineEdit->setText(enterpriseCustomer->getEmail());
    ui->addressStreetLineEdit->setText(enterpriseCustomer->getAddressStreet());
    ui->addressNumberLineEdit->setText(QString::number(enterpriseCustomer->getAddressNumber()));
    ui->addressComplementLineEdit->setText(enterpriseCustomer->getAddressComplement());
    ui->addressSquareLineEdit->setText(enterpriseCustomer->getAddressSquare());
    ui->addressCityLineEdit->setText(enterpriseCustomer->getAddressCity());
    ui->addressStateLineEdit->setText(enterpriseCustomer->getAddressState());
    ui->addressPostalCodeLineEdit->setText(enterpriseCustomer->getAddressPostalCode());
}

AddEnterpriseCustomerView::~AddEnterpriseCustomerView()
{
    delete ui;
    //parentMainWindow = NULL;
//    parent = NULL;
    delete editingEnterpriseCustomer;
}

void AddEnterpriseCustomerView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddEnterpriseCustomer()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddEnterpriseCustomerView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddEnterpriseCustomerView::proceedToAddEnterpriseCustomer()
{
    bool okAddressNUmber;
    QString cnpj = Utilities::stripCNPJChars(ui->cnpjLineEdit->text());
    QString stateNumber = ui->stateNumberLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString fantasyName = ui->fantasyNameLineEdit->text();
    QString phoneNumber = ui->phoneNumberLineEdit->text();
    QString faxNumber = ui->faxNumberLineEdit->text();
    QString contactName = ui->contactNameLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QString addressStreet = ui->addressStreetLineEdit->text();
    int addressNumber = ui->addressNumberLineEdit->text().toInt(&okAddressNUmber);
    QString addressComplement = ui->addressComplementLineEdit->text();
    QString addressSquare = ui->addressSquareLineEdit->text();
    QString addressCity = ui->addressCityLineEdit->text();
    QString addressState = ui->addressStateLineEdit->text();
    QString addressPostalCode = ui->addressPostalCodeLineEdit->text();

    if(cnpj.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill cnpj field"),
                              QMessageBox::Ok);
    }

    else if(name.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill name field"),
                              QMessageBox::Ok);
    }
    else if(ui->addressNumberLineEdit->text().count() >0 && !okAddressNUmber)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Invalid number format. It must contain only digits."),
                              QMessageBox::Ok);
    }
    else{

        EnterpriseCustomer *enterpriseCustomer;
        CustomerController *customerController = new CustomerController();
        enterpriseCustomer = new EnterpriseCustomer(cnpj, stateNumber, name, fantasyName, phoneNumber, faxNumber, contactName,
                                        email, addressStreet, addressNumber, addressComplement, addressSquare,
                                        addressCity, addressState, addressPostalCode);

        Utilities::StatusControl status = (this->editingEnterpriseCustomer) ?
                                          customerController->updateCustomer(enterpriseCustomer) :
                                          customerController->addCustomer(enterpriseCustomer);

        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listEnterpriseCustomers();
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
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already an enterprise customer registered with this cnpj"),
                                      QMessageBox::Ok);
                break;
            }
            case Utilities::INVALID_ID:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The cnpj specified is not valid"),
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

void AddEnterpriseCustomerView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
