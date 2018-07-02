#include "userslistview.h"
#include "ui_userslistview.h"
#include <QMessageBox>

UsersListView::UsersListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsersListView)
{
    ui->setupUi(this);

    connect(ui->addUserPushButton, SIGNAL(released()), this, SLOT(onAddNewUser()));
    connect(ui->editUserPushButton, SIGNAL(released()), this, SLOT(onEditUser()));
    connect(ui->removeUserPushButton, SIGNAL(released()), this, SLOT(onRemoveUser()));

    userController = new UserController();
    listUsers();
}

UsersListView::~UsersListView()
{
    delete ui;

    delete this->userController;
}

void UsersListView::setParentMainWindow(IMainWindow *parentMainWindow)
{
    this->parentMainWindow = parentMainWindow;
}

void UsersListView::listUsers()
{
    QList<User*> *users = userController->getUsers();

    int count = users->count();
    ui->usersTableWidget->clearContents();
    ui->usersTableWidget->setRowCount(count);
    for(int i=0; i<count; i++)
    {
        User *user = users->at(i);
        QTableWidgetItem *verticalHeader = new QTableWidgetItem();
        ui->usersTableWidget->setVerticalHeaderItem(i, verticalHeader);

        //CPF
        QTableWidgetItem *cpfItem = new QTableWidgetItem();
        QString cpfItemValue = user->getCpf();
        cpfItem->setText(cpfItemValue);
        ui->usersTableWidget->setItem(i, 0, cpfItem);

        //Role
        QTableWidgetItem *roleItem = new QTableWidgetItem();
        User::UserRole roleItemValue = user->getRole();
        QString roleTranslated = QApplication::translate("AddUserView", userController->getUserRoleName(roleItemValue).toLocal8Bit().constData(), 0);
        roleItem->setText(roleTranslated);
        ui->usersTableWidget->setItem(i, 1, roleItem);

        //Name
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QString nameItemValue = user->getName();
        nameItem->setText(nameItemValue);
        ui->usersTableWidget->setItem(i, 2, nameItem);
    }

//    ui->usersTableWidget->setRowCount(1);

//    QTableWidgetItem *verticalHeader = new QTableWidgetItem();
//    ui->usersTableWidget->setVerticalHeaderItem(0, verticalHeader);

//    //Destinatario
//    QTableWidgetItem *receiverItem = new QTableWidgetItem();
//    QString receiverItemValue = "AAA";
//    receiverItem->setText(receiverItemValue);
//    ui->usersTableWidget->setItem(0, 0, receiverItem);
//    //Data
//    QTableWidgetItem *dateItem = new QTableWidgetItem();
//    QString dateItemValue = "BBB";
//    dateItem->setText(dateItemValue);
//    ui->usersTableWidget->setItem(0, 1, dateItem);
//    //Mensagem
//    QTableWidgetItem *messageItem = new QTableWidgetItem();
//    QString messageItemValue = "CCC";
//    messageItem->setText(messageItemValue);
//    ui->usersTableWidget->setItem(0, 2, messageItem);

    ui->usersTableWidget->resizeColumnsToContents();
    ui->usersTableWidget->selectRow(0);

    if(count == 0){
        ui->editUserPushButton->setEnabled(false);
    }
    else{
        ui->editUserPushButton->setEnabled(true);
    }

}

//============== PUBLIC SLOTS ===================

void UsersListView::onAddNewUser()
{
    this->parentMainWindow->addFormAddUserToMDI();
}

void UsersListView::onEditUser()
{
    QTableWidgetItem *item = ui->usersTableWidget->selectedItems().at(0);
    QString cpf = item->text();
    User *user = userController->getUserByCPF(cpf);
    this->parentMainWindow->addFormEditUserToMDI(user);

}

void UsersListView::onRemoveUser()
{
    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("ERPRock"),
                                                           tr("Are you sure you want to remove this user?\n"
                                                              "This action cannot be undone!"),
                                                           QMessageBox::Ok | QMessageBox::Cancel,
                                                           QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        QTableWidgetItem *item = ui->usersTableWidget->selectedItems().at(0);
        QString cpf = item->text();
        Utilities::StatusControl status = userController->removeUser(cpf);
        switch(status)
        {
            case Utilities::NO_ERR:
            {
                this->listUsers();
                break;
            }
            case Utilities::DOESNT_EXIST:
            {
                QMessageBox::critical(this,
                                      tr("Error"),
                                      tr("The entered CPF doesn't belong to any user of database"),
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
