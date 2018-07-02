#include "login.h"
#include "ui_login.h"

#include <QCryptographicHash>
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    this->userController = new UserController();

    connect(ui->okPushButton, SIGNAL(released()), this, SLOT(processLogin()));
    connect(ui->cancelPushButton, SIGNAL(released()), this, SLOT(reject()));
}

Login::~Login()
{
    delete ui;
    delete userController;
}

void Login::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

//========= PUBLIC SLOTS ===========
void Login::processLogin()
{
    QString cpf = Utilities::stripCPFChars(ui->cpfLineEdit->text());
    QString password = ui->passwordLineEdit->text();
    QString encryptedPassword = QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Md5).toHex();

    bool result = this->userController->validateLogin(cpf, encryptedPassword);


    if(result)
    {
        User *user = this->userController->getUserByCPF(cpf);
        this->parentMainWindow->setUser(user);
        accept();
    }
    else
    {
        QMessageBox::critical(this,
                              tr("ERPRock"),
                              tr("Invalid cpf/password"),
                              QMessageBox::Ok);
    }
}
