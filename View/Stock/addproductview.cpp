#include "addproductview.h"
#include "ui_addproductview.h"

#include <QMessageBox>

AddProductView::AddProductView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProductView)
{
    ui->setupUi(this);

    this->parent = (ProductsListView*)parent;
    init();

    QString title = QApplication::translate("AddProductView", "Add new product", 0);
    setWindowTitle(title);

    this->editingProduct = NULL;
}

AddProductView::AddProductView(Product *product, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProductView)
{
    ui->setupUi(this);

    this->parent = (ProductsListView*)parent;
    init();

    QString title = QApplication::translate("AddProductView", "Edit product", 0);
    setWindowTitle(title);

    this->editingProduct = product;

    ui->codeLineEdit->setText(product->getCode());
    ui->barCodeLineEdit->setText(product->getBarCode());

    int productCategoryId = product->getProductCategoryId();
    int idxProductCategory = ui->productCategoryComboBox->findData(QVariant(productCategoryId));
    ui->productCategoryComboBox->setCurrentIndex(idxProductCategory);

    QString manufacturerCnpj = product->getManufacturerCnpj();
    int idxManufacturerCnpj = ui->manufacturerComboBox->findData(QVariant(manufacturerCnpj));
    ui->manufacturerComboBox->setCurrentIndex(idxManufacturerCnpj);

    ui->nameLineEdit->setText(product->getName());
    ui->descriptionPlainTextEdit->setPlainText(product->getDescription());

    QString cstIcms = product->getCstIcms();
    int idxCstIcms = ui->icmsComboBox->findData(QVariant(cstIcms));
    ui->icmsComboBox->setCurrentIndex(idxCstIcms);

    QString cstIpi = product->getCstIpi();
    int idxCstIpi = ui->ipiComboBox->findData(QVariant(cstIpi));
    ui->ipiComboBox->setCurrentIndex(idxCstIpi);

    QString cstPis = product->getCstPis();
    int idxCstPis = ui->pisComboBox->findData(QVariant(cstPis));
    ui->pisComboBox->setCurrentIndex(idxCstPis);

    QString cstCofins = product->getCstCofins();
    int idxCstCofins = ui->cofinsComboBox->findData(QVariant(cstCofins));
    ui->cofinsComboBox->setCurrentIndex(idxCstCofins);

    QString icmsPercentName = product->getIcmsPercentName();
    int idxIcmsPercentName = ui->icmsPercentComboBox->findData(QVariant(icmsPercentName));
    ui->icmsPercentComboBox->setCurrentIndex(idxIcmsPercentName);

    QString ipiPercentName = product->getIpiPercentName();
    int idxIpiPercentName = ui->ipiPercentComboBox->findData(QVariant(ipiPercentName));
    ui->ipiPercentComboBox->setCurrentIndex(idxIpiPercentName);

    QString pisPercentName = product->getPisPercentName();
    int idxPisPercentName = ui->pisPercentComboBox->findData(QVariant(pisPercentName));
    ui->pisPercentComboBox->setCurrentIndex(idxPisPercentName);

    QString cofinsPercentName = product->getCofinsPercentName();
    int idxCofinsPercentName = ui->cofinsPercentComboBox->findData(QVariant(cofinsPercentName));
    ui->cofinsPercentComboBox->setCurrentIndex(idxCofinsPercentName);

    ui->cfopLineEdit->setText(product->getCfopCode());

}

AddProductView::~AddProductView()
{
    delete ui;

    delete productCategoryController;
//    parent = NULL;
    delete editingProduct;
    delete cstIcmsController;
    delete cstIpiController;
    delete cstPisController;
    delete cstCofinsController;
    delete taxRateController;

    if(cfopsListView)
        delete cfopsListView;
}

void AddProductView::init()
{
    //ui->tabWidget->setCurrentIndex(0);

    this->cfopsListView = NULL;

    //== Product category ==
    productCategoryController = new ProductCategoryController();
    QList<ProductCategory*> *productCategories = productCategoryController->getProductCategories();
    ui->productCategoryComboBox->clear();
    ui->productCategoryComboBox->addItem(QApplication::translate("AddProductView", "-- Select a product category", 0), QVariant(0));
    int categoriesCount = productCategories->count();
    for(int i=0; i<categoriesCount; i++)
    {
        ProductCategory *pc = productCategories->at(i);
        ui->productCategoryComboBox->addItem(pc->getName(), QVariant(pc->getId()));
    }

    //== Manufacturer ==
    manufacturerController = new ManufacturerController();
    QList<Manufacturer*> *manufacturers = manufacturerController->getManufacturers();
    ui->manufacturerComboBox->clear();
    ui->manufacturerComboBox->addItem(QApplication::translate("AddProductView", "-- Select a manufacturer", 0), QVariant(""));
    int manufacturersCount = manufacturers->count();
    for(int i=0; i<manufacturersCount; i++)
    {
        Manufacturer *manufacturer = manufacturers->at(i);
        ui->manufacturerComboBox->addItem(manufacturer->getName(), QVariant(manufacturer->getCNPJ()));
    }

//    //== Provider ==
//    providerController = new ProviderController();
//    QList<Provider*> *providers = providerController->getProviders();
//    ui->providerComboBox->clear();
//    ui->providerComboBox->addItem(QApplication::translate("AddProductView", "-- Select a provider", 0, QApplication::UnicodeUTF8), QVariant(""));
//    int providersCount = providers->count();
//    for(int i=0; i<providersCount; i++)
//    {
//        Provider *provider = providers->at(i);
//        ui->providerComboBox->addItem(provider->getName(), QVariant(provider->getCNPJ()));
//    }

    //== ICMS ==
    cstIcmsController = new CstIcmsController();
    QList<CstIcms*> *cstIcmss = cstIcmsController->getCstIcmss();
    ui->icmsComboBox->clear();
    ui->icmsComboBox->addItem(QApplication::translate("AddProductView", "-- Select a condition", 0), QVariant(""));
    int cstIcmsCount = cstIcmss->count();
    for(int i=0; i<cstIcmsCount; i++)
    {
        CstIcms *cstIcms = cstIcmss->at(i);
        ui->icmsComboBox->addItem(cstIcms->getCode() + " - " + cstIcms->getName(), QVariant(cstIcms->getCode()));
    }

    //== IPI ==
    cstIpiController = new CstIpiController();
    QList<CstIpi*> *cstIpis = cstIpiController->getCstIpis();
    ui->ipiComboBox->clear();
    ui->ipiComboBox->addItem(QApplication::translate("AddProductView", "-- Select a condition", 0), QVariant(""));
    int cstIpiCount = cstIpis->count();
    for(int i=0; i<cstIpiCount; i++)
    {
        CstIpi *cstIpi = cstIpis->at(i);
        ui->ipiComboBox->addItem(cstIpi->getCode() + " - " + cstIpi->getName(), QVariant(cstIpi->getCode()));
    }

    //== PIS ==
    cstPisController = new CstPisController();
    QList<CstPis*> *cstPiss = cstPisController->getCstPiss();
    ui->pisComboBox->clear();
    ui->pisComboBox->addItem(QApplication::translate("AddProductView", "-- Select a condition", 0), QVariant(""));
    int cstPisCount = cstPiss->count();
    for(int i=0; i<cstPisCount; i++)
    {
        CstPis *cstPis = cstPiss->at(i);
        ui->pisComboBox->addItem(cstPis->getCode() + " - " + cstPis->getName(), QVariant(cstPis->getCode()));
    }

    //== COFINS ==
    cstCofinsController = new CstCofinsController();
    QList<CstCofins*> *cstCofinss = cstCofinsController->getCstCofinss();
    ui->cofinsComboBox->clear();
    ui->cofinsComboBox->addItem(QApplication::translate("AddProductView", "-- Select a condition", 0), QVariant(""));
    int cstCofinsCount = cstCofinss->count();
    for(int i=0; i<cstCofinsCount; i++)
    {
        CstCofins *cstCofins = cstCofinss->at(i);
        ui->cofinsComboBox->addItem(cstCofins->getCode() + " - " + cstCofins->getName(), QVariant(cstCofins->getCode()));
    }

    //== TAX RATES ==
    taxRateController = new TaxRateController();
    QList<TaxRate*> *taxRates = taxRateController->getTaxRates();
    ui->icmsPercentComboBox->clear();
    ui->ipiPercentComboBox->clear();
    ui->pisPercentComboBox->clear();
    ui->cofinsPercentComboBox->clear();
    ui->icmsPercentComboBox->addItem(QApplication::translate("AddProductView", "-- Select a Tax Rate", 0), QVariant(""));
    ui->ipiPercentComboBox->addItem(QApplication::translate("AddProductView", "-- Select a Tax Rate", 0), QVariant(""));
    ui->pisPercentComboBox->addItem(QApplication::translate("AddProductView", "-- Select a Tax Rate", 0), QVariant(""));
    ui->cofinsPercentComboBox->addItem(QApplication::translate("AddProductView", "-- Select a Tax Rate", 0), QVariant(""));
    int taxRatesCount = taxRates->count();
    for(int i=0; i<taxRatesCount; i++)
    {
        TaxRate *taxRate = taxRates->at(i);
        ui->icmsPercentComboBox->addItem(taxRate->getName() + " - " + QString::number(taxRate->getValue()) + "%", QVariant(taxRate->getName()));
        ui->ipiPercentComboBox->addItem(taxRate->getName() + " - " + QString::number(taxRate->getValue()) + "%", QVariant(taxRate->getName()));
        ui->pisPercentComboBox->addItem(taxRate->getName() + " - " + QString::number(taxRate->getValue()) + "%", QVariant(taxRate->getName()));
        ui->cofinsPercentComboBox->addItem(taxRate->getName() + " - " + QString::number(taxRate->getValue()) + "%", QVariant(taxRate->getName()));
    }

    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddProduct()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
    connect(ui->cfopPushButton, SIGNAL(released()), this, SLOT(openCfopsWindow()));
}

void AddProductView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddProductView::proceedToAddProduct()
{
    QString code = ui->codeLineEdit->text();
    QString barCode = ui->barCodeLineEdit->text();
    int productCategoryId = ui->productCategoryComboBox->itemData(ui->productCategoryComboBox->currentIndex()).toInt();
    QString manufacturerCnpj = ui->manufacturerComboBox->itemData(ui->manufacturerComboBox->currentIndex()).toString();
//    QString providerCnpj = ui->providerComboBox->itemData(ui->providerComboBox->currentIndex()).toString();
    QString name = ui->nameLineEdit->text();
    QString description = ui->descriptionPlainTextEdit->toPlainText();
    QString cstIcms = ui->icmsComboBox->itemData(ui->icmsComboBox->currentIndex()).toString();
    QString cstIpi = ui->ipiComboBox->itemData(ui->ipiComboBox->currentIndex()).toString();
    QString cstPis = ui->pisComboBox->itemData(ui->pisComboBox->currentIndex()).toString();
    QString cstCofins = ui->cofinsComboBox->itemData(ui->cofinsComboBox->currentIndex()).toString();
    QString icmsPercent = ui->icmsPercentComboBox->itemData(ui->icmsPercentComboBox->currentIndex()).toString();
    QString ipiPercent = ui->ipiPercentComboBox->itemData(ui->ipiPercentComboBox->currentIndex()).toString();
    QString pisPercent = ui->pisPercentComboBox->itemData(ui->pisPercentComboBox->currentIndex()).toString();
    QString cofinsPercent = ui->cofinsPercentComboBox->itemData(ui->cofinsPercentComboBox->currentIndex()).toString();
    QString cfopCode = ui->cfopLineEdit->text();

    if(name.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill name field"),
                              QMessageBox::Ok);
    }
    else if(ui->productCategoryComboBox->currentIndex() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select a product category"),
                              QMessageBox::Ok);
    }
    else if(ui->manufacturerComboBox->currentIndex() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select a manufacturer"),
                              QMessageBox::Ok);
    }
//    else if(ui->providerComboBox->currentIndex() == 0)
//    {
//        QMessageBox::critical(this,
//                              tr("Error"),
//                              tr("Select a provider"),
//                              QMessageBox::Ok);
//    }
    else{

        Product *product;
        ProductController *productController = new ProductController();
        product = new Product(code, barCode, productCategoryId, manufacturerCnpj, name, description,
                              cstIcms, cstIpi, cstPis, cstCofins, icmsPercent, ipiPercent, pisPercent,
                              cofinsPercent, cfopCode);

        Utilities::StatusControl status = (this->editingProduct) ?
                                          productController->updateProduct(this->editingProduct->getCode(), product) :
                                          productController->addProduct(product);


        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listProducts();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a product registered with this code"),
                                      QMessageBox::Ok);
                break;
            }
            case Utilities::BAR_CODE_ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a product registered with this bar code"),
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

void AddProductView::hideAndClearFieldsData()
{
    emit aboutToClose();
}

void AddProductView::openCfopsWindow()
{
    this->chosenCfop = new Cfop("","","");
    this->cfopsListView = new CfopsListView();
    this->cfopsListView->setWindowMode(Utilities::CHOOSE_ITEM);
    this->cfopsListView->setCfopObjectChosen(this->chosenCfop);
    connect(this->cfopsListView, SIGNAL(aboutToClose()), this, SLOT(onCfopChosen()));
    this->cfopsListView->show();
}

void AddProductView::onCfopChosen()
{
    if(this->chosenCfop)
    {
        ui->cfopLineEdit->setText(this->chosenCfop->getCfop());
    }
}
