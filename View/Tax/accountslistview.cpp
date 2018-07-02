#include "accountslistview.h"
#include "ui_accountslistview.h"

#include <QMessageBox>

AccountsListView::AccountsListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountsListView)
{
    ui->setupUi(this);

    connect(ui->addAccountPushButton, SIGNAL(released()), this, SLOT(onAddNewAccount()));
    connect(ui->editAccountPushButton, SIGNAL(released()), this, SLOT(onEditAccount()));
    connect(ui->removeAccountPushButton, SIGNAL(released()), this, SLOT(onRemoveAccount()));

    accountsController = new AccountsController();
    listAccounts();
}

AccountsListView::~AccountsListView()
{
    delete ui;

    delete this->accountsController;
}

void AccountsListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void AccountsListView::listAccounts()
{
    QList<Account*> *accounts = accountsController->getAccounts();

    int count = accounts->count();
    ui->accountsTableWidget->clearContents();
    ui->accountsTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        Account *account = accounts->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->accountsTableWidget->setVerticalHeaderItem(i, verticalHeader);

        //CPF
        QTableWidgetItem *codeItem = new QTableWidgetItem();
        QString codeItemValue = account->getCode();
        codeItem->setText(codeItemValue);
        ui->accountsTableWidget->setItem(i, 0, codeItem);

        //Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = account->getName();
        nameItem->setText(nameItemValue);
        ui->accountsTableWidget->setItem(i, 1, nameItem);
    }

    ui->accountsTableWidget->resizeColumnsToContents();
    ui->accountsTableWidget->selectRow(0);

    if(count == 0){
        ui->editAccountPushButton->setEnabled(false);
    }
    else{
        ui->editAccountPushButton->setEnabled(true);
    }
}

void AccountsListView::onAddNewAccount()
{
    this->parentMainWindow->addFormAddAccountToMDI();
}

void AccountsListView::onEditAccount()
{
    QTableWidgetItem *item = ui->accountsTableWidget->selectedItems().at(0);
    QString code = item->text();
    Account *account = accountsController->getAccountByCode(code);
    this->parentMainWindow->addFormEditAccountToMDI(account);
}

void AccountsListView::onRemoveAccount()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this account?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->accountsTableWidget->selectedItems().at(0);
        QString code = item->text();
        Utilities::StatusControl status = accountsController->removeAccount(code);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listAccounts();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered Code doesn't belong to any account of database"),
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
