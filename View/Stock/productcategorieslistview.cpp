#include "productcategorieslistview.h"
#include "ui_productcategorieslistview.h"

#include <QMessageBox>

ProductCategoriesListView::ProductCategoriesListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductCategoriesListView)
{
    ui->setupUi(this);

    connect(ui->addProductCategoryPushButton, SIGNAL(released()), this, SLOT(onAddNewProductCategory()));
    connect(ui->editProductCategoryPushButton, SIGNAL(released()), this, SLOT(onEditProductCategory()));
    connect(ui->removeProductCategoryPushButton, SIGNAL(released()), this, SLOT(onRemoveProductCategory()));

    productCategoryController = new ProductCategoryController();
    listProductCategories();
}

ProductCategoriesListView::~ProductCategoriesListView()
{
    delete ui;

    //parentMainWindow = NULL;
    delete productCategoryController;
}

void ProductCategoriesListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void ProductCategoriesListView::listProductCategories()
{
    QList<ProductCategory*> *productCategories = productCategoryController->getProductCategories();

    int count = productCategories->count();
    ui->productCategoriesTableWidget->clearContents();
    ui->productCategoriesTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        ProductCategory *productCategory = productCategories->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->productCategoriesTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Id
        QTableWidgetItem *idItem = new QTableWidgetItem();
        int idItemValue = productCategory->getId();
        idItem->setText(QString::number(idItemValue));
        ui->productCategoriesTableWidget->setItem(i, 0, idItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = productCategory->getName();
        nameItem->setText(nameItemValue);
        ui->productCategoriesTableWidget->setItem(i, 1, nameItem);
    }

    ui->productCategoriesTableWidget->resizeColumnsToContents();
    ui->productCategoriesTableWidget->selectRow(0);

    if(count == 0){
        ui->editProductCategoryPushButton->setEnabled(false);
    }
    else{
        ui->editProductCategoryPushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void ProductCategoriesListView::onAddNewProductCategory()
{
    this->parentMainWindow->addFormAddProductCategoryToMDI();
}

void ProductCategoriesListView::onEditProductCategory()
{
    QTableWidgetItem *item = ui->productCategoriesTableWidget->selectedItems().at(0);
    int id = item->text().toInt();
    ProductCategory *productCategory = productCategoryController->getProductCategoryById(id);
    this->parentMainWindow->addFormEditProductCategoryToMDI(productCategory);
}

void ProductCategoriesListView::onRemoveProductCategory()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this product category?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->productCategoriesTableWidget->selectedItems().at(0);
        int id = item->text().toInt();
        Utilities::StatusControl status = productCategoryController->removeProductCategory(id);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listProductCategories();
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
