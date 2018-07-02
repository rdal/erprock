#include "csticmsslistview.h"
#include "ui_csticmsslistview.h"

#include <QMessageBox>

CstIcmssListView::CstIcmssListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CstIcmssListView)
{
    ui->setupUi(this);

    connect(ui->addCstIcmsPushButton, SIGNAL(released()), this, SLOT(onAddNewCstIcms()));
    connect(ui->editCstIcmsPushButton, SIGNAL(released()), this, SLOT(onEditCstIcms()));
    connect(ui->removeCstIcmsPushButton, SIGNAL(released()), this, SLOT(onRemoveCstIcms()));

    cstIcmsController = new CstIcmsController();
    listCstIcmss();
}

CstIcmssListView::~CstIcmssListView()
{
    delete ui;

    delete cstIcmsController;
}

void CstIcmssListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void CstIcmssListView::listCstIcmss()
{
    QList<CstIcms*> *cstIcmss = cstIcmsController->getCstIcmss();

    int count = cstIcmss->count();
    ui->cstIcmssTableWidget->clearContents();
    ui->cstIcmssTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        CstIcms *cstIcms = cstIcmss->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->cstIcmssTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Code
        QTableWidgetItem *codeItem = new QTableWidgetItem();
        QString codeItemValue = cstIcms->getCode();
        codeItem->setText(codeItemValue);
        ui->cstIcmssTableWidget->setItem(i, 0, codeItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = cstIcms->getName();
        nameItem->setText(nameItemValue);
        ui->cstIcmssTableWidget->setItem(i, 1, nameItem);
    }

    ui->cstIcmssTableWidget->resizeColumnsToContents();
    ui->cstIcmssTableWidget->selectRow(0);

    if(count == 0){
        ui->editCstIcmsPushButton->setEnabled(false);
    }
    else{
        ui->editCstIcmsPushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void CstIcmssListView::onAddNewCstIcms()
{
    this->parentMainWindow->addFormAddCstIcmsToMDI();
}

void CstIcmssListView::onEditCstIcms()
{
    QTableWidgetItem *item = ui->cstIcmssTableWidget->selectedItems().at(0);
    QString code = item->text();
    CstIcms *cstIcms = cstIcmsController->getCstIcmsByCode(code);
    this->parentMainWindow->addFormEditCstIcmsToMDI(cstIcms);
}

void CstIcmssListView::onRemoveCstIcms()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this CST ICMS?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->cstIcmssTableWidget->selectedItems().at(0);
        QString code = item->text();
        Utilities::StatusControl status = cstIcmsController->removeCstIcms(code);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listCstIcmss();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered code doesn't belong to any CST ICMS of database"),
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
