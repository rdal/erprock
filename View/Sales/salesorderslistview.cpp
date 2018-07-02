#include "salesorderslistview.h"
#include "ui_salesorderslistview.h"

#include <QMessageBox>
#include <QCheckBox>

SalesOrdersListView::SalesOrdersListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SalesOrdersListView)
{
    ui->setupUi(this);

    connect(ui->addSalesOrderPushButton, SIGNAL(released()), this, SLOT(onAddNewSalesOrder()));
    connect(ui->editSalesOrderPushButton, SIGNAL(released()), this, SLOT(onEditSalesOrder()));
    connect(ui->removeSalesOrderPushButton, SIGNAL(released()), this, SLOT(onRemoveSalesOrder()));

    salesOrderController = new SalesOrderController();
    listSalesOrders();
}

SalesOrdersListView::~SalesOrdersListView()
{
    delete ui;

    delete this->salesOrderController;
}

void SalesOrdersListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void SalesOrdersListView::listSalesOrders()
{
    QLocale locale(QLocale::German);

    QList<SalesOrder*> *salesOrders = salesOrderController->getSalesOrders();

    int count = salesOrders->count();
    ui->salesOrdersTableWidget->clearContents();
    ui->salesOrdersTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        SalesOrder *salesOrder = salesOrders->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->salesOrdersTableWidget->setVerticalHeaderItem(i, verticalHeader);

        //Id
        QTableWidgetItem *idItem = new QTableWidgetItem();
        int idItemValue = salesOrder->getId();
        idItem->setText(QString::number(idItemValue));
        ui->salesOrdersTableWidget->setItem(i, 0, idItem);

        //Receipt
        QTableWidgetItem *receiptItem = new QTableWidgetItem();
        QString receiptItemValue = salesOrder->getReceipt();
        receiptItem->setText(receiptItemValue);
        ui->salesOrdersTableWidget->setItem(i, 1, receiptItem);

        //Date
        QTableWidgetItem *dateItem = new QTableWidgetItem();
        QDateTime dateItemValue = salesOrder->getDate();
        dateItem->setText(dateItemValue.toString());
        ui->salesOrdersTableWidget->setItem(i, 2, dateItem);

        //Payment Form
        QTableWidgetItem *paymentConditionItem = new QTableWidgetItem();
        QString paymentConditionItemValue = Utilities::getPaymentFormName((Utilities::PaymentForm)salesOrder->getPaymentForm());
        paymentConditionItem->setText(paymentConditionItemValue);
        ui->salesOrdersTableWidget->setItem(i, 3, paymentConditionItem);

        //Payment Condition
        QTableWidgetItem *paymentFormItem = new QTableWidgetItem();
        int paymentFormItemValue = salesOrder->getPaymentCondition();
        paymentFormItem->setText(QString::number(paymentFormItemValue) + "X");
        ui->salesOrdersTableWidget->setItem(i, 4, paymentFormItem);

        //Discount
        QTableWidgetItem *discountItem = new QTableWidgetItem();
        double discountItemValue = salesOrder->getDiscount();
        discountItem->setText(QString::number(discountItemValue));
        ui->salesOrdersTableWidget->setItem(i, 5, discountItem);

        //Paid Value
        QTableWidgetItem *valuePaidItem = new QTableWidgetItem();
        double valuePaidItemValue = salesOrder->getValuePaid();
        QString valuePaidItemValueStr = locale.toString(valuePaidItemValue,'f',2);
        valuePaidItem->setText(valuePaidItemValueStr);
        ui->salesOrdersTableWidget->setItem(i, 6, valuePaidItem);

        //Total Value
        QTableWidgetItem *valueTotalItem = new QTableWidgetItem();
        double valueTotalItemValue = salesOrder->getValueTotal();
        QString valueTotalItemValueStr = locale.toString(valueTotalItemValue,'f',2);
        valueTotalItem->setText(valueTotalItemValueStr);
        ui->salesOrdersTableWidget->setItem(i, 7, valueTotalItem);
    }

    ui->salesOrdersTableWidget->resizeColumnsToContents();
    ui->salesOrdersTableWidget->selectRow(0);
    ui->salesOrdersTableWidget->hideColumn(0);

    if(count == 0){
        ui->editSalesOrderPushButton->setEnabled(false);
    }
    else{
        ui->editSalesOrderPushButton->setEnabled(true);
    }

}

//============== PUBLIC SLOTS ===================

void SalesOrdersListView::onAddNewSalesOrder()
{
    this->parentMainWindow->addFormAddSalesOrderToMDI();
}

void SalesOrdersListView::onEditSalesOrder()
{
    ui->salesOrdersTableWidget->showColumn(0);
    QTableWidgetItem *item = ui->salesOrdersTableWidget->selectedItems().at(0);
    ui->salesOrdersTableWidget->hideColumn(0);

    int id = item->text().toInt();
    SalesOrder *salesOrder = salesOrderController->getSalesOrderById(id);
    this->parentMainWindow->addFormEditSalesOrderToMDI(salesOrder);

}

void SalesOrdersListView::onRemoveSalesOrder()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("ERPRock"),
                       tr("Are you sure you want to remove this sales order?\nThis action cannot be undone!"),
                       0,
                       0);
    QCheckBox dontPrompt(QObject::tr("Remove all related accounting entries to this sale order."), &msgBox);

    // HACK: BLOCKING SIGNALS SO QMessageBox WON'T CLOSE
    dontPrompt.blockSignals(true);
    dontPrompt.setCheckState(Qt::Checked);

    msgBox.addButton(&dontPrompt, QMessageBox::ActionRole);

    msgBox.addButton(QMessageBox::Ok);
    msgBox.addButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Ok)
    {
        ui->salesOrdersTableWidget->showColumn(0);
        QTableWidgetItem *item = ui->salesOrdersTableWidget->selectedItems().at(0);
        ui->salesOrdersTableWidget->hideColumn(0);
        int id = item->text().toInt();
        Utilities::StatusControl status = salesOrderController->removeSalesOrder(id, (dontPrompt.checkState() == Qt::Checked));
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listSalesOrders();
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
//                                                           tr("Are you sure you want to remove this sales order?\n"
//                                                              "This action cannot be undone!"),
//                                                           QMessageBox::Ok | QMessageBox::Cancel,
//                                                           QMessageBox::Cancel);
//    if (ret == QMessageBox::Ok)
//    {
//        ui->salesOrdersTableWidget->showColumn(0);
//        QTableWidgetItem *item = ui->salesOrdersTableWidget->selectedItems().at(0);
//        ui->salesOrdersTableWidget->hideColumn(0);
//        int id = item->text().toInt();
//        Utilities::StatusControl status = salesOrderController->removeSalesOrder(id);
//        switch(status)
//        {
//            case Utilities::NO_ERR:
//            {
//                this->listSalesOrders();
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
