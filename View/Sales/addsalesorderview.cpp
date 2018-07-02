#include "addsalesorderview.h"
#include "ui_addsalesorderview.h"
#include "productcontroller.h"

#include <QMessageBox>
#include <QTableWidgetItem>

AddSalesOrderView::AddSalesOrderView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddSalesOrderView)
{
    ui->setupUi(this);

    this->parent = (SalesOrdersListView*)parent;
    init();

    QString title = QApplication::translate("AddSalesOrderView", "Add new sales order", 0);
    setWindowTitle(title);

    this->editingSalesOrder = NULL;
    this->saleProductOrders = new QList<SaleProductOrder*>();

    listSaleProductOrders();
}

AddSalesOrderView::AddSalesOrderView(SalesOrder *salesOrder, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddSalesOrderView)
{
    ui->setupUi(this);

    this->parent = (SalesOrdersListView*)parent;
    init();

    QString title = QApplication::translate("AddSalesOrderView", "Add new sales order", 0);
    setWindowTitle(title);

    this->editingSalesOrder = salesOrder;

    // Receipt
    ui->receiptLineEdit->setText(this->editingSalesOrder->getReceipt());

    // Payment Condition
    ui->paymentConditionLineEdit->setText(QString::number(this->editingSalesOrder->getPaymentCondition()));

    // Payment Form
    Utilities::PaymentForm paymentForm = this->editingSalesOrder->getPaymentForm();
    int idxPaymentForm = ui->paymentFormComboBox->findData(QVariant(paymentForm));
    ui->paymentFormComboBox->setCurrentIndex(idxPaymentForm);

    // Customer
    QString customerId = this->editingSalesOrder->getCustomerId();
    if(customerId.length() == 11)
    {
        ui->physicalCustomerRadioButton->setChecked(true);
        showPhysicalCustomersList(true);
    }
    else
    {
        ui->enterpriseCustomerRadioButton->setChecked(true);
        showEnterpriseCustomersList(true);
    }
    int idxCustomerId = ui->customerComboBox->findData(QVariant(customerId));
    ui->customerComboBox->setCurrentIndex(idxCustomerId);

    // Observation
    ui->observationPlainTextEdit->setPlainText(this->editingSalesOrder->getObservation());

    // Discount
    ui->discountDoubleSpinBox->setValue(this->editingSalesOrder->getDiscount());

    // Paid Value
    ui->valuePaidDoubleSpinBox->setValue(this->editingSalesOrder->getValuePaid());

    // Total Value
    ui->totalValueLineEdit->setText(QString::number(this->editingSalesOrder->getValueTotal()));

    // Sales Product Orders
    this->saleProductOrders =
            this->salesOrderController->getSaleProductOrdersBySalesOrderId(this->editingSalesOrder->getId());

    listSaleProductOrders();

}

AddSalesOrderView::~AddSalesOrderView()
{
    delete ui;
    delete salesOrderController;
    delete priceController;
    delete saleProductOrders;

    if (editingSalesOrder)
        delete editingSalesOrder;
}

void AddSalesOrderView::init()
{
    priceController = new PriceController();

    this->salesOrderController = new SalesOrderController();
    ui->paymentConditionLineEdit->setValidator(new QIntValidator(this));

    //========== Payment Form ===========
    ui->paymentFormComboBox->clear();
    ui->paymentFormComboBox->addItem(QApplication::translate("AddSalesOrderView", "-- Select a payment condition", 0), QVariant(0));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddSalesOrderView", "Money", 0), QVariant(Utilities::MONEY));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddSalesOrderView", "Visa", 0), QVariant(Utilities::VISA));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddSalesOrderView", "MasterCard", 0), QVariant(Utilities::MASTERCARD));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddSalesOrderView", "Diners", 0), QVariant(Utilities::DINERS));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddSalesOrderView", "American Express", 0), QVariant(Utilities::AMEX));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddSalesOrderView", "Bank Ticket", 0), QVariant(Utilities::BANK_TICKET));


    //=========== Customers ============
    customerController = new CustomerController();
    QList<PhysicalCustomer*> *physicalCustomersObjects = customerController->getPhysicalCustomers();

    ui->customerComboBox->clear();
    ui->customerComboBox->addItem(QApplication::translate("AddSalesOrderView", "-- Select a customer", 0), QVariant(""));

    int physicalCustomersCount = physicalCustomersObjects->count();
    for(int i=0; i<physicalCustomersCount; i++)
    {
        QString cpf = physicalCustomersObjects->at(i)->getCpf();
        QString name = ((PhysicalCustomer*)physicalCustomersObjects->at(i))->getName();
        ui->customerComboBox->addItem(cpf+" - "+name, QVariant(cpf));
    }

    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddSalesOrder()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
    connect(ui->physicalCustomerRadioButton, SIGNAL(toggled(bool)), this, SLOT(showPhysicalCustomersList(bool)));
    connect(ui->enterpriseCustomerRadioButton, SIGNAL(toggled(bool)), this, SLOT(showEnterpriseCustomersList(bool)));

    connect(ui->addProductPushButton, SIGNAL(released()), this, SLOT(onAddNewSaleProductOrder()));
    connect(ui->editProductPushButton, SIGNAL(released()), this, SLOT(onEditSaleProductOrder()));
    connect(ui->removeProductPushButton, SIGNAL(released()), this, SLOT(onRemoveSaleProductOrder()));

    delete physicalCustomersObjects;
}

void AddSalesOrderView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void AddSalesOrderView::listSaleProductOrders()
{
    QLocale locale(QLocale::German);

    double totalValue = 0;
    int saleProductOrderCount = this->saleProductOrders->count();
    ui->itemsTableWidget->clearContents();
    ui->itemsTableWidget->setRowCount(saleProductOrderCount);
    for(int i=0; i<saleProductOrderCount; i++)
    {
        SaleProductOrder *saleProductOrder = this->saleProductOrders->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->itemsTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Id
        QTableWidgetItem *idItem = new QTableWidgetItem();
        int idItemValue = saleProductOrder->getId();
        idItem->setText(QString::number(idItemValue));
        ui->itemsTableWidget->setItem(i, 0, idItem);

        // Product Code
        QTableWidgetItem *productCodeItem = new QTableWidgetItem();
        QString productCodeItemValue = saleProductOrder->getProductCode();
        productCodeItem->setText(productCodeItemValue);
        ui->itemsTableWidget->setItem(i, 1, productCodeItem);

        // Product Name
        ProductController *productController = new ProductController();
        QTableWidgetItem *productNameItem = new QTableWidgetItem();
        QString productNameItemValue = productController->getProductByCode(saleProductOrder->getProductCode())->getName();
        productNameItem->setText(productNameItemValue);
        ui->itemsTableWidget->setItem(i, 2, productNameItem);
        delete productController;

        // Quantity
        QTableWidgetItem *quantityItem = new QTableWidgetItem();
        int quantityItemValue = saleProductOrder->getQuantity();
        quantityItem->setText(QString::number(quantityItemValue));
        ui->itemsTableWidget->setItem(i, 3, quantityItem);

        // Value
        double priceValue = saleProductOrder->getValue();
        QTableWidgetItem *priceItem = new QTableWidgetItem();

        double priceItemValue = priceValue * quantityItemValue;
        QString priceItemValueStr = locale.toString(priceItemValue,'f',2);
        priceItem->setText(priceItemValueStr);
        ui->itemsTableWidget->setItem(i, 4, priceItem);

//        Price *p = priceController->getPriceByProductCode(productCodeItemValue);
//        double priceValue = p->getValue();

//        QTableWidgetItem *priceItem = new QTableWidgetItem();
//        double priceItemValue = priceValue * quantityItemValue;
//        QString priceItemValueStr = locale.toString(priceItemValue,'f',2);
//        priceItem->setText(priceItemValueStr);
//        ui->itemsTableWidget->setItem(i, 4, priceItem);

        totalValue += priceItemValue;

    }

    ui->itemsTableWidget->resizeColumnsToContents();
    ui->itemsTableWidget->selectRow(0);
    ui->itemsTableWidget->hideColumn(0);

    QString totalValueStr = locale.toString(totalValue,'f',2);
    ui->totalValueLineEdit->setText(totalValueStr);

    if(saleProductOrderCount == 0){
        ui->editProductPushButton->setEnabled(false);
    }
    else{
        ui->editProductPushButton->setEnabled(true);
    }
}

void AddSalesOrderView::appendSaleProductOrder(SaleProductOrder *saleProductOrder)
{
    this->saleProductOrders->append(saleProductOrder);

    // Add one more item
    int lastIdx = ui->itemsTableWidget->rowCount();
    ui->itemsTableWidget->setRowCount(lastIdx + 1);

    // Id
    QTableWidgetItem *idItem = new QTableWidgetItem();
    int idItemValue = saleProductOrder->getId();
    idItem->setText(QString::number(idItemValue));
    ui->itemsTableWidget->setItem(lastIdx, 0, idItem);

    // Product Code
    QTableWidgetItem *productCodeItem = new QTableWidgetItem();
    QString productCodeItemValue = saleProductOrder->getProductCode();
    productCodeItem->setText(productCodeItemValue);
    ui->itemsTableWidget->setItem(lastIdx, 1, productCodeItem);

    // Product Name
    ProductController *productController = new ProductController();
    QTableWidgetItem *productNameItem = new QTableWidgetItem();
    QString productNameItemValue = productController->getProductByCode(saleProductOrder->getProductCode())->getName();
    productNameItem->setText(productNameItemValue);
    ui->itemsTableWidget->setItem(lastIdx, 2, productNameItem);
    delete productController;

    // Quantity
    QTableWidgetItem *quantityItem = new QTableWidgetItem();
    int quantityItemValue = saleProductOrder->getQuantity();
    quantityItem->setText(QString::number(quantityItemValue));
    ui->itemsTableWidget->setItem(lastIdx, 3, quantityItem);

    // Value
    Price *p = priceController->getPriceByProductCode(productCodeItemValue);
    double priceValue = p->getValue();

    QTableWidgetItem *priceItem = new QTableWidgetItem();
    double priceItemValue = priceValue * quantityItemValue;
    priceItem->setText(QString::number(priceItemValue));
    ui->itemsTableWidget->setItem(lastIdx, 4, priceItem);

    double totalValue = ui->totalValueLineEdit->text().toDouble();
    totalValue += priceItemValue;
    ui->totalValueLineEdit->setText(QString::number(totalValue));

}

//========= PUBLIC SLOTS ============
void AddSalesOrderView::proceedToAddSalesOrder()
{
    bool ok = false;

    QString receipt = ui->receiptLineEdit->text();
    QDateTime date = (editingSalesOrder) ? editingSalesOrder->getDate() : QDateTime();
    int paymentCondition = ui->paymentConditionLineEdit->text().toInt(&ok);
    int paymentForm = ui->paymentFormComboBox->itemData(ui->paymentFormComboBox->currentIndex()).toInt();
    double discount = ui->discountDoubleSpinBox->value();
    QString observation = ui->observationPlainTextEdit->toPlainText();
    double valuePaid = ui->valuePaidDoubleSpinBox->value();
    QString customerId = ui->customerComboBox->itemData(ui->customerComboBox->currentIndex()).toString();

    if(receipt.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill receipt field."),
                              QMessageBox::Ok);
    }
    else if((ui->paymentConditionLineEdit->text().count() == 0) ||
            (ui->paymentConditionLineEdit->text().count() >0 && !ok))
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Invalid number format. It must contain only digits."),
                              QMessageBox::Ok);
    }
    else if(paymentForm == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("You must select a payment form."),
                              QMessageBox::Ok);
    }
    else{
        Utilities::StatusControl status;
        SalesOrder *salesOrder;
        if(this->editingSalesOrder)
        {
            salesOrder = new SalesOrder(this->editingSalesOrder->getId(), this->saleProductOrders, receipt, date, paymentCondition,
                                        (Utilities::PaymentForm)paymentForm, discount, observation, valuePaid, customerId);
            status = salesOrderController->storeSalesOrder(salesOrder, this->editingSalesOrder->getReceipt());
        }
        else
        {
            salesOrder = new SalesOrder(this->saleProductOrders, receipt, paymentCondition, (Utilities::PaymentForm)paymentForm,
                                        discount, observation, valuePaid, customerId);
            status = salesOrderController->storeSalesOrder(salesOrder);
        }
        delete salesOrder;

        switch(status)
        {
            case Utilities::NO_ERR:
            {
                QMessageBox::information(this,
                                         tr("Error"),
                                         tr("The sales order was successfully recorded!"),
                                         QMessageBox::Ok);

                this->parent->listSalesOrders();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a sales order with that receipt"),
                                      QMessageBox::Ok);
                break;
            }
            case Utilities::EMPTY:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There are no items in this sales order"),
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

void AddSalesOrderView::hideAndClearFieldsData()
{
    emit aboutToClose();
}

void AddSalesOrderView::showPhysicalCustomersList(bool checked)
{
    if(checked)
    {
        QList<PhysicalCustomer*> *physicalCustomersObjects = customerController->getPhysicalCustomers();

        ui->customerComboBox->clear();
        ui->customerComboBox->addItem(QApplication::translate("AddSalesOrderView", "-- Select a customer", 0), QVariant(""));

        int physicalCustomersCount = physicalCustomersObjects->count();
        for(int i=0; i<physicalCustomersCount; i++)
        {
            QString cpf = physicalCustomersObjects->at(i)->getCpf();
            QString name = ((PhysicalCustomer*)physicalCustomersObjects->at(i))->getName();
            ui->customerComboBox->addItem(cpf+" - "+name, QVariant(cpf));
        }
    }
}

void AddSalesOrderView::showEnterpriseCustomersList(bool checked)
{
    if(checked)
    {
        QList<EnterpriseCustomer*> *enterpriseCustomersObjects = customerController->getEnterpriseCustomers();

        ui->customerComboBox->clear();
        ui->customerComboBox->addItem(QApplication::translate("AddSalesOrderView", "-- Select a customer", 0), QVariant(""));

        int enterpriseCustomersCount = enterpriseCustomersObjects->count();
        for(int i=0; i<enterpriseCustomersCount; i++)
        {
            QString cnpj = enterpriseCustomersObjects->at(i)->getCnpj();
            QString name = ((EnterpriseCustomer*)enterpriseCustomersObjects->at(i))->getName();
            ui->customerComboBox->addItem(cnpj+" - "+name, QVariant(cnpj));
        }
    }
}

void AddSalesOrderView::onAddNewSaleProductOrder()
{
    this->parentMainWindow->addFormAddSaleProductOrderToMDI(this);
}

void AddSalesOrderView::onEditSaleProductOrder()
{
    //ui->itemsTableWidget->showColumn(0);
    int rowIdx = ui->itemsTableWidget->selectionModel()->selectedRows().at(0).row();
    //ui->itemsTableWidget->hideColumn(0);

    this->parentMainWindow->addFormEditSaleProductOrderToMDI(this->saleProductOrders->at(rowIdx), this);
}

void AddSalesOrderView::onRemoveSaleProductOrder()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this sale product order?"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
//        ui->itemsTableWidget->showColumn(0);
//        QTableWidgetItem *item = ui->itemsTableWidget->selectedItems().at(0);
//        ui->itemsTableWidget->hideColumn(0);

        int rowIdx = ui->itemsTableWidget->selectionModel()->selectedRows().at(0).row();
        saleProductOrders->removeAt(rowIdx);

        listSaleProductOrders();
    }
}
