#include "addsaleproductorderview.h"
#include "ui_addsaleproductorderview.h"

#include <QMessageBox>

AddSaleProductOrderView::AddSaleProductOrderView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddSaleProductOrderView)
{
    ui->setupUi(this);

    this->parent = (AddSalesOrderView*)parent;
    init();

    QString title = QApplication::translate("AddSaleProductOrderView", "Add new sale product order", 0);
    setWindowTitle(title);

    this->editingSaleProductOrder = NULL;
}

AddSaleProductOrderView::AddSaleProductOrderView(SaleProductOrder *saleProductOrder, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddSaleProductOrderView)
{
    ui->setupUi(this);

    this->parent = (AddSalesOrderView*)parent;
    init();

    QString title = QApplication::translate("AddSaleProductOrderView", "Edit sale product order", 0);
    setWindowTitle(title);

    this->editingSaleProductOrder = saleProductOrder;

    // Product
    ProductController *productController = new ProductController();
    this->chosenProduct = productController->getProductByCode(saleProductOrder->getProductCode());
    ui->productLineEdit->setText(this->chosenProduct->getName());

    // Price
//    Price *price = priceController->getPriceByProductCode(saleProductOrder->getProductCode());
//    ui->priceDoubleSpinBox->setValue(price->getValue());
    ui->priceDoubleSpinBox->setValue(saleProductOrder->getValue());

    // Quantity
    int quantity = saleProductOrder->getQuantity();
    ui->quantityLineEdit->setText(QString::number(quantity));

    delete productController;

    //delete price;
}

AddSaleProductOrderView::~AddSaleProductOrderView()
{
    delete ui;
    delete priceController;

    if(previousChosenProduct)
        delete previousChosenProduct;

    if(productsListView)
        delete productsListView;

    if(saleProductOrders)
        delete saleProductOrders;
}

void AddSaleProductOrderView::init()
{
    priceController = new PriceController();

    this->productsListView = NULL;
    this->chosenProduct = NULL;
    this->previousChosenProduct = NULL;
    this->saleProductOrders = NULL;

    ui->quantityLineEdit->setValidator(new QIntValidator(this));

    connect(ui->chooseProductToolButton, SIGNAL(released()), this, SLOT(openProductsWindow()));
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddSaleProductOrder()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddSaleProductOrderView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddSaleProductOrderView::proceedToAddSaleProductOrder()
{
    int quantity = ui->quantityLineEdit->text().toInt();

    if(!chosenProduct)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select a product."),
                              QMessageBox::Ok);
    }
    else if(quantity == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill quantity field"),
                              QMessageBox::Ok);
    }
    else
    {

        if(this->chosenProduct->getCode().length() == 0)
        {
            this->chosenProduct = this->previousChosenProduct;
        }

        if(this->chosenProduct)
        {
            ProductController *productController = new ProductController();
            int availableQuantity = (this->editingSaleProductOrder) ?
                                    productController->getQuantityByCode(this->chosenProduct->getCode()) + this->editingSaleProductOrder->getQuantity() :
                                    productController->getQuantityByCode(this->chosenProduct->getCode());

            if((availableQuantity - quantity) < 0)
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The required product quantity is not available."),
                                      QMessageBox::Ok);
            }
            else
            {
                Utilities *u = new Utilities();

                if(this->editingSaleProductOrder)
                {
                    this->editingSaleProductOrder->setProductCode(this->chosenProduct->getCode());
                    this->editingSaleProductOrder->setQuantity(quantity);
                }
                else
                {
                    SaleProductOrder *saleProductOrder = new SaleProductOrder(this->chosenProduct->getCode(),
                                                            quantity,
                                                            this->chosenProduct->getCstIcms(),
                                                            this->chosenProduct->getCstIpi(),
                                                            this->chosenProduct->getCstPis(),
                                                            this->chosenProduct->getCstCofins(),
                                                            this->chosenProduct->getIcmsPercentName(),
                                                            this->chosenProduct->getIpiPercentName(),
                                                            this->chosenProduct->getPisPercentName(),
                                                            this->chosenProduct->getCofinsPercentName(),
                                                            this->chosenProduct->getCfopCode(),
                                                            u->getDefaultCNPJ(),
                                                            this->priceController->getPriceByProductCode(chosenProduct->getCode())->getValue());
                    ((AddSalesOrderView*)parent)->appendSaleProductOrder(saleProductOrder);
                }
                delete u;

                ((AddSalesOrderView*)parent)->listSaleProductOrders();
                emit aboutToClose();
            }

            delete productController;


    //        PriceController *priceController = new PriceController();
    //        Utilities::StatusControl status = (this->editingPrice) ?
    //                                          priceController->updatePrice(new Price(this->editingPrice->getId(), this->chosenProduct->getCode(), value, storeCnpj, name)) :
    //                                          priceController->addPrice(new Price(this->chosenProduct->getCode(), value, storeCnpj, name));


    //        switch(status)
    //        {
    //            case Utilities::NO_ERR:
    //            {
    //                this->parent->listPrices();
    //                emit aboutToClose();
    //                break;
    //            }
    //            case Utilities::DB_NOT_CONNECTED:
    //            {
    //                QMessageBox::critical(this,
    //                                      tr("Error"),
    //                                      tr("Database is not connected"),
    //                                      QMessageBox::Ok);
    //                break;
    //            }
    //            case Utilities::UNKNOWN_ERROR:
    //            {
    //                QMessageBox::critical(this,
    //                                      tr("Error"),
    //                                      tr("Unknown error"),
    //                                      QMessageBox::Ok);
    //                break;
    //            }
    //            default:
    //            {
    //                break;
    //            }
    //        }
        }
        else
        {
            QMessageBox::critical(this,
                                  tr("Error"),
                                  tr("You must select a product, before adding a new sale product order."),
                                  QMessageBox::Ok);
        }
    }
}

void AddSaleProductOrderView::hideAndClearFieldsData()
{
    emit aboutToClose();
}

void AddSaleProductOrderView::openProductsWindow()
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

void AddSaleProductOrderView::onProductChosen()
{
    if(this->chosenProduct)
    {
        ui->productLineEdit->setText(this->chosenProduct->getName());

        Price *price = priceController->getPriceByProductCode(this->chosenProduct->getCode());
        if(price)
        {
            ui->priceDoubleSpinBox->setValue(price->getValue());
            delete price;
        }
        else
        {
            QMessageBox::critical(this,
                                  tr("Error"),
                                  tr("This product is not precified yet. You cannot sell a product without a price."),
                                  QMessageBox::Ok);
        }
    }
}
