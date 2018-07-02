#include "addtaxrateview.h"
#include "ui_addtaxrateview.h"

#include <QMessageBox>

AddTaxRateView::AddTaxRateView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddTaxRateView)
{
    ui->setupUi(this);

    this->parent = (TaxRatesListView*)parent;
    init();

    QString title = QApplication::translate("AddTaxRateView", "Add new tax rate", 0);
    setWindowTitle(title);

    this->editingTaxRate = NULL;
}

AddTaxRateView::AddTaxRateView(TaxRate *taxRate, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddTaxRateView)
{
    ui->setupUi(this);

    this->parent = (TaxRatesListView*)parent;
    init();

    QString title = QApplication::translate("AddTaxRateView", "Edit tax rate", 0);
    setWindowTitle(title);

    this->editingTaxRate = taxRate;
    ui->nameLineEdit->setText(taxRate->getName());
    ui->nameDoubleSpinBox->setValue(taxRate->getValue());
}

AddTaxRateView::~AddTaxRateView()
{
    delete ui;

    delete editingTaxRate;
}

void AddTaxRateView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddTaxRate()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddTaxRateView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddTaxRateView::proceedToAddTaxRate()
{
    QString name = ui->nameLineEdit->text();
    double value = ui->nameDoubleSpinBox->value();

    if(name.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill name field"),
                              QMessageBox::Ok);
    }
    else{

        TaxRate *taxRate;
        TaxRateController *taxRateController = new TaxRateController();
        taxRate = new TaxRate(name, value);

        Utilities::StatusControl status = (this->editingTaxRate) ?
                                          taxRateController->updateTaxRate(this->editingTaxRate->getName(), taxRate) :
                                          taxRateController->addTaxRate(taxRate);


        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listTaxRates();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a tax rate registered with this name"),
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

void AddTaxRateView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
