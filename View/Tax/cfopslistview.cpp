#include "cfopslistview.h"
#include "ui_cfopslistview.h"

#include <QMessageBox>
//#include <QPlainTextEdit>
#include <QLabel>
#include <QScrollArea>
#include <QFileDialog>

CfopsListView::CfopsListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CfopsListView)
{
    ui->setupUi(this);

    windowMode = Utilities::DEFAULT;
    chosenCfop = NULL;

    connect(ui->addCfopPushButton, SIGNAL(released()), this, SLOT(onAddNewCfop()));
    connect(ui->editCfopPushButton, SIGNAL(released()), this, SLOT(onEditCfop()));
    connect(ui->removeCfopPushButton, SIGNAL(released()), this, SLOT(onRemoveCfop()));
    connect(ui->importIntoDBPushButton, SIGNAL(released()), this, SLOT(onImportIntoDB()));

    cfopController = new CfopController();
    listCfops();
}

CfopsListView::~CfopsListView()
{
    delete ui;

    delete cfopController;

    if(chosenCfop)
        delete chosenCfop;
}

void CfopsListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void CfopsListView::listCfops()
{
    QList<Cfop*> *cfops = cfopController->getCfops();

    int count = cfops->count();
    ui->cfopsTableWidget->clearContents();
    ui->cfopsTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        Cfop *cfop = cfops->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->cfopsTableWidget->setVerticalHeaderItem(i, verticalHeader);

        // CFOP
        QTableWidgetItem *cfopItem = new QTableWidgetItem();
        QString cfopItemValue = cfop->getCfop();
        cfopItem->setText(cfopItemValue);
        ui->cfopsTableWidget->setItem(i, 0, cfopItem);

        // Description
        QString descriptionItemValue = cfop->getDescription();
        QLabel *labelDescription = new QLabel(descriptionItemValue);
        QScrollArea *scrollDescription = new QScrollArea();
        scrollDescription->setWidget(labelDescription);
        ui->cfopsTableWidget->setCellWidget(i, 1, scrollDescription);

        // Application
        QString applicationItemValue = cfop->getApplication();
        QLabel *labelApplication = new QLabel(applicationItemValue);
        QScrollArea *scrollApplication = new QScrollArea();
        scrollApplication->setWidget(labelApplication);
        ui->cfopsTableWidget->setCellWidget(i, 2, scrollApplication);

//        int max = 0;
//        int descriptionHeight = labelDescription->height();
//        int applicationHeight = labelApplication->height();
//        if(descriptionHeight < applicationHeight)
//        {
//            max = applicationHeight;
//        }
//        else
//        {
//            max = descriptionHeight;
//        }

//        ui->cfopsTableWidget->verticalHeader()->setDefaultSectionSize(max);

//        // Description
//        QString descriptionItemValue = cfop->getDescription();
//        QPlainTextEdit *plainDescription = new QPlainTextEdit(descriptionItemValue);
//        plainDescription->setReadOnly(true);
//        ui->cfopsTableWidget->setCellWidget(i, 1, plainDescription);

//        // Application
//        QString applicationItemValue = cfop->getApplication();
//        QPlainTextEdit *plainApplication = new QPlainTextEdit(applicationItemValue);
//        plainApplication->setReadOnly(true);
//        ui->cfopsTableWidget->setCellWidget(i, 2, plainApplication);
    }

    ui->cfopsTableWidget->resizeColumnsToContents();
    ui->cfopsTableWidget->selectRow(0);

    if(count == 0){
        ui->editCfopPushButton->setEnabled(false);
    }
    else{
        ui->editCfopPushButton->setEnabled(true);
    }
}

//============== PUBLIC SLOTS ================
void CfopsListView::onAddNewCfop()
{
    this->parentMainWindow->addFormAddCfopToMDI();
}

void CfopsListView::onEditCfop()
{
    QTableWidgetItem *item = ui->cfopsTableWidget->selectedItems().at(0);
    QString cfop = item->text();
    Cfop *cfopObj = cfopController->getCfopByCfop(cfop);
    this->parentMainWindow->addFormEditCfopToMDI(cfopObj);
}

void CfopsListView::onRemoveCfop()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this CFOP?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->cfopsTableWidget->selectedItems().at(0);
        QString cfop = item->text();
        Utilities::StatusControl status = cfopController->removeCfop(cfop);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listCfops();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered cfop doesn't exist at database"),
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

void CfopsListView::onImportIntoDB()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::homePath(),
                                                     tr("Input CFOP files (*.input)"));
    this->cfopController->importCfop(fileName);
    this->listCfops();
}

void CfopsListView::setWindowMode(Utilities::ItemsListWindowMode windowMode)
{
    this->windowMode = windowMode;
    if(this->windowMode == Utilities::CHOOSE_ITEM)
    {
        ui->frame_2->setVisible(false);
        connect(ui->cfopsTableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(onChooseCfop()));
    }
    else
    {
        ui->frame_2->setVisible(true);
        ui->cfopsTableWidget->disconnect();
    }
}

void CfopsListView::setCfopObjectChosen(Cfop *&localChosenCfop)
{
    this->chosenCfop = localChosenCfop;
}

void CfopsListView::onChooseCfop()
{
    QTableWidgetItem *item = ui->cfopsTableWidget->selectedItems().at(0);
    QString cfopCode = item->text();
    Cfop *c = cfopController->getCfopByCfop(cfopCode);

    this->chosenCfop->setCfop(c->getCfop());
    this->chosenCfop->setDescription(c->getDescription());
    this->chosenCfop->setApplication(c->getApplication());


    emit aboutToClose();

    this->close();
}
