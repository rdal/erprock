#include "addpurchasesorderview.h"
#include "ui_addpurchasesorderview.h"
#include "productcontroller.h"

#include <QMessageBox>

AddPurchasesOrderView::AddPurchasesOrderView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPurchasesOrderView)
{
    ui->setupUi(this);

    this->parent = (PurchasesOrdersListView*)parent;
    init();

    QString title = QApplication::translate("AddPurchasesOrderView", "Add new purchases order", 0);
    setWindowTitle(title);

    this->editingPurchasesOrder = NULL;
    this->purchaseProductOrders = new QList<PurchaseProductOrder*>();
    this->totalValue = 0;

    listPurchaseProductOrders();
}

AddPurchasesOrderView::AddPurchasesOrderView(PurchasesOrder *purchasesOrder, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPurchasesOrderView)
{
    ui->setupUi(this);

    this->parent = (PurchasesOrdersListView*)parent;
    init();

    QString title = QApplication::translate("AddPurchasesOrderView", "Add new purchases order", 0);
    setWindowTitle(title);

    this->editingPurchasesOrder = purchasesOrder;

    // Receipt
    ui->receiptLineEdit->setText(this->editingPurchasesOrder->getReceipt());

    // Payment Condition
    ui->paymentConditionLineEdit->setText(QString::number(this->editingPurchasesOrder->getPaymentCondition()));

    // Payment Form
    Utilities::PaymentForm paymentForm = this->editingPurchasesOrder->getPaymentForm();
    int idxPaymentForm = ui->paymentFormComboBox->findData(QVariant(paymentForm));
    ui->paymentFormComboBox->setCurrentIndex(idxPaymentForm);

    // Provider
    QString providerId = this->editingPurchasesOrder->getProviderId();
    int idxProviderId = ui->providerComboBox->findData(QVariant(providerId));
    ui->providerComboBox->setCurrentIndex(idxProviderId);

    // Date
    ui->dateTimeEdit->setDateTime(this->editingPurchasesOrder->getDate());

    // Observation
    ui->observationPlainTextEdit->setPlainText(this->editingPurchasesOrder->getObservation());

    // Paid Value
    ui->valuePaidDoubleSpinBox->setValue(this->editingPurchasesOrder->getValuePaid());

    // Cargo
    ui->cargoDoubleSpinBox->setValue(this->editingPurchasesOrder->getCargo());

    // Total Value
    this->totalValue = this->editingPurchasesOrder->getValueTotal();
    ui->totalValueLineEdit->setText(QString::number(this->totalValue));

    // Purchases Product Orders
    this->purchaseProductOrders =
            this->purchasesOrderController->getPurchaseProductOrdersByPurchasesOrderId(this->editingPurchasesOrder->getId());

    listPurchaseProductOrders();

}

AddPurchasesOrderView::~AddPurchasesOrderView()
{
    delete ui;
    delete purchasesOrderController;
    delete purchaseProductOrders;
    delete providerController;

    if (editingPurchasesOrder)
        delete editingPurchasesOrder;
}

void AddPurchasesOrderView::init()
{
    this->purchasesOrderController = new PurchasesOrderController();
    ui->paymentConditionLineEdit->setValidator(new QIntValidator(this));

    //========== Payment Form ===========
    ui->paymentFormComboBox->clear();
    ui->paymentFormComboBox->addItem(QApplication::translate("AddPurchasesOrderView", "-- Select a payment condition", 0), QVariant(0));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddPurchasesOrderView", "Money", 0), QVariant(Utilities::MONEY));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddPurchasesOrderView", "Visa", 0), QVariant(Utilities::VISA));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddPurchasesOrderView", "MasterCard", 0), QVariant(Utilities::MASTERCARD));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddPurchasesOrderView", "Diners", 0), QVariant(Utilities::DINERS));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddPurchasesOrderView", "American Express", 0), QVariant(Utilities::AMEX));
    ui->paymentFormComboBox->addItem(QApplication::translate("AddPurchasesOrderView", "Bank Ticket", 0), QVariant(Utilities::BANK_TICKET));


    //=========== Providers ============
    providerController = new ProviderController();
    QList<Provider*> *providersObjects = providerController->getProviders();

    ui->providerComboBox->clear();
    ui->providerComboBox->addItem(QApplication::translate("AddPurchasesOrderView", "-- Select a provider", 0), QVariant(""));

    int providersCount = providersObjects->count();
    for(int i=0; i<providersCount; i++)
    {
        QString cnpj = providersObjects->at(i)->getCNPJ();
        QString name = ((Provider*)providersObjects->at(i))->getName();
        ui->providerComboBox->addItem(cnpj+" - "+name, QVariant(cnpj));
    }

    //====== Date ======
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());



    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddPurchasesOrder()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));

    connect(ui->addProductPushButton, SIGNAL(released()), this, SLOT(onAddNewPurchaseProductOrder()));
    connect(ui->editProductPushButton, SIGNAL(released()), this, SLOT(onEditPurchaseProductOrder()));
    connect(ui->removeProductPushButton, SIGNAL(released()), this, SLOT(onRemovePurchaseProductOrder()));

    connect(ui->cargoDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(onCargoValueChanged(double)));

    delete providersObjects;
}

void AddPurchasesOrderView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void AddPurchasesOrderView::listPurchaseProductOrders()
{
    QLocale locale(QLocale::German);

    this->totalValue = 0;
    int purchaseProductOrderCount = this->purchaseProductOrders->count();
    ui->itemsTableWidget->clearContents();
    ui->itemsTableWidget->setRowCount(purchaseProductOrderCount);
    for(int i=0; i<purchaseProductOrderCount; i++)
    {
        PurchaseProductOrder *purchaseProductOrder = this->purchaseProductOrders->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->itemsTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Id
        QTableWidgetItem *idItem = new QTableWidgetItem();
        int idItemValue = purchaseProductOrder->getId();
        idItem->setText(QString::number(idItemValue));
        ui->itemsTableWidget->setItem(i, 0, idItem);

        // Product Code
        QTableWidgetItem *productCodeItem = new QTableWidgetItem();
        QString productCodeItemValue = purchaseProductOrder->getProductCode();
        productCodeItem->setText(productCodeItemValue);
        ui->itemsTableWidget->setItem(i, 1, productCodeItem);

        // Product Name
        ProductController *productController = new ProductController();
        QTableWidgetItem *productNameItem = new QTableWidgetItem();
        QString productNameItemValue = productController->getProductByCode(purchaseProductOrder->getProductCode())->getName();
        productNameItem->setText(productNameItemValue);
        ui->itemsTableWidget->setItem(i, 2, productNameItem);
        delete productController;

        // Quantity
        QTableWidgetItem *quantityItem = new QTableWidgetItem();
        int quantityItemValue = purchaseProductOrder->getQuantity();
        quantityItem->setText(QString::number(quantityItemValue));
        ui->itemsTableWidget->setItem(i, 3, quantityItem);

        // Value
        QTableWidgetItem *priceItem = new QTableWidgetItem();
        double priceItemValue = purchaseProductOrder->getUnitPrice() * quantityItemValue;
        QString priceItemValueStr = locale.toString(priceItemValue,'f',2);
        priceItem->setText(priceItemValueStr);
        ui->itemsTableWidget->setItem(i, 4, priceItem);

        this->totalValue += priceItemValue;

    }
    double totalWithCargo = totalValue + ui->cargoDoubleSpinBox->value();

    ui->itemsTableWidget->resizeColumnsToContents();
    ui->itemsTableWidget->selectRow(0);
    ui->itemsTableWidget->hideColumn(0);

    QString totalWithCargoStr = locale.toString(totalWithCargo,'f',2);
    ui->totalValueLineEdit->setText(totalWithCargoStr);

    if(purchaseProductOrderCount == 0){
        ui->editProductPushButton->setEnabled(false);
    }
    else{
        ui->editProductPushButton->setEnabled(true);
    }
}

void AddPurchasesOrderView::appendPurchaseProductOrder(PurchaseProductOrder *purchaseProductOrder)
{
    this->purchaseProductOrders->append(purchaseProductOrder);

    // Add one more item
    int lastIdx = ui->itemsTableWidget->rowCount();
    ui->itemsTableWidget->setRowCount(lastIdx + 1);

    // Id
    QTableWidgetItem *idItem = new QTableWidgetItem();
    int idItemValue = purchaseProductOrder->getId();
    idItem->setText(QString::number(idItemValue));
    ui->itemsTableWidget->setItem(lastIdx, 0, idItem);

    // Product Code
    QTableWidgetItem *productCodeItem = new QTableWidgetItem();
    QString productCodeItemValue = purchaseProductOrder->getProductCode();
    productCodeItem->setText(productCodeItemValue);
    ui->itemsTableWidget->setItem(lastIdx, 1, productCodeItem);

    // Product Name
    ProductController *productController = new ProductController();
    QTableWidgetItem *productNameItem = new QTableWidgetItem();
    QString productNameItemValue = productController->getProductByCode(purchaseProductOrder->getProductCode())->getName();
    productNameItem->setText(productNameItemValue);
    ui->itemsTableWidget->setItem(lastIdx, 2, productNameItem);
    delete productController;

    // Quantity
    QTableWidgetItem *quantityItem = new QTableWidgetItem();
    int quantityItemValue = purchaseProductOrder->getQuantity();
    quantityItem->setText(QString::number(quantityItemValue));
    ui->itemsTableWidget->setItem(lastIdx, 3, quantityItem);

    // Value
    QTableWidgetItem *priceItem = new QTableWidgetItem();
    double priceItemValue = purchaseProductOrder->getUnitPrice() * quantityItemValue;
    priceItem->setText(QString::number(priceItemValue));
    ui->itemsTableWidget->setItem(lastIdx, 4, priceItem);

    //double totalValue = ui->totalValueLineEdit->text().toDouble();
    QLocale locale(QLocale::German);
    this->totalValue += priceItemValue;
    double totalWithCargo = this->totalValue + ui->cargoDoubleSpinBox->value();
    QString totalWithCargoStr = locale.toString(totalWithCargo,'f',2);
    ui->totalValueLineEdit->setText(totalWithCargoStr);

}

void AddPurchasesOrderView::proceedToAddPurchasesOrder()
{
    bool ok = false;

    QString receipt = ui->receiptLineEdit->text();
    //QDateTime date = (editingPurchasesOrder) ? editingPurchasesOrder->getDate() : ui->dateTimeEdit->dateTime();
    QDateTime date = ui->dateTimeEdit->dateTime();
    int paymentCondition = ui->paymentConditionLineEdit->text().toInt(&ok);
    int paymentForm = ui->paymentFormComboBox->itemData(ui->paymentFormComboBox->currentIndex()).toInt();
    QString observation = ui->observationPlainTextEdit->toPlainText();
    double valuePaid = ui->valuePaidDoubleSpinBox->value();
    double cargo = ui->cargoDoubleSpinBox->value();
    QString providerId = ui->providerComboBox->itemData(ui->providerComboBox->currentIndex()).toString();

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
        PurchasesOrder *purchasesOrder;
        if(this->editingPurchasesOrder)
        {
            purchasesOrder = new PurchasesOrder(this->editingPurchasesOrder->getId(), this->purchaseProductOrders, receipt,
                                            date, providerId, paymentCondition, (Utilities::PaymentForm)paymentForm,
                                            observation, valuePaid, cargo);
            status = purchasesOrderController->storePurchasesOrder(purchasesOrder, this->editingPurchasesOrder->getReceipt());
        }
        else
        {
            purchasesOrder = new PurchasesOrder(this->purchaseProductOrders, receipt, date, providerId, paymentCondition,
                                                (Utilities::PaymentForm)paymentForm, observation, valuePaid, cargo);
            status = purchasesOrderController->storePurchasesOrder(purchasesOrder);
        }
        delete purchasesOrder;

        switch(status)
        {
            case Utilities::NO_ERR:
            {
                QMessageBox::information(this,
                                         tr("Error"),
                                         tr("The purchases order was successfully recorded!"),
                                         QMessageBox::Ok);

                this->parent->listPurchasesOrders();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a purchases order with that receipt, for the specified provider"),
                                      QMessageBox::Ok);
                break;
            }
            case Utilities::EMPTY:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There are no items in this purchases order"),
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

void AddPurchasesOrderView::hideAndClearFieldsData()
{
    emit aboutToClose();
}

void AddPurchasesOrderView::onAddNewPurchaseProductOrder()
{
    this->parentMainWindow->addFormAddPurchaseProductOrderToMDI(this);
}

void AddPurchasesOrderView::onEditPurchaseProductOrder()
{
    int rowIdx = ui->itemsTableWidget->selectionModel()->selectedRows().at(0).row();
    this->parentMainWindow->addFormEditPurchaseProductOrderToMDI(this->purchaseProductOrders->at(rowIdx), this);
}

void AddPurchasesOrderView::onRemovePurchaseProductOrder()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this purchase product order?"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        int rowIdx = ui->itemsTableWidget->selectionModel()->selectedRows().at(0).row();
        purchaseProductOrders->removeAt(rowIdx);

        listPurchaseProductOrders();
    }
}

void AddPurchasesOrderView::onCargoValueChanged(double val)
{
    QLocale locale(QLocale::German);
    double totalWithCargo = this->totalValue + val;
    QString totalWithCargoStr = locale.toString(totalWithCargo,'f',2);
    ui->totalValueLineEdit->setText(totalWithCargoStr);
}
