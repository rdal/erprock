#include "addpriceview.h"
#include "ui_addpriceview.h"
#include "storecontroller.h"

#include <QMessageBox>
#include <QDebug>

AddPriceView::AddPriceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPriceView)
{
    ui->setupUi(this);

    this->parent = (PricesListView*)parent;
    init();

    QString title = QApplication::translate("AddPriceView", "Add new price", 0);
    setWindowTitle(title);

    this->editingPrice = NULL;
}

AddPriceView::AddPriceView(Price *price, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPriceView)
{
    ui->setupUi(this);

    this->parent = (PricesListView*)parent;
    init();

    QString title = QApplication::translate("AddPriceView", "Edit price", 0);
    setWindowTitle(title);

    this->editingPrice = price;

    // Product
    ProductController *productController = new ProductController();
    this->chosenProduct = productController->getProductByCode(price->getProductCode());
    ui->productLineEdit->setText(this->chosenProduct->getName());

    // Value
    ui->valueDoubleSpinBox->setValue(price->getValue());

    // Store
    QString storerCnpj = price->getStoreCnpj();
    int idxStoreCnpj = ui->storeComboBox->findData(QVariant(storerCnpj));
    ui->storeComboBox->setCurrentIndex(idxStoreCnpj);

    // Name
    ui->nameLineEdit->setText(price->getName());

    delete productController;
}

AddPriceView::~AddPriceView()
{
    delete ui;

    if (editingPrice)
        delete editingPrice;

    if(productsListView)
        delete productsListView;
}

void AddPriceView::init()
{
    this->productsListView = NULL;
    this->chosenProduct = NULL;

    StoreController *storeController = new StoreController();
    QList<Store*> *storeObjects = storeController->getStores();

    ui->storeComboBox->clear();
    ui->storeComboBox->addItem(QApplication::translate("AddPriceView", "-- Select a store", 0), QVariant(""));

    int storesCount = storeObjects->count();
    for(int i=0; i<storesCount; i++)
    {
        QString name = ((Store*)storeObjects->at(i))->getName();
        ui->storeComboBox->addItem(name, QVariant(storeObjects->at(i)->getCNPJ()));
    }

    connect(ui->chooseProductToolButton, SIGNAL(released()), this, SLOT(openProductsWindow()));
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddPrice()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));

    delete storeController;
}

void AddPriceView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddPriceView::proceedToAddPrice()
{
    double value = ui->valueDoubleSpinBox->value();
    QString storeCnpj = ui->storeComboBox->itemData(ui->storeComboBox->currentIndex()).toString();
    QString name = ui->nameLineEdit->text();

    if(!chosenProduct)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select a product."),
                              QMessageBox::Ok);
    }
    else if(storeCnpj.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select a store where the product will be kept."),
                              QMessageBox::Ok);
    }
    else if(name.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill name field"),
                              QMessageBox::Ok);
    }
    else{

        PriceController *priceController = new PriceController();
        Utilities::StatusControl status = (this->editingPrice) ?
                                          priceController->updatePrice(new Price(this->editingPrice->getId(), this->chosenProduct->getCode(), value, storeCnpj, name)) :
                                          priceController->addPrice(new Price(this->chosenProduct->getCode(), value, storeCnpj, name));


        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listPrices();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("This product was already precified for this store"),
                                      QMessageBox::Ok);
                break;
            }
            case Utilities::ALREADY_EXISTS_NAME:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a price registered with this name"),
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

        delete priceController;
    }
}

void AddPriceView::hideAndClearFieldsData()
{
    emit aboutToClose();
}

void AddPriceView::openProductsWindow()
{
    this->chosenProduct = new Product("","",0,"","","","","","","","","","","","");
    this->productsListView = new ProductsListView();
    this->productsListView->setWindowMode(Utilities::CHOOSE_ITEM);
    this->productsListView->setProductObjectChosen(this->chosenProduct);
    connect(this->productsListView, SIGNAL(aboutToClose()), this, SLOT(onProductChosen()));
    this->productsListView->show();
}

void AddPriceView::onProductChosen()
{
    if(this->chosenProduct)
    {
        ui->productLineEdit->setText(this->chosenProduct->getName());
    }
}
