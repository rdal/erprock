#include "addcfopview.h"
#include "ui_addcfopview.h"

#include <QMessageBox>

AddCfopView::AddCfopView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCfopView)
{
    ui->setupUi(this);

    this->parent = (CfopsListView*)parent;
    init();

    QString title = QApplication::translate("AddCfopView", "Add new cfop", 0);
    setWindowTitle(title);

    this->editingCfop = NULL;
}

AddCfopView::AddCfopView(Cfop *cfopObj, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCfopView)
{
    ui->setupUi(this);

    this->parent = (CfopsListView*)parent;
    init();

    QString title = QApplication::translate("AddCfopView", "Edit cfop", 0);
    setWindowTitle(title);

    this->editingCfop = cfopObj;
    ui->cfopLineEdit->setText(cfopObj->getCfop());
    ui->descriptionPlainTextEdit->setPlainText(cfopObj->getDescription());
    ui->applicationPlainTextEdit->setPlainText(cfopObj->getApplication());
}

AddCfopView::~AddCfopView()
{
    delete ui;

    delete editingCfop;
}

void AddCfopView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddCfop()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddCfopView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddCfopView::proceedToAddCfop()
{
    QString cfop = ui->cfopLineEdit->text();
    QString description = ui->descriptionPlainTextEdit->toPlainText();
    QString application = ui->applicationPlainTextEdit->toPlainText();

    if(cfop.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill cfop field"),
                              QMessageBox::Ok);
    }
    else if(description.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill description field"),
                              QMessageBox::Ok);
    }
    else if(application.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill application field"),
                              QMessageBox::Ok);
    }
    else{

        Cfop *cfopObj;
        CfopController *cfopController = new CfopController();
        cfopObj = new Cfop(cfop, description, application);

        Utilities::StatusControl status = (this->editingCfop) ?
                                          cfopController->updateCfop(this->editingCfop->getCfop(), cfopObj) :
                                          cfopController->addCfop(cfopObj);


        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listCfops();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a cfop registered with this cfop"),
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

void AddCfopView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
