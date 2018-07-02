#include "addphysicalcustomerview.h"
#include "ui_addphysicalcustomerview.h"

#include <QMessageBox>

AddPhysicalCustomerView::AddPhysicalCustomerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPhysicalCustomerView)
{
    ui->setupUi(this);

    this->parent = (CustomersListView*)parent;
    init();

    QString title = QApplication::translate("AddPhysicalCustomerView", "Add new physical customer", 0);
    setWindowTitle(title);
    ui->cpfLineEdit->setReadOnly(false);

    ui->birthDateDateEdit->setDateTime(QDateTime::currentDateTime());

    this->editingPhysicalCustomer = NULL;
}

AddPhysicalCustomerView::AddPhysicalCustomerView(PhysicalCustomer *physicalCustomer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPhysicalCustomerView)
{
    ui->setupUi(this);

    this->parent = (CustomersListView*)parent;
    init();

    QString title = QApplication::translate("AddPhysicalCustomerView", "Edit physical customer", 0);
    setWindowTitle(title);
    ui->cpfLineEdit->setReadOnly(true);

    this->editingPhysicalCustomer = physicalCustomer;

    ui->cpfLineEdit->setText(physicalCustomer->getCpf());
    ui->nameLineEdit->setText(physicalCustomer->getName());
    ui->birthDateDateEdit->setDateTime(physicalCustomer->getBirthDate());
    ui->phoneNumberLineEdit->setText(physicalCustomer->getPhoneNumber());
    ui->emailLineEdit->setText(physicalCustomer->getEmail());
    ui->addressStreetLineEdit->setText(physicalCustomer->getAddressStreet());
    ui->addressNumberLineEdit->setText(QString::number(physicalCustomer->getAddressNumber()));
    ui->addressComplementLineEdit->setText(physicalCustomer->getAddressComplement());
    ui->addressSquareLineEdit->setText(physicalCustomer->getAddressSquare());
    ui->addressCityLineEdit->setText(physicalCustomer->getAddressCity());
    ui->addressStateLineEdit->setText(physicalCustomer->getAddressState());
    ui->addressPostalCodeLineEdit->setText(physicalCustomer->getAddressPostalCode());
}

AddPhysicalCustomerView::~AddPhysicalCustomerView()
{
    delete ui;

    delete editingPhysicalCustomer;
}

void AddPhysicalCustomerView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddPhysicalCustomer()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddPhysicalCustomerView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddPhysicalCustomerView::proceedToAddPhysicalCustomer()
{
    bool okAddressNUmber;
    QString cpf = Utilities::stripCPFChars(ui->cpfLineEdit->text());
    QString name = ui->nameLineEdit->text();
    QDateTime birthDate = ui->birthDateDateEdit->dateTime();
    QString phoneNumber = ui->phoneNumberLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QString addressStreet = ui->addressStreetLineEdit->text();
    int addressNumber = ui->addressNumberLineEdit->text().toInt(&okAddressNUmber);
    QString addressComplement = ui->addressComplementLineEdit->text();
    QString addressSquare = ui->addressSquareLineEdit->text();
    QString addressCity = ui->addressCityLineEdit->text();
    QString addressState = ui->addressStateLineEdit->text();
    QString addressPostalCode = ui->addressPostalCodeLineEdit->text();

    if(cpf.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill cpf field"),
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

        PhysicalCustomer *physicalCustomer;
        CustomerController *customerController = new CustomerController();
        physicalCustomer = new PhysicalCustomer(cpf, name, birthDate, phoneNumber, email, addressStreet,
                                                addressNumber, addressComplement, addressSquare, addressCity,
                                                addressState, addressPostalCode);

        Utilities::StatusControl status = (this->editingPhysicalCustomer) ?
                                          customerController->updateCustomer(physicalCustomer) :
                                          customerController->addCustomer(physicalCustomer);

        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listPhysicalCustomers();
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
                                      tr("There is already an physical customer registered with this cpf"),
                                      QMessageBox::Ok);
                break;
            }
            case Utilities::INVALID_ID:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The cpf specified is not valid"),
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

void AddPhysicalCustomerView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
