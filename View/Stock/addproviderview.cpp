#include "addproviderview.h"
#include "ui_addproviderview.h"

#include <QMessageBox>

AddProviderView::AddProviderView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProviderView)
{
    ui->setupUi(this);

    this->parent = (ProvidersListView*)parent;
    init();

    QString title = QApplication::translate("AddProviderView", "Add new provider", 0);
    setWindowTitle(title);
    ui->cnpjLineEdit->setReadOnly(false);

    this->editingProvider = NULL;
}

AddProviderView::AddProviderView(Provider *provider, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProviderView)
{
    ui->setupUi(this);

    this->parent = (ProvidersListView*)parent;
    init();

    QString title = QApplication::translate("AddProviderView", "Edit provider", 0);
    setWindowTitle(title);
    ui->cnpjLineEdit->setReadOnly(true);

    this->editingProvider = provider;

    ui->cnpjLineEdit->setText(provider->getCNPJ());
    ui->stateNumberLineEdit->setText(provider->getStateNumber());
    ui->nameLineEdit->setText(provider->getName());
    ui->fantasyNameLineEdit->setText(provider->getFantasyName());
    ui->phoneNumberLineEdit->setText(provider->getPhoneNumber());
    ui->faxNumberLineEdit->setText(provider->getFaxNumber());
    ui->contactNameLineEdit->setText(provider->getContactName());
    ui->emailLineEdit->setText(provider->getEmail());
    ui->addressStreetLineEdit->setText(provider->getAddressStreet());
    ui->addressNumberLineEdit->setText(QString::number(provider->getAddressNumber()));
    ui->addressComplementLineEdit->setText(provider->getAddressComplement());
    ui->addressSquareLineEdit->setText(provider->getAddressSquare());
    ui->addressCityLineEdit->setText(provider->getAddressCity());
    ui->addressStateLineEdit->setText(provider->getAddressState());
    ui->addressPostalCodeLineEdit->setText(provider->getAddressPostalCode());
}

AddProviderView::~AddProviderView()
{
    delete ui;
    //parentMainWindow = NULL;
//    parent = NULL;
    delete editingProvider;
}

void AddProviderView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddProvider()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddProviderView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddProviderView::proceedToAddProvider()
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

        Provider *provider;
        ProviderController *providerController = new ProviderController();
        provider = new Provider(cnpj, stateNumber, name, fantasyName, phoneNumber, faxNumber, contactName,
                                        email, addressStreet, addressNumber, addressComplement, addressSquare,
                                        addressCity, addressState, addressPostalCode);

        Utilities::StatusControl status = (this->editingProvider) ?
                                          providerController->updateProvider(provider) :
                                          providerController->addProvider(provider);

        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listProviders();
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
                                      tr("There is already a provider registered with this cnpj"),
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

void AddProviderView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
