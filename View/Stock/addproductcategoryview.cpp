#include "addproductcategoryview.h"
#include "ui_addproductcategoryview.h"

#include <QMessageBox>

AddProductCategoryView::AddProductCategoryView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProductCategoryView)
{
    ui->setupUi(this);

    this->parent = (ProductCategoriesListView*)parent;
    init();

    QString title = QApplication::translate("AddProductCategoryView", "Add new product category", 0);
    setWindowTitle(title);

    this->editingProductCategory = NULL;
}

AddProductCategoryView::AddProductCategoryView(ProductCategory *productCategory, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProductCategoryView)
{
    ui->setupUi(this);

    this->parent = (ProductCategoriesListView*)parent;
    init();

    QString title = QApplication::translate("AddProductCategoryView", "Edit product category", 0);
    setWindowTitle(title);

    this->editingProductCategory = productCategory;
    ui->nameLineEdit->setText(productCategory->getName());
}

AddProductCategoryView::~AddProductCategoryView()
{
    delete ui;

//    //parentMainWindow = NULL;
//    parent = NULL;
    delete editingProductCategory;
}

void AddProductCategoryView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddProductCategory()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddProductCategoryView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddProductCategoryView::proceedToAddProductCategory()
{
    QString name = ui->nameLineEdit->text();

    if(name.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill name field"),
                              QMessageBox::Ok);
    }
    else{

        ProductCategory *productCategory;
        ProductCategoryController *productCategoryController = new ProductCategoryController();
        productCategory = new ProductCategory(name);

        Utilities::StatusControl status;
        if(this->editingProductCategory)
        {
            productCategory->setId(this->editingProductCategory->getId());
            status = productCategoryController->updateProductCategory(productCategory);
        }
        else
        {
            status = productCategoryController->addProductCategory(productCategory);
        }


        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listProductCategories();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a product category registered with this name"),
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

void AddProductCategoryView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
