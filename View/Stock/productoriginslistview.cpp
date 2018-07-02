#include "productoriginslistview.h"
#include "ui_productoriginslistview.h"

#include <QMessageBox>

ProductOriginsListView::ProductOriginsListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductOriginsListView)
{
    ui->setupUi(this);

    connect(ui->addProductOriginPushButton, SIGNAL(released()), this, SLOT(onAddNewProductOrigin()));
    connect(ui->editProductOriginPushButton, SIGNAL(released()), this, SLOT(onEditProductOrigin()));
    connect(ui->removeProductOriginPushButton, SIGNAL(released()), this, SLOT(onRemoveProductOrigin()));

    productOriginController = new ProductOriginController();
    listProductOrigins();
}

ProductOriginsListView::~ProductOriginsListView()
{
    delete ui;

    delete productOriginController;
}

void ProductOriginsListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void ProductOriginsListView::listProductOrigins()
{
    QList<ProductOrigin*> *productOrigins = productOriginController->getProductOrigins();

    int count = productOrigins->count();
    ui->productOriginsTableWidget->clearContents();
    ui->productOriginsTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        ProductOrigin *productOrigin = productOrigins->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->productOriginsTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Code
        QTableWidgetItem *codeItem = new QTableWidgetItem();
        QString codeItemValue = productOrigin->getCode();
        codeItem->setText(codeItemValue);
        ui->productOriginsTableWidget->setItem(i, 0, codeItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = productOrigin->getName();
        nameItem->setText(nameItemValue);
        ui->productOriginsTableWidget->setItem(i, 1, nameItem);
    }

    ui->productOriginsTableWidget->resizeColumnsToContents();
    ui->productOriginsTableWidget->selectRow(0);

    if(count == 0){
        ui->editProductOriginPushButton->setEnabled(false);
    }
    else{
        ui->editProductOriginPushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void ProductOriginsListView::onAddNewProductOrigin()
{
    this->parentMainWindow->addFormAddProductOriginToMDI();
}

void ProductOriginsListView::onEditProductOrigin()
{
    QTableWidgetItem *item = ui->productOriginsTableWidget->selectedItems().at(0);
    QString code = item->text();
    ProductOrigin *productOrigin = productOriginController->getProductOriginByCode(code);
    this->parentMainWindow->addFormEditProductOriginToMDI(productOrigin);
}

void ProductOriginsListView::onRemoveProductOrigin()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this product origin?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->productOriginsTableWidget->selectedItems().at(0);
        QString code = item->text();
        Utilities::StatusControl status = productOriginController->removeProductOrigin(code);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listProductOrigins();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered code doesn't belong to any product origin of database"),
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
