#include "cstpisslistview.h"
#include "ui_cstpisslistview.h"

#include <QMessageBox>

CstPissListView::CstPissListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CstPissListView)
{
    ui->setupUi(this);

    connect(ui->addCstPisPushButton, SIGNAL(released()), this, SLOT(onAddNewCstPis()));
    connect(ui->editCstPisPushButton, SIGNAL(released()), this, SLOT(onEditCstPis()));
    connect(ui->removeCstPisPushButton, SIGNAL(released()), this, SLOT(onRemoveCstPis()));

    cstPisController = new CstPisController();
    listCstPiss();
}

CstPissListView::~CstPissListView()
{
    delete ui;

    delete cstPisController;
}

void CstPissListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void CstPissListView::listCstPiss()
{
    QList<CstPis*> *cstPiss = cstPisController->getCstPiss();

    int count = cstPiss->count();
    ui->cstPissTableWidget->clearContents();
    ui->cstPissTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        CstPis *cstPis = cstPiss->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->cstPissTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // Code
        QTableWidgetItem *codeItem = new QTableWidgetItem();
        QString codeItemValue = cstPis->getCode();
        codeItem->setText(codeItemValue);
        ui->cstPissTableWidget->setItem(i, 0, codeItem);

        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = cstPis->getName();
        nameItem->setText(nameItemValue);
        ui->cstPissTableWidget->setItem(i, 1, nameItem);
    }

    ui->cstPissTableWidget->resizeColumnsToContents();
    ui->cstPissTableWidget->selectRow(0);

    if(count == 0){
        ui->editCstPisPushButton->setEnabled(false);
    }
    else{
        ui->editCstPisPushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void CstPissListView::onAddNewCstPis()
{
    this->parentMainWindow->addFormAddCstPisToMDI();
}

void CstPissListView::onEditCstPis()
{
    QTableWidgetItem *item = ui->cstPissTableWidget->selectedItems().at(0);
    QString code = item->text();
    CstPis *cstPis = cstPisController->getCstPisByCode(code);
    this->parentMainWindow->addFormEditCstPisToMDI(cstPis);
}

void CstPissListView::onRemoveCstPis()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this CST PIS?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->cstPissTableWidget->selectedItems().at(0);
        QString code = item->text();
        Utilities::StatusControl status = cstPisController->removeCstPis(code);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listCstPiss();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered code doesn't belong to any CST PIS of database"),
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
