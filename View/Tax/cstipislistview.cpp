#include "cstipislistview.h"
#include "ui_cstipislistview.h"

#include <QMessageBox>

CstIpisListView::CstIpisListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CstIpisListView)
{
    ui->setupUi(this);

    connect(ui->addCstIpiPushButton, SIGNAL(released()), this, SLOT(onAddNewCstIpi()));
    connect(ui->editCstIpiPushButton, SIGNAL(released()), this, SLOT(onEditCstIpi()));
    connect(ui->removeCstIpiPushButton, SIGNAL(released()), this, SLOT(onRemoveCstIpi()));

    cstIpiController = new CstIpiController();
    listCstIpis();
}

CstIpisListView::~CstIpisListView()
{
    delete ui;

    delete cstIpiController;
}

void CstIpisListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void CstIpisListView::listCstIpis()
{
    QList<CstIpi*> *cstIpis = cstIpiController->getCstIpis();

    int count = cstIpis->count();
    ui->cstIpisTableWidget->clearContents();
    ui->cstIpisTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        CstIpi *cstIpi = cstIpis->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->cstIpisTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Code
        QTableWidgetItem *codeItem = new QTableWidgetItem();
        QString codeItemValue = cstIpi->getCode();
        codeItem->setText(codeItemValue);
        ui->cstIpisTableWidget->setItem(i, 0, codeItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = cstIpi->getName();
        nameItem->setText(nameItemValue);
        ui->cstIpisTableWidget->setItem(i, 1, nameItem);
    }

    ui->cstIpisTableWidget->resizeColumnsToContents();
    ui->cstIpisTableWidget->selectRow(0);

    if(count == 0){
        ui->editCstIpiPushButton->setEnabled(false);
    }
    else{
        ui->editCstIpiPushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void CstIpisListView::onAddNewCstIpi()
{
    this->parentMainWindow->addFormAddCstIpiToMDI();
}

void CstIpisListView::onEditCstIpi()
{
    QTableWidgetItem *item = ui->cstIpisTableWidget->selectedItems().at(0);
    QString code = item->text();
    CstIpi *cstIpi = cstIpiController->getCstIpiByCode(code);
    this->parentMainWindow->addFormEditCstIpiToMDI(cstIpi);
}

void CstIpisListView::onRemoveCstIpi()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this CST IPI?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->cstIpisTableWidget->selectedItems().at(0);
        QString code = item->text();
        Utilities::StatusControl status = cstIpiController->removeCstIpi(code);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listCstIpis();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered code doesn't belong to any CST IPI of database"),
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
