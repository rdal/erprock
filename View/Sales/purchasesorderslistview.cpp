#include "purchasesorderslistview.h"
#include "ui_purchasesorderslistview.h"

#include <QMessageBox>
#include <QCheckBox>

PurchasesOrdersListView::PurchasesOrdersListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PurchasesOrdersListView)
{
    ui->setupUi(this);

    connect(ui->addPurchasesOrderPushButton, SIGNAL(released()), this, SLOT(onAddNewPurchasesOrder()));
    connect(ui->editPurchasesOrderPushButton, SIGNAL(released()), this, SLOT(onEditPurchasesOrder()));
    connect(ui->removePurchasesOrderPushButton, SIGNAL(released()), this, SLOT(onRemovePurchasesOrder()));

    purchasesOrderController = new PurchasesOrderController();
    listPurchasesOrders();
}

PurchasesOrdersListView::~PurchasesOrdersListView()
{
    delete ui;
    delete purchasesOrderController;
}

void PurchasesOrdersListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void PurchasesOrdersListView::listPurchasesOrders()
{
    QLocale locale(QLocale::German);

    QList<PurchasesOrder*> *purchasesOrders = purchasesOrderController->getPurchasesOrders();

    int count = purchasesOrders->count();
    ui->purchasesOrdersTableWidget->clearContents();
    ui->purchasesOrdersTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        PurchasesOrder *purchasesOrder = purchasesOrders->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->purchasesOrdersTableWidget->setVerticalHeaderItem(i, verticalHeader);

        //Id
        QTableWidgetItem *idItem = new QTableWidgetItem();
        int idItemValue = purchasesOrder->getId();
        idItem->setText(QString::number(idItemValue));
        ui->purchasesOrdersTableWidget->setItem(i, 0, idItem);

        //Receipt
        QTableWidgetItem *receiptItem = new QTableWidgetItem();
        QString receiptItemValue = purchasesOrder->getReceipt();
        receiptItem->setText(receiptItemValue);
        ui->purchasesOrdersTableWidget->setItem(i, 1, receiptItem);

        //Date
        QTableWidgetItem *dateItem = new QTableWidgetItem();
        QDateTime dateItemValue = purchasesOrder->getDate();
        dateItem->setText(dateItemValue.toString());
        ui->purchasesOrdersTableWidget->setItem(i, 2, dateItem);

        //Provider
        QTableWidgetItem *providerItem = new QTableWidgetItem();
        QString providerItemValue = purchasesOrder->getProviderId();
        providerItem->setText(providerItemValue);
        ui->purchasesOrdersTableWidget->setItem(i, 3, providerItem);

        //Payment Form
        QTableWidgetItem *paymentConditionItem = new QTableWidgetItem();
        QString paymentConditionItemValue = Utilities::getPaymentFormName((Utilities::PaymentForm)purchasesOrder->getPaymentForm());
        paymentConditionItem->setText(paymentConditionItemValue);
        ui->purchasesOrdersTableWidget->setItem(i, 4, paymentConditionItem);

        //Payment Condition
        QTableWidgetItem *paymentFormItem = new QTableWidgetItem();
        int paymentFormItemValue = purchasesOrder->getPaymentCondition();
        paymentFormItem->setText(QString::number(paymentFormItemValue) + "X");
        ui->purchasesOrdersTableWidget->setItem(i, 5, paymentFormItem);

        //Paid Value
        QTableWidgetItem *valuePaidItem = new QTableWidgetItem();
        double valuePaidItemValue = purchasesOrder->getValuePaid();
        QString valuePaidItemValueStr = locale.toString(valuePaidItemValue,'f',2);
        valuePaidItem->setText(valuePaidItemValueStr);
        ui->purchasesOrdersTableWidget->setItem(i, 6, valuePaidItem);

        //Cargo
        QTableWidgetItem *cargoItem = new QTableWidgetItem();
        double cargoItemValue = purchasesOrder->getCargo();
        QString cargoItemValueStr = locale.toString(cargoItemValue,'f',2);
        cargoItem->setText(cargoItemValueStr);
        ui->purchasesOrdersTableWidget->setItem(i, 7, cargoItem);

        //Total Value
        QTableWidgetItem *valueTotalItem = new QTableWidgetItem();
        double valueTotalItemValue = purchasesOrder->getValueTotal();
        QString valueTotalItemValueStr = locale.toString(valueTotalItemValue,'f',2);
        valueTotalItem->setText(valueTotalItemValueStr);
        ui->purchasesOrdersTableWidget->setItem(i, 8, valueTotalItem);
    }

    ui->purchasesOrdersTableWidget->resizeColumnsToContents();
    ui->purchasesOrdersTableWidget->selectRow(0);
    ui->purchasesOrdersTableWidget->hideColumn(0);

    if(count == 0){
        ui->editPurchasesOrderPushButton->setEnabled(false);
    }
    else{
        ui->editPurchasesOrderPushButton->setEnabled(true);
    }

}

//============== PUBLIC SLOTS ===================

void PurchasesOrdersListView::onAddNewPurchasesOrder()
{
    this->parentMainWindow->addFormAddPurchasesOrderToMDI();
}

void PurchasesOrdersListView::onEditPurchasesOrder()
{
    ui->purchasesOrdersTableWidget->showColumn(0);
    QTableWidgetItem *item = ui->purchasesOrdersTableWidget->selectedItems().at(0);
    ui->purchasesOrdersTableWidget->hideColumn(0);

    int id = item->text().toInt();
    PurchasesOrder *purchasesOrder = purchasesOrderController->getPurchasesOrderById(id);
    this->parentMainWindow->addFormEditPurchasesOrderToMDI(purchasesOrder);

}

void PurchasesOrdersListView::onRemovePurchasesOrder()
{

    QMessageBox msgBox(QMessageBox::Warning, tr("ERPRock"),
                       tr("Are you sure you want to remove this purchases order?\nThis action cannot be undone!"),
                       0,
                       0);
    QCheckBox dontPrompt(QObject::tr("Remove all related accounting entries to this purchase order."), &msgBox);

    // HACK: BLOCKING SIGNALS SO QMessageBox WON'T CLOSE
    dontPrompt.blockSignals(true);
    dontPrompt.setCheckState(Qt::Checked);

    msgBox.addButton(&dontPrompt, QMessageBox::ActionRole);

    msgBox.addButton(QMessageBox::Ok);
    msgBox.addButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Ok)
    {
        ui->purchasesOrdersTableWidget->showColumn(0);
        QTableWidgetItem *item = ui->purchasesOrdersTableWidget->selectedItems().at(0);
        ui->purchasesOrdersTableWidget->hideColumn(0);
        int id = item->text().toInt();
        Utilities::StatusControl status = purchasesOrderController->removePurchasesOrder(id, (dontPrompt.checkState() == Qt::Checked));
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listPurchasesOrders();
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

//    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
//                                                           tr("Are you sure you want to remove this purchases order?\n"
//                                                              "This action cannot be undone!"),
//                                                           QMessageBox::Ok | QMessageBox::Cancel,
//                                                           QMessageBox::Cancel);
//    if (ret == QMessageBox::Ok)
//    {
//        ui->purchasesOrdersTableWidget->showColumn(0);
//        QTableWidgetItem *item = ui->purchasesOrdersTableWidget->selectedItems().at(0);
//        ui->purchasesOrdersTableWidget->hideColumn(0);
//        int id = item->text().toInt();
//        Utilities::StatusControl status = purchasesOrderController->removePurchasesOrder(id);
//        switch(status)
//        {
//            case Utilities::NO_ERR:
//            {
//                this->listPurchasesOrders();
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
//    }
}
