#include "addaccountview.h"
#include "ui_addaccountview.h"

#include <QMessageBox>

AddAccountView::AddAccountView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddAccountView)
{
    ui->setupUi(this);

    this->parent = (AccountsListView*)parent;
    init();

    QString title = QApplication::translate("AddAccountView", "Add new account", 0);
    setWindowTitle(title);

    this->editingAccount = NULL;
}

AddAccountView::AddAccountView(Account *account, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddAccountView)
{
    ui->setupUi(this);

    this->parent = (AccountsListView*)parent;
    init();

    QString title = QApplication::translate("AddAccountView", "Edit account", 0);
    setWindowTitle(title);

    this->editingAccount = account;

    QString accountCode = account->getCode();
    QStringList pieces = accountCode.split(".",QString::SkipEmptyParts);
    QString pattern = "";
    if(pieces.count() != 0)
    {
        pieces.removeLast();
        pattern = pieces.join(".");
    }
    int idxParentComboBox = ui->parentComboBox->findData(QVariant(pattern));
    ui->parentComboBox->setCurrentIndex(idxParentComboBox);

    ui->codeLineEdit->setText(account->getCode());
    ui->typeComboBox->setCurrentIndex(account->getType());
    ui->nameLineEdit->setText(account->getName());
    ui->reductiveCheckBox->setChecked(account->isReductive());
}

AddAccountView::~AddAccountView()
{
    delete ui;

    delete editingAccount;
}

void AddAccountView::init()
{
    QString strSelect = QApplication::translate("AddAccountView", "-- Select a type", 0);
    QString strActive = QApplication::translate("AddAccountView", "Active", 0);
    QString strPassive = QApplication::translate("AddAccountView", "Passive", 0);
    QString strRevenue = QApplication::translate("AddAccountView", "Revenue", 0);
    QString strDeductionsReturns = QApplication::translate("AddAccountView", "Deductions Returns", 0);
    QString strCosts = QApplication::translate("AddAccountView", "Costs", 0);
    QString strOperatingExpenses = QApplication::translate("AddAccountView", "Operating Expenses", 0);

    AccountsController *accountsController = new AccountsController();
    QStringList *types = accountsController->getAccountTypes();

    QStringList typesTranslated;
    typesTranslated << strSelect;
    int typesCount = types->count();
    for(int i=0; i<typesCount; i++)
    {
        QString r = types->at(i);
        typesTranslated << QApplication::translate("AddAccountView", r.toLocal8Bit().constData(), 0);
    }


    ui->typeComboBox->clear();
    ui->typeComboBox->insertItems(0, typesTranslated);

    //=========

    QString strRoot = QApplication::translate("AddAccountView", "Root", 0);
    QList<Account*> *accounts = accountsController->getSyntheticAccounts();

    ui->parentComboBox->clear();
    ui->parentComboBox->addItem(strRoot, QVariant(""));

    int accountsCount = accounts->count();
    for(int i=0; i<accountsCount; i++)
    {
        Account *account = accounts->at(i);
        ui->parentComboBox->addItem(account->getCode() + " - " + account->getName(), QVariant(account->getCode()));
    }

    //=========

    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddAccount()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
    connect(ui->codeLineEdit, SIGNAL(textEdited(QString)), this, SLOT(formatAccountCode(QString)));
    connect(ui->parentComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeMaskCode(int)));
    connect(ui->codeLineEdit, SIGNAL(textEdited(QString)), this, SLOT(adjustCodeLineEditCursor(QString)));
}

void AddAccountView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void AddAccountView::proceedToAddAccount()
{
    QString code = ui->codeLineEdit->text();
    Account::AccountType type = (Account::AccountType) (ui->typeComboBox->currentIndex());
    QString name = ui->nameLineEdit->text();
    bool reductive = ui->reductiveCheckBox->isChecked();

    if(code.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill code field"),
                              QMessageBox::Ok);
    }
    else if(!isCodeFormatValid(code))
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("The inserted code hasn't a valid account format"),
                              QMessageBox::Ok);
    }
    else if(name.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill name field"),
                              QMessageBox::Ok);
    }
    else if(ui->typeComboBox->currentIndex() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select a type"),
                              QMessageBox::Ok);
    }
    else{

        AccountsController *accountsController = new AccountsController();
        Account *account = new Account(code, name, type, reductive);
        Utilities::StatusControl status = (this->editingAccount) ?
                                          accountsController->updateAccount(this->editingAccount->getCode(), account) :
                                          accountsController->addAccount(account);

        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listAccounts();
                emit aboutToClose();
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
            case Utilities::ALREADY_EXISTS:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("There is already an account registered with this code"),
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

void AddAccountView::hideAndClearFieldsData()
{
    emit aboutToClose();
}

void AddAccountView::formatAccountCode(QString text)
{
    QString inputValue = "";

    QStringList list = text.split(".");
    QString code = list.join("");
    int length = code.length();
    switch (length) {
        case 2:
            inputValue = code.at(0);
            inputValue += ".";
            inputValue += code.at(1);
            ui->codeLineEdit->setText(inputValue);
            break;
        case 3:
            inputValue = code.at(0);
            inputValue += ".";
            inputValue += code.at(1);
            inputValue += ".";
            inputValue += code.at(2);
            ui->codeLineEdit->setText(inputValue);
            break;
        case 4:
            inputValue = code.at(0);
            inputValue += ".";
            inputValue += code.at(1);
            inputValue += ".";
            inputValue += code.at(2);
            inputValue += ".";
            inputValue += code.at(3);
            ui->codeLineEdit->setText(inputValue);
            break;
        case 5:
            inputValue = code.at(0);
            inputValue += ".";
            inputValue += code.at(1);
            inputValue += ".";
            inputValue += code.at(2);
            inputValue += ".";
            inputValue += code.at(3);
            inputValue += code.at(4);
            ui->codeLineEdit->setText(inputValue);
            break;
        case 6:
            inputValue = code.at(0);
            inputValue += ".";
            inputValue += code.at(1);
            inputValue += ".";
            inputValue += code.at(2);
            inputValue += ".";
            inputValue += code.at(3);
            inputValue += code.at(4);
            inputValue += code.at(5);
            ui->codeLineEdit->setText(inputValue);
            break;
    }
}

void AddAccountView::changeMaskCode(int index)
{
    ui->codeLineEdit->clearMask();
    ui->codeLineEdit->clear();
    ui->reductiveCheckBox->setEnabled(false);
    QString code = ui->parentComboBox->itemData(index).toString();
    int codeLength = code.length();
    switch(codeLength)
    {
        case 0:
        {
            ui->codeLineEdit->setInputMask("9;");
            break;
        }
        case 1:
        {
            ui->codeLineEdit->setInputMask("9.9;");
            break;
        }
        case 3:
        {
            ui->codeLineEdit->setInputMask("9.9.9;");
            break;
        }
        case 5:
        {
            ui->reductiveCheckBox->setEnabled(true);
            ui->codeLineEdit->setInputMask("9.9.9.999;");
            break;
        }
    }
}

void AddAccountView::adjustCodeLineEditCursor(QString txt)
{
    QStringList pieces = txt.split(".",QString::SkipEmptyParts);

    int count = pieces.count();
    switch(count)
    {
        case 0:
        {
            ui->codeLineEdit->setCursorPosition(0);
            break;
        }
        case 1:
        {
            ui->codeLineEdit->setCursorPosition(2);
            break;
        }
        case 2:
        {
            ui->codeLineEdit->setCursorPosition(4);
            break;
        }
        case 3:
        {
            ui->codeLineEdit->setCursorPosition(6);
            break;
        }
        case 4:
        {
            if(pieces.at(3).count() == 1)
            {
                ui->codeLineEdit->setCursorPosition(7);
            }
            else if(pieces.at(3).count() == 2)
            {
                ui->codeLineEdit->setCursorPosition(8);
            }
            if(pieces.at(3).count() == 3)
            {
                ui->codeLineEdit->setCursorPosition(9);
            }
            break;
        }
    }


}

bool AddAccountView::isCodeFormatValid(QString code)
{
    bool ret = false;

    QString inputMask = ui->codeLineEdit->inputMask().trimmed();
    if((inputMask == "9;") && (code.length() == 1))
    {
        ret = true;
    }
    else if((inputMask == "9.9;") && (code.length() == 3))
    {
        ret = true;
    }
    else if((inputMask == "9.9.9;") && (code.length() == 5))
    {
        ret = true;
    }
    else if((inputMask == "9.9.9.999;") && (code.length() == 9))
    {
        ret = true;
    }

    return ret;
}
