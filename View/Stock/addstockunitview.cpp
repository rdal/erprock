#include "addstockunitview.h"
#include "ui_addstockunitview.h"

#include <QMessageBox>

AddStockUnitView::AddStockUnitView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddStockUnitView)
{
    ui->setupUi(this);

    this->parent = (StockUnitsListView*)parent;
    init();

    QString title = QApplication::translate("AddStockUnitView", "Add new stock unit", 0);
    setWindowTitle(title);

    this->editingStockUnit = NULL;
}

AddStockUnitView::AddStockUnitView(StockUnit *stockUnit, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddStockUnitView)
{
    ui->setupUi(this);

    this->parent = (StockUnitsListView*)parent;
    init();

    QString title = QApplication::translate("AddStockUnitView", "Edit stock unit", 0);
    setWindowTitle(title);

    this->editingStockUnit = stockUnit;
    ui->nameLineEdit->setText(stockUnit->getName());
}

AddStockUnitView::~AddStockUnitView()
{
    delete ui;

    delete editingStockUnit;
}

void AddStockUnitView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddStockUnit()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddStockUnitView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddStockUnitView::proceedToAddStockUnit()
{
    QString name = ui->nameLineEdit->text();

    if(name.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill name field"),
                              QMessageBox::Ok);
    }
    else{

        StockUnit *stockUnit;
        StockUnitController *stockUnitController = new StockUnitController();
        stockUnit = new StockUnit(name);

        Utilities::StatusControl status;
        if(this->editingStockUnit)
        {
            stockUnit->setId(this->editingStockUnit->getId());
            status = stockUnitController->updateStockUnit(stockUnit);
        }
        else
        {
            status = stockUnitController->addStockUnit(stockUnit);
        }


        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listStockUnits();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a stock unit registered with this name"),
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

void AddStockUnitView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
