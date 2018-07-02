#include "addcsticmsview.h"
#include "ui_addcsticmsview.h"

#include <QMessageBox>

AddCstIcmsView::AddCstIcmsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCstIcmsView)
{
    ui->setupUi(this);

    this->parent = (CstIcmssListView*)parent;
    init();

    QString title = QApplication::translate("AddCstIcmsView", "Add new CST ICMS", 0);
    setWindowTitle(title);

    this->editingCstIcms = NULL;
}

AddCstIcmsView::AddCstIcmsView(CstIcms *cstIcms, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCstIcmsView)
{
    ui->setupUi(this);

    this->parent = (CstIcmssListView*)parent;
    init();

    QString title = QApplication::translate("AddCstIcmsView", "Edit CST ICMS", 0);
    setWindowTitle(title);

    this->editingCstIcms = cstIcms;
    ui->codeLineEdit->setText(cstIcms->getCode());
    ui->nameLineEdit->setText(cstIcms->getName());
}

AddCstIcmsView::~AddCstIcmsView()
{
    delete ui;

    delete editingCstIcms;
}

void AddCstIcmsView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddCstIcms()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddCstIcmsView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddCstIcmsView::proceedToAddCstIcms()
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

        CstIcms *cstIcms;
        CstIcmsController *cstIcmsController = new CstIcmsController();
        cstIcms = new CstIcms(code, name);

        Utilities::StatusControl status = (this->editingCstIcms) ?
                                          cstIcmsController->updateCstIcms(this->editingCstIcms->getCode(), cstIcms) :
                                          cstIcmsController->addCstIcms(cstIcms);


        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listCstIcmss();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a CST ICMS registered with this code"),
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

void AddCstIcmsView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
