#include "addcstipiview.h"
#include "ui_addcstipiview.h"

#include <QMessageBox>

AddCstIpiView::AddCstIpiView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCstIpiView)
{
    ui->setupUi(this);

    this->parent = (CstIpisListView*)parent;
    init();

    QString title = QApplication::translate("AddCstIpiView", "Add new CST IPI", 0);
    setWindowTitle(title);

    this->editingCstIpi = NULL;
}

AddCstIpiView::AddCstIpiView(CstIpi *cstIpi, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCstIpiView)
{
    ui->setupUi(this);

    this->parent = (CstIpisListView*)parent;
    init();

    QString title = QApplication::translate("AddCstIpiView", "Edit CST IPI", 0);
    setWindowTitle(title);

    this->editingCstIpi = cstIpi;
    ui->codeLineEdit->setText(cstIpi->getCode());
    ui->nameLineEdit->setText(cstIpi->getName());
}

AddCstIpiView::~AddCstIpiView()
{
    delete ui;

    delete editingCstIpi;
}

void AddCstIpiView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddCstIpi()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddCstIpiView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddCstIpiView::proceedToAddCstIpi()
{
    QString code = ui->codeLineEdit->text();
    QString name = ui->nameLineEdit->text();

    if(name.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill name field"),
                              QMessageBox::Ok);
    }
    else{

        CstIpi *cstIpi;
        CstIpiController *cstIpiController = new CstIpiController();
        cstIpi = new CstIpi(code, name);

        Utilities::StatusControl status = (this->editingCstIpi) ?
                                          cstIpiController->updateCstIpi(this->editingCstIpi->getCode(), cstIpi) :
                                          cstIpiController->addCstIpi(cstIpi);


        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listCstIpis();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a CST IPI registered with this code"),
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

void AddCstIpiView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
