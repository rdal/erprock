#include "adduserview.h"
#include "ui_adduserview.h"
#include "usercontroller.h"
#include <QCryptographicHash>
#include <QMessageBox>

AddUserView::AddUserView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddUserView)
{
    ui->setupUi(this);

    this->parent = (UsersListView*)parent;
    init();

    QString title = QApplication::translate("AddUserView", "Add new user", 0);
    setWindowTitle(title);
    ui->cpfLineEdit->setReadOnly(false);

    this->editingUser = NULL;
}

AddUserView::AddUserView(User *user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddUserView)
{
    ui->setupUi(this);

    this->parent = (UsersListView*)parent;
    init();

    QString title = QApplication::translate("AddUserView", "Edit user", 0);
    setWindowTitle(title);

    this->editingUser = user;

    ui->cpfLineEdit->setText(user->getCpf());
    ui->cpfLineEdit->setReadOnly(true);
    ui->roleComboBox->setCurrentIndex(user->getRole() + 1); // Plus 1, because the enum type starts with 0
    ui->nameLineEdit->setText(user->getName());
}

AddUserView::~AddUserView()
{
    delete ui;

    //parentMainWindow = NULL;
//    parent = NULL;
    delete editingUser;
}

void AddUserView::init()
{
    QString strSelect = QApplication::translate("AddUserView", "-- Select a role", 0);
    QString strManager = QApplication::translate("AddUserView", "Manager", 0);
    QString strSupervisor = QApplication::translate("AddUserView", "Supervisor", 0);
    QString strStock = QApplication::translate("AddUserView", "Stock", 0);
    QString strSeller = QApplication::translate("AddUserView", "Seller", 0);
    QString strCash = QApplication::translate("AddUserView", "Cash", 0);

    UserController *userController = new UserController();
    QStringList *roles = userController->getUsersRoles();

    QStringList rolesTranslated;
    rolesTranslated << QApplication::translate("AddUserView", "-- Select a role", 0);
    int rolesCount = roles->count();
    for(int i=0; i<rolesCount; i++)
    {
        QString r = roles->at(i);
        rolesTranslated << QApplication::translate("AddUserView", r.toLocal8Bit().constData(), 0);
    }


    ui->roleComboBox->clear();
    ui->roleComboBox->insertItems(0, rolesTranslated);

    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(proceedToAddUser()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(hideAndClearFieldsData()));
}

void AddUserView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void AddUserView::proceedToAddUser()
{
    QString cpf = Utilities::stripCPFChars(ui->cpfLineEdit->text());
    User::UserRole role = (User::UserRole) (ui->roleComboBox->currentIndex() - 1); // Minus 1, because the enum type starts with 0
    QString name = ui->nameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString retypePassword = ui->retypePasswordLineEdit->text();

    if(cpf.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill cpf field"),
                              QMessageBox::Ok);
    }
    else if(ui->roleComboBox->currentIndex() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Select a role"),
                              QMessageBox::Ok);
    }
    else if(name.count() == 0)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill name field"),
                              QMessageBox::Ok);
    }
    else if ((password.count() == 0) && (!this->editingUser))
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Fill password field"),
                              QMessageBox::Ok);
    }
    else if(password != retypePassword)
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Passwords mismatch"),
                              QMessageBox::Ok);
    }
    else{

        QString encryptedPassword = QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Md5).toHex();

        User *user;
        UserController *userController = new UserController();
        Utilities::StatusControl status;
        if(this->editingUser)
        {
            if(password.count() == 0)
            {
                encryptedPassword = this->editingUser->getPassword();
            }
            user = new User(cpf, role, name, encryptedPassword);
            status = userController->updateUser(user);
        }
        else
        {
            user = new User(cpf, role, name, encryptedPassword);
            status = userController->addUser(user);
        }

        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->parent->listUsers();
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
                                      tr("There is already an user registered with this cpf"),
                                      QMessageBox::Ok);
                break;
            }
            case Utilities::INVALID_ID:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The cpf specified is not valid"),
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

void AddUserView::hideAndClearFieldsData()
{
    emit aboutToClose();
}
