#include "addpurchaseproductorderview.h"
#include "ui_addpurchaseproductorderview.h"

#include <QMessageBox>

AddPurchaseProductOrderView::AddPurchaseProductOrderView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPurchaseProductOrderView)
{
    ui->setupUi(this);

    this->parent = (AddPurchasesOrderView*)parent;
    init();

    QString title = QApplication::translate("AddPurchaseProductOrderView", "Add new purchase product order", 0);
    setWindowTitle(title);

    this->editingPurchaseProductOrder = NULL;
}

AddPurchaseProductOrderView::AddPurchaseProductOrderView(PurchaseProductOrder *purchaseProductOrder, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPurchaseProductOrderView)
{
    ui->setupUi(this);

    this->parent = (AddPurchasesOrderView*)parent;
    init();

    QString title = QApplication::translate("AddPurchaseProductOrderView", "Edit purchase product order", 0);
    setWindowTitle(title);

    this->editingPurchaseProductOrder = purchaseProductOrder;

    // Product
    ProductController *productController = new ProductController();
    this->chosenProduct = productController->getProductByCode(purchaseProductOrder->getProductCode());
    ui->productLineEdit->setText(this->chosenProduct->getName());

    // Product Origin
    QString productOrigin(purchaseProductOrder->getProductOriginCode());
    int idxProductOrigin = ui->productOriginComboBox->findData(QVariant(productOrigin));
    ui->productOriginComboBox->setCurrentIndex(idxProductOrigin);

    // CST ICMS
    QString cstIcms = purchaseProductOrder->getCstIcmsCode();
    int idxCstIcms = ui->icmsComboBox->findData(QVariant(cstIcms));
    ui->icmsComboBox->setCurrentIndex(idxCstIcms);

    // CST IPI
    QString cstIpi = purchaseProductOrder->getCstIpiCode();
    int idxCstIpi = ui->ipiComboBox->findData(QVariant(cstIpi));
    ui->ipiComboBox->setCurrentIndex(idxCstIpi);

    // CST PIS
    QString cstPis = purchaseProductOrder->getCstPisCode();
    int idxCstPis = ui->pisComboBox->findData(QVariant(cstPis));
    ui->pisComboBox->setCurrentIndex(idxCstPis);

    // CST COFINS
    QString cstCofins = purchaseProductOrder->getCstCofinsCode();
    int idxCstCofins = ui->cofinsComboBox->findData(QVariant(cstCofins));
    ui->cofinsComboBox->setCurrentIndex(idxCstCofins);

    // ICMS VALUE
    ui->icmsDoubleSpinBox->setValue(purchaseProductOrder->getIcmsValue());

    // IPI VALUE
    ui->ipiDoubleSpinBox->setValue(purchaseProductOrder->getIpiValue());

    // PIS VALUE
    ui->pisDoubleSpinBox->setValue(purchaseProductOrder->getPisValue());

    // COFINS VALUE
    ui->cofinsDoubleSpinBox->setValue(purchaseProductOrder->getCofinsValue());

    // CFOP
    ui->cfopLineEdit->setText(purchaseProductOrder->getCfopCode());

    // Price
    ui->priceDoubleSpinBox->setValue(purchaseProductOrder->getUnitPrice());

    // Quantity
    int quantity = purchaseProductOrder->getQuantity();
    ui->quantityLineEdit->setText(QString::number(quantity));

    delete productController;
}

AddPurchaseProductOrderView::~AddPurchaseProductOrderView()
{
    delete ui;

    if(previousChosenProduct)
        delete previousChosenProduct;

    if(productsListView)
        delete productsListView;

    if(purchaseProductOrders)
        delete purchaseProductOrders;

    if(productOriginController)
        delete productOriginController;
    if(cstIcmsController)
        delete cstIcmsController;
    if(cstIpiController)
        delete cstIpiController;
    if(cstPisController)
        delete cstPisController;
    if(cstCofinsController)
        delete cstCofinsController;
    if(taxRateController)
        delete taxRateController;
    if(cfopsListView)
        delete cfopsListView;
}

void AddPurchaseProductOrderView::init()
{
    this->productsListView = NULL;
    this->chosenProduct = NULL;
    this->previousChosenProduct = NULL;
    this->purchaseProductOrders = NULL;

    this->productOriginController = NULL;
    this->cstIcmsController = NULL;
    this->cstIpiController = NULL;
    this->cstPisController = NULL;
    this->cstCofinsController = NULL;
    this->taxRateController = NULL;

    this->cfopsListView = NULL;

    //== PRODUCT ORIGIN ==
    productOriginController = new ProductOriginController();
    QList<ProductOrigin*> *productOrigins = productOriginController->getProductOrigins();
    ui->productOriginComboBox->clear();
    ui->productOriginComboBox->addItem(QApplication::translate("AddPurchaseProductOrderView", "-- Select an origin", 0), QVariant(""));
    int productOriginCount = productOrigins->count();
    for(int i=0; i<productOriginCount; i++)
    {
        ProductOrigin *productOrigin = productOrigins->at(i);
        ui->productOriginComboBox->addItem(productOrigin->getCode() + " - " + productOrigin->getName(), QVariant(productOrigin->getCode()));
    }

    //====
    //== ICMS ==
    cstIcmsController = new CstIcmsController();
    QList<CstIcms*> *cstIcmss = cstIcmsController->getCstIcmss();
    ui->icmsComboBox->clear();
    ui->icmsComboBox->addItem(QApplication::translate("AddPurchaseProductOrderView", "-- Select a condition", 0), QVariant(""));
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
    ui->ipiComboBox->addItem(QApplication::translate("AddPurchaseProductOrderView", "-- Select a condition", 0), QVariant(""));
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
    ui->pisComboBox->addItem(QApplication::translate("AddPurchaseProductOrderView", "-- Select a condition", 0), QVariant(""));
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
    ui->cofinsComboBox->addItem(QApplication::translate("AddPurchaseProductOrderView", "-- Select a condition", 0), QVariant(""));
    int cstCofinsCount = cstCofinss->count();
    for(int i=0; i<cstCofinsCount; i++)
    {
        CstCofins *cstCofins = cstCofinss->at(i);
        ui->cofinsComboBox->addItem(cstCofins->getCode() + " - " + cstCofins->getName(), QVariant(cstCofins->getCode()));
    }

//    //== TAX RATES ==
//    taxRateController = new TaxRateController();
//    QList<TaxRate*> *taxRates = taxRateController->getTaxRates();
//    ui->icmsPercentComboBox->clear();
//    ui->ipiPercentComboBox->clear();
//    ui->pisPercentComboBox->clear();
//    ui->cofinsPercentComboBox->clear();
//    ui->icmsPercentComboBox->addItem(QApplication::translate("AddPurchaseProductOrderView", "-- Select a Tax Rate", 0, QApplication::UnicodeUTF8), QVariant(""));
//    ui->ipiPercentComboBox->addItem(QApplication::translate("AddPurchaseProductOrderView", "-- Select a Tax Rate", 0, QApplication::UnicodeUTF8), QVariant(""));
//    ui->pisPercentComboBox->addItem(QApplication::translate("AddPurchaseProductOrderView", "-- Select a Tax Rate", 0, QApplication::UnicodeUTF8), QVariant(""));
//    ui->cofinsPercentComboBox->addItem(QApplication::translate("AddPurchaseProductOrderView", "-- Select a Tax Rate", 0, QApplication::UnicodeUTF8), QVariant(""));
//    int taxRatesCount = taxRates->count();
//    for(int i=0; i<taxRatesCount; i++)
//    {
//        TaxRate *taxRate = taxRates->at(i);
//        ui->icmsPercentComboBox->addItem(taxRate->getName() + " - " + QString::number(taxRate->getValue()) + "%", QVariant(taxRate->getName()));
//        ui->ipiPercentComboBox->addItem(taxRate->getName() + " - " + QString::number(taxRate->getValue()) + "%", QVariant(taxRate->getName()));
//        ui->pisPercentComboBox->addItem(taxRate->getName() + " - " + QString::number(taxRate->getValue()) + "%", QVariant(taxRate->getName()));
//        ui->cofinsPercentComboBox->addItem(taxRate->getName() + " - " + QString::number(taxRate->getValue()) + "%", QVariant(taxRate->getName()));
//    }
//    //=====
    ui->quantityLineEdit->setValidator(new QIntValidator(this));

    connect(ui->chooseProductToolButton, SIGNAL(released()), this, SLOT(openProductsWindow()));
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddPurchaseProductOrder()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));

    connect(ui->cfopPushButton, SIGNAL(released()), this, SLOT(openCfopsWindow()));
}

void AddPurchaseProductOrderView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddPurchaseProductOrderView::proceedToAddPurchaseProductOrder()
{
    double price = ui->priceDoubleSpinBox->value();
    int quantity = ui->quantityLineEdit->text().toInt();
    QString productOriginCode = ui->productOriginComboBox->itemData(ui->productOriginComboBox->currentIndex()).toString();
    QString cstIcms = ui->icmsComboBox->itemData(ui->icmsComboBox->currentIndex()).toString();
    QString cstIpi = ui->ipiComboBox->itemData(ui->ipiComboBox->currentIndex()).toString();
    QString cstPis = ui->pisComboBox->itemData(ui->pisComboBox->currentIndex()).toString();
    QString cstCofins = ui->cofinsComboBox->itemData(ui->cofinsComboBox->currentIndex()).toString();
    double icmsValue = ui->icmsDoubleSpinBox->value();
    double ipiValue = ui->ipiDoubleSpinBox->value();
    double pisValue = ui->pisDoubleSpinBox->value();
    double cofinsValue = ui->cofinsDoubleSpinBox->value();
    QString cfopCode = ui->cfopLineEdit->text();

    if(!chosenProduct)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select a product."),
                              QMessageBox::Ok);
    }
    else if(ui->productOriginComboBox->currentIndex() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select an origin"),
                              QMessageBox::Ok);
    }
    else if(price == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Set a price."),
                              QMessageBox::Ok);
    }
    else if(quantity == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill quantity field."),
                              QMessageBox::Ok);
    }
    else{

        if(this->chosenProduct->getCode().length() == 0)
        {
            this->chosenProduct = this->previousChosenProduct;
        }

        if(this->chosenProduct)
        {

            Utilities *u = new Utilities();

            if(this->editingPurchaseProductOrder)
            {
                this->editingPurchaseProductOrder->setProductCode(this->chosenProduct->getCode());
                this->editingPurchaseProductOrder->setQuantity(quantity);
                this->editingPurchaseProductOrder->setProductOriginCode(productOriginCode.at(0));
                this->editingPurchaseProductOrder->setCstIcmsCode(cstIcms);
                this->editingPurchaseProductOrder->setCstIpiCode(cstIpi);
                this->editingPurchaseProductOrder->setCstPisCode(cstPis);
                this->editingPurchaseProductOrder->setCstCofinsCode(cstCofins);
                this->editingPurchaseProductOrder->setIcmsValue(icmsValue);
                this->editingPurchaseProductOrder->setIpiValue(ipiValue);
                this->editingPurchaseProductOrder->setPisValue(pisValue);
                this->editingPurchaseProductOrder->setCofinsValue(cofinsValue);
                this->editingPurchaseProductOrder->setCfopCode(cfopCode);
                this->editingPurchaseProductOrder->setUnitPrice(price);
            }
            else
            {
                PurchaseProductOrder *purchaseProductOrder = new PurchaseProductOrder(this->chosenProduct->getCode(),
                                                        quantity, productOriginCode.at(0), cstIcms, cstIpi, cstPis,
                                                        cstCofins, icmsValue, ipiValue, pisValue, cofinsValue,
                                                        cfopCode, price, u->getDefaultCNPJ());
                ((AddPurchasesOrderView*)parent)->appendPurchaseProductOrder(purchaseProductOrder);
            }

            delete u;

            ((AddPurchasesOrderView*)parent)->listPurchaseProductOrders();
            emit aboutToClose();
        }
        else
        {
            QMessageBox::critical(this,
                                  tr("Error"),
                                  tr("You must select a product, before adding a new purchase product order."),
                                  QMessageBox::Ok);
        }

    }
}

void AddPurchaseProductOrderView::hideAndClearFieldsData()
{
    emit aboutToClose();
}

void AddPurchaseProductOrderView::openProductsWindow()
{
    if(this->chosenProduct && (this->chosenProduct->getCode() != 0))
    {
        this->previousChosenProduct = this->chosenProduct;
    }

    this->chosenProduct = new Product("","",0,"","","","","","","","","","","","");
    this->productsListView = new ProductsListView();
    this->productsListView->setWindowMode(Utilities::CHOOSE_ITEM);
    this->productsListView->setProductObjectChosen(this->chosenProduct);
    connect(this->productsListView, SIGNAL(aboutToClose()), this, SLOT(onProductChosen()));
    this->productsListView->show();
}

void AddPurchaseProductOrderView::onProductChosen()
{
    if(this->chosenProduct)
    {
        ui->productLineEdit->setText(this->chosenProduct->getName());
    }
}

void AddPurchaseProductOrderView::openCfopsWindow()
{
    this->chosenCfop = new Cfop("","","");
    this->cfopsListView = new CfopsListView();
    this->cfopsListView->setWindowMode(Utilities::CHOOSE_ITEM);
    this->cfopsListView->setCfopObjectChosen(this->chosenCfop);
    connect(this->cfopsListView, SIGNAL(aboutToClose()), this, SLOT(onCfopChosen()));
    this->cfopsListView->show();
}

void AddPurchaseProductOrderView::onCfopChosen()
{
    if(this->chosenCfop)
    {
        ui->cfopLineEdit->setText(this->chosenCfop->getCfop());
    }
}
