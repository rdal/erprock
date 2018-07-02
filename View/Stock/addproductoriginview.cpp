#include "addproductoriginview.h"
#include "ui_addproductoriginview.h"

#include <QMessageBox>

AddProductOriginView::AddProductOriginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProductOriginView)
{
    ui->setupUi(this);

    this->parent = (ProductOriginsListView*)parent;
    init();

    QString title = QApplication::translate("AddProductOriginView", "Add new product origin", 0);
    setWindowTitle(title);

    this->editingProductOrigin = NULL;
}

AddProductOriginView::AddProductOriginView(ProductOrigin *productOrigin, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProductOriginView)
{
    ui->setupUi(this);

    this->parent = (ProductOriginsListView*)parent;
    init();

    QString title = QApplication::translate("AddProductOriginView", "Edit product origin", 0);
    setWindowTitle(title);

    this->editingProductOrigin = productOrigin;
    ui->codeLineEdit->setText(productOrigin->getCode());
    ui->nameLineEdit->setText(productOrigin->getName());
}

AddProductOriginView::~AddProductOriginView()
{
    delete ui;

    delete editingProductOrigin;
}

void AddProductOriginView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddProductOrigin()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddProductOriginView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddProductOriginView::proceedToAddProductOrigin()
{
    QString code = ui->codeLineEdit->text();
    QString name = ui->nameLineEdit->text();

    if(name.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill name field"),
                              QMessageBox::Ok);
    }
    else{

        ProductOrigin *productOrigin;
        ProductOriginController *productOriginController = new ProductOriginController();
        productOrigin = new ProductOrigin(code, name);

        Utilities::StatusControl status = (this->editingProductOrigin) ?
                                          productOriginController->updateProductOrigin(this->editingProductOrigin->getCode(), productOrigin) :
                                          productOriginController->addProductOrigin(productOrigin);


        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listProductOrigins();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a product origin registered with this code"),
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

void AddProductOriginView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
