#include "cstcofinsslistview.h"
#include "ui_cstcofinsslistview.h"

#include <QMessageBox>

CstCofinssListView::CstCofinssListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CstCofinssListView)
{
    ui->setupUi(this);

    connect(ui->addCstCofinsPushButton, SIGNAL(released()), this, SLOT(onAddNewCstCofins()));
    connect(ui->editCstCofinsPushButton, SIGNAL(released()), this, SLOT(onEditCstCofins()));
    connect(ui->removeCstCofinsPushButton, SIGNAL(released()), this, SLOT(onRemoveCstCofins()));

    cstCofinsController = new CstCofinsController();
    listCstCofinss();
}

CstCofinssListView::~CstCofinssListView()
{
    delete ui;

    delete cstCofinsController;
}

void CstCofinssListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void CstCofinssListView::listCstCofinss()
{
    QList<CstCofins*> *cstCofinss = cstCofinsController->getCstCofinss();

    int count = cstCofinss->count();
    ui->cstCofinssTableWidget->clearContents();
    ui->cstCofinssTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        CstCofins *cstCofins = cstCofinss->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->cstCofinssTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Code
        QTableWidgetItem *codeItem = new QTableWidgetItem();
        QString codeItemValue = cstCofins->getCode();
        codeItem->setText(codeItemValue);
        ui->cstCofinssTableWidget->setItem(i, 0, codeItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = cstCofins->getName();
        nameItem->setText(nameItemValue);
        ui->cstCofinssTableWidget->setItem(i, 1, nameItem);
    }

    ui->cstCofinssTableWidget->resizeColumnsToContents();
    ui->cstCofinssTableWidget->selectRow(0);

    if(count == 0){
        ui->editCstCofinsPushButton->setEnabled(false);
    }
    else{
        ui->editCstCofinsPushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void CstCofinssListView::onAddNewCstCofins()
{
    this->parentMainWindow->addFormAddCstCofinsToMDI();
}

void CstCofinssListView::onEditCstCofins()
{
    QTableWidgetItem *item = ui->cstCofinssTableWidget->selectedItems().at(0);
    QString code = item->text();
    CstCofins *cstCofins = cstCofinsController->getCstCofinsByCode(code);
    this->parentMainWindow->addFormEditCstCofinsToMDI(cstCofins);
}

void CstCofinssListView::onRemoveCstCofins()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this CST COFINS?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->cstCofinssTableWidget->selectedItems().at(0);
        QString code = item->text();
        Utilities::StatusControl status = cstCofinsController->removeCstCofins(code);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listCstCofinss();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered code doesn't belong to any CST COFINS of database"),
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
