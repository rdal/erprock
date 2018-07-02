#include "addcstpisview.h"
#include "ui_addcstpisview.h"

#include <QMessageBox>

AddCstPisView::AddCstPisView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCstPisView)
{
    ui->setupUi(this);

    this->parent = (CstPissListView*)parent;
    init();

    QString title = QApplication::translate("AddCstPisView", "Add new CST PIS", 0);
    setWindowTitle(title);

    this->editingCstPis = NULL;
}

AddCstPisView::AddCstPisView(CstPis *cstPis, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCstPisView)
{
    ui->setupUi(this);

    this->parent = (CstPissListView*)parent;
    init();

    QString title = QApplication::translate("AddCstPisView", "Edit CST PIS", 0);
    setWindowTitle(title);

    this->editingCstPis = cstPis;
    ui->codeLineEdit->setText(cstPis->getCode());
    ui->nameLineEdit->setText(cstPis->getName());
}

AddCstPisView::~AddCstPisView()
{
    delete ui;

    delete editingCstPis;
}

void AddCstPisView::init()
{
    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddCstPis()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddCstPisView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ============
void AddCstPisView::proceedToAddCstPis()
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

        CstPis *cstPis;
        CstPisController *cstPisController = new CstPisController();
        cstPis = new CstPis(code, name);

        Utilities::StatusControl status = (this->editingCstPis) ?
                                          cstPisController->updateCstPis(this->editingCstPis->getCode(), cstPis) :
                                          cstPisController->addCstPis(cstPis);


        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listCstPiss();
                emit aboutToClose();
                break;
            }
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already a CST PIS registered with this code"),
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

void AddCstPisView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
