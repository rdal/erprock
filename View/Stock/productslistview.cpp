#include "productslistview.h"
#include "ui_productslistview.h"

#include <QMessageBox>

ProductsListView::ProductsListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductsListView)
{
    ui->setupUi(this);

    windowMode = Utilities::DEFAULT;
    chosenProduct = NULL;

    productController = new ProductController();
    productCategoryController = new ProductCategoryController();
    manufacturerController = new ManufacturerController();

    connect(ui->addProductPushButton, SIGNAL(released()), this, SLOT(onAddNewProduct()));
    connect(ui->editProductPushButton, SIGNAL(released()), this, SLOT(onEditProduct()));
    connect(ui->removeProductPushButton, SIGNAL(released()), this, SLOT(onRemoveProduct()));

    listProducts();
}

ProductsListView::~ProductsListView()
{
    delete ui;

    delete productController;
    delete productCategoryController;
    delete manufacturerController;

    if(chosenProduct)
        delete chosenProduct;
}

void ProductsListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void ProductsListView::listProducts()
{
    QList<Product*> *products = productController->getProducts();

    int count = products->count();
    ui->productsTableWidget->clearContents();
    ui->productsTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        Product *product = products->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->productsTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Code
        QTableWidgetItem *codeItem = new QTableWidgetItem();
        QString codeItemValue = product->getCode();
        codeItem->setText(codeItemValue);
        ui->productsTableWidget->setItem(i, 0, codeItem);

        // Bar Code
        QTableWidgetItem *barCodeItem = new QTableWidgetItem();
        QString barCodeItemValue = product->getBarCode();
        barCodeItem->setText(barCodeItemValue);
        ui->productsTableWidget->setItem(i, 1, barCodeItem);

        // Product Category
        QTableWidgetItem *productCategoryIdItem = new QTableWidgetItem();
        int productCategoryIdItemValue = product->getProductCategoryId();
        ProductCategory *productCategory = productCategoryController->getProductCategoryById(productCategoryIdItemValue);
        productCategoryIdItem->setText(productCategory->getName());
        ui->productsTableWidget->setItem(i, 2, productCategoryIdItem);

        // Manufacturer
        QTableWidgetItem *manufacturerItem = new QTableWidgetItem();
        QString manufacturerItemValue = product->getManufacturerCnpj();
        Manufacturer *manufacturer = manufacturerController->getManufacturerByCNPJ(manufacturerItemValue);
        manufacturerItem->setText(manufacturer->getName());
        ui->productsTableWidget->setItem(i, 3, manufacturerItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = product->getName();
        nameItem->setText(nameItemValue);
        ui->productsTableWidget->setItem(i, 4, nameItem);

        // Quantity
        QTableWidgetItem *quantityItem = new QTableWidgetItem();
        double quantityItemValue = productController->getQuantityByCode(codeItemValue);
        quantityItem->setText(QString::number(quantityItemValue));
        ui->productsTableWidget->setItem(i, 5, quantityItem);

//        // Description
//        QTableWidgetItem *descriptionItem = new QTableWidgetItem();
//        QString descriptionItemValue = product->getDescription();
//        descriptionItem->setText(descriptionItemValue);
//        ui->productsTableWidget->setItem(i, 5, descriptionItem);

//        // Purchase Price
//        QTableWidgetItem *purchasePriceItem = new QTableWidgetItem();
//        double purchasePriceItemValue = product->getPurchasePrice();
//        purchasePriceItem->setText(QString::number(purchasePriceItemValue));
//        ui->productsTableWidget->setItem(i, 6, purchasePriceItem);

//        // Selling Price
//        QTableWidgetItem *sellingPriceItem = new QTableWidgetItem();
//        double sellingPriceItemValue = product->getSellingPrice();
//        sellingPriceItem->setText(QString::number(sellingPriceItemValue));
//        ui->productsTableWidget->setItem(i, 7, sellingPriceItem);

//        // Quantity
//        QTableWidgetItem *quantityItem = new QTableWidgetItem();
//        double quantityItemValue = product->getQuantity();
//        quantityItem->setText(QString::number(quantityItemValue));
//        ui->productsTableWidget->setItem(i, 8, quantityItem);
    }

    ui->productsTableWidget->resizeColumnsToContents();
    ui->productsTableWidget->selectRow(0);

    if(count == 0){
        ui->editProductPushButton->setEnabled(false);
    }
    else{
        ui->editProductPushButton->setEnabled(true);
    }

}

//============== PUBLIC SLOTS ================
void ProductsListView::onAddNewProduct()
{
    this->parentMainWindow->addFormAddProductToMDI();
}

void ProductsListView::onEditProduct()
{
    QTableWidgetItem *item = ui->productsTableWidget->selectedItems().at(0);
    QString code = item->text();
    Product *product = productController->getProductByCode(code);
    this->parentMainWindow->addFormEditProductToMDI(product);
}

void ProductsListView::onRemoveProduct()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this product?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->productsTableWidget->selectedItems().at(0);
        QString code = item->text();
        Utilities::StatusControl status = productController->removeProduct(code);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listProducts();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered code doesn't belong to any product of database"),
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

void ProductsListView::setWindowMode(Utilities::ItemsListWindowMode windowMode)
{
    this->windowMode = windowMode;
    if(this->windowMode == Utilities::CHOOSE_ITEM)
    {
        ui->frame->setVisible(false);
        connect(ui->productsTableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(onChooseProduct()));
    }
    else
    {
        ui->frame->setVisible(true);
        ui->productsTableWidget->disconnect();
    }
}

void ProductsListView::setProductObjectChosen(Product *&localChosenProduct)
{
    this->chosenProduct = localChosenProduct;
}

void ProductsListView::onChooseProduct()
{
//    QList<QTableWidgetItem*> selectedItems = this->productsTableWidget->selectedItems();
//    int itemsLen = selectedItems.length();
//    if(itemsLen != 0)
//    {
//        int selectedIndex = selectedItems.at(0)->row();
//    }

    QTableWidgetItem *item = ui->productsTableWidget->selectedItems().at(0);
    QString code = item->text();
    Product *p = productController->getProductByCode(code);

    this->chosenProduct->setCode(p->getCode());
    this->chosenProduct->setBarCode(p->getBarCode());
    this->chosenProduct->setProductCategoryId(p->getProductCategoryId());
    this->chosenProduct->setManufacturerCnpj(p->getManufacturerCnpj());
    this->chosenProduct->setName(p->getName());
    this->chosenProduct->setDescription(p->getDescription());
    this->chosenProduct->setCstIcms(p->getCstIcms());
    this->chosenProduct->setCstIpi(p->getCstIpi());
    this->chosenProduct->setCstPis(p->getCstPis());
    this->chosenProduct->setCstCofins(p->getCstCofins());
    this->chosenProduct->setIcmsPercentName(p->getIcmsPercentName());
    this->chosenProduct->setIpiPercentName(p->getIpiPercentName());
    this->chosenProduct->setPisPercentName(p->getPisPercentName());
    this->chosenProduct->setCofinsPercentName(p->getCofinsPercentName());
    this->chosenProduct->setCfopCode(p->getCfopCode());

    emit aboutToClose();

    this->close();
}
