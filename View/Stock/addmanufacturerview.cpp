#include "addmanufacturerview.h"
#include "ui_addmanufacturerview.h"

#include <QMessageBox>

AddManufacturerView::AddManufacturerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddManufacturerView)
{
    ui->setupUi(this);

    this->parent = (ManufacturersListView*)parent;
    init();

    QString title = QApplication::translate("AddManufacturerView", "Add new manufacturer", 0);
    setWindowTitle(title);
    ui->cnpjLineEdit->setReadOnly(false);

    this->editingManufacturer = NULL;
}

AddManufacturerView::AddManufacturerView(Manufacturer *manufacturer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddManufacturerView)
{
    ui->setupUi(this);

    this->parent = (ManufacturersListView*)parent;
    init();

    QString title = QApplication::translate("AddManufacturerView", "Edit manufacturer", 0);
    setWindowTitle(title);
    ui->cnpjLineEdit->setReadOnly(true);

    this->editingManufacturer = manufacturer;

    ui->cnpjLineEdit->setText(manufacturer->getCNPJ());
    ui->stateNumberLineEdit->setText(manufacturer->getStateNumber());
    ui->nameLineEdit->setText(manufacturer->getName());
    ui->fantasyNameLineEdit->setText(manufacturer->getFantasyName());
    ui->phoneNumberLineEdit->setText(manufacturer->getPhoneNumber());
    ui->faxNumberLineEdit->setText(manufacturer->getFaxNumber());
    ui->contactNameLineEdit->setText(manufacturer->getContactName());
    ui->emailLineEdit->setText(manufacturer->getEmail());
    ui->addressStreetLineEdit->setText(manufacturer->getAddressStreet());
    ui->addressNumberLineEdit->setText(QString::number(manufacturer->getAddressNumber()));
    ui->addressComplementLineEdit->setText(manufacturer->getAddressComplement());
    ui->addressSquareLineEdit->setText(manufacturer->getAddressSquare());
    ui->addressCityLineEdit->setText(manufacturer->getAddressCity());
    ui->addressStateLineEdit->setText(manufacturer->getAddressState());
    ui->addressPostalCodeLineEdit->setText(manufacturer->getAddressPostalCode());
}

AddManufacturerView::~AddManufacturerView()
{
    delete ui;

//    //parentMainWindow = NULL;
//    parent = NULL;
    delete editingManufacturer;
}

void AddManufacturerView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddManufacturer()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddManufacturerView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddManufacturerView::proceedToAddManufacturer()
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

        Manufacturer *manufacturer;
        ManufacturerController *manufacturerController = new ManufacturerController();
        manufacturer = new Manufacturer(cnpj, stateNumber, name, fantasyName, phoneNumber, faxNumber, contactName,
                                        email, addressStreet, addressNumber, addressComplement, addressSquare,
                                        addressCity, addressState, addressPostalCode);

        Utilities::StatusControl status = (this->editingManufacturer) ?
                                          manufacturerController->updateManufacturer(manufacturer) :
                                          manufacturerController->addManufacturer(manufacturer);

        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listManufacturers();
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
                                      tr("There is already an manufacturer registered with this cnpj"),
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

void AddManufacturerView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
