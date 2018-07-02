#include "addstoreview.h"
#include "ui_addstoreview.h"

#include <QMessageBox>

AddStoreView::AddStoreView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddStoreView)
{
    ui->setupUi(this);

    this->parent = (StoresListView*)parent;
    init();

    QString title = QApplication::translate("AddStoreView", "Add new store", 0);
    setWindowTitle(title);
    ui->cnpjLineEdit->setReadOnly(false);

    this->editingStore = NULL;
}

AddStoreView::AddStoreView(Store *store, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddStoreView)
{
    ui->setupUi(this);

    this->parent = (StoresListView*)parent;
    init();

    QString title = QApplication::translate("AddStoreView", "Edit store", 0);
    setWindowTitle(title);
    ui->cnpjLineEdit->setReadOnly(true);

    this->editingStore = store;

    ui->cnpjLineEdit->setText(store->getCNPJ());
    ui->stateNumberLineEdit->setText(store->getStateNumber());
    ui->nameLineEdit->setText(store->getName());
    ui->fantasyNameLineEdit->setText(store->getFantasyName());
    ui->phoneNumberLineEdit->setText(store->getPhoneNumber());
    ui->faxNumberLineEdit->setText(store->getFaxNumber());
    ui->contactNameLineEdit->setText(store->getContactName());
    ui->emailLineEdit->setText(store->getEmail());
    ui->addressStreetLineEdit->setText(store->getAddressStreet());
    ui->addressNumberLineEdit->setText(QString::number(store->getAddressNumber()));
    ui->addressComplementLineEdit->setText(store->getAddressComplement());
    ui->addressSquareLineEdit->setText(store->getAddressSquare());
    ui->addressCityLineEdit->setText(store->getAddressCity());
    ui->addressStateLineEdit->setText(store->getAddressState());
    ui->addressPostalCodeLineEdit->setText(store->getAddressPostalCode());
}

AddStoreView::~AddStoreView()
{
    delete ui;

    delete editingStore;
}

void AddStoreView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddStore()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddStoreView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddStoreView::proceedToAddStore()
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

        Store *store;
        StoreController *storeController = new StoreController();
        store = new Store(cnpj, stateNumber, name, fantasyName, phoneNumber, faxNumber, contactName,
                                        email, addressStreet, addressNumber, addressComplement, addressSquare,
                                        addressCity, addressState, addressPostalCode);

        Utilities::StatusControl status = (this->editingStore) ?
                                          storeController->updateStore(store) :
                                          storeController->addStore(store);

        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listStores();
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
                                      tr("There is already a store registered with this cnpj"),
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

void AddStoreView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
