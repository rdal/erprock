#include "addcstcofinsview.h"
#include "ui_addcstcofinsview.h"

#include <QMessageBox>

AddCstCofinsView::AddCstCofinsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCstCofinsView)
{
    ui->setupUi(this);

    this->parent = (CstCofinssListView*)parent;
    init();

    QString title = QApplication::translate("AddCstCofinsView", "Add new CST COFINS", 0);
    setWindowTitle(title);

    this->editingCstCofins = NULL;
}

AddCstCofinsView::AddCstCofinsView(CstCofins *cstCofins, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCstCofinsView)
{
    ui->setupUi(this);

    this->parent = (CstCofinssListView*)parent;
    init();

    QString title = QApplication::translate("AddCstCofinsView", "Edit CST COFINS", 0);
    setWindowTitle(title);

    this->editingCstCofins = cstCofins;
    ui->codeLineEdit->setText(cstCofins->getCode());
    ui->nameLineEdit->setText(cstCofins->getName());
}

AddCstCofinsView::~AddCstCofinsView()
{
    delete ui;

    delete editingCstCofins;
}

void AddCstCofinsView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddCstCofins()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddCstCofinsView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddCstCofinsView::proceedToAddCstCofins()
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

        CstCofins *cstCofins;
        CstCofinsController *cstCofinsController = new CstCofinsController();
        cstCofins = new CstCofins(code, name);

        Utilities::StatusControl status = (this->editingCstCofins) ?
                                          cstCofinsController->updateCstCofins(this->editingCstCofins->getCode(), cstCofins) :
                                          cstCofinsController->addCstCofins(cstCofins);


        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listCstCofinss();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a CST COFINS registered with this code"),
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

void AddCstCofinsView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
