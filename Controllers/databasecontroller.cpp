#include "databasecontroller.h"
#include "utilities.h"
#include "filenotfoundexception.h"

#include <QFile>
#include <QDebug>
#include <QDir>
#include <QSqlDatabase>

#ifdef DB_POSTGRESQL

#ifdef Q_OS_UNIX
#include "/usr/local/qt-everywhere-opensource-src-4.8.0/src/sql/drivers/psql/qsql_psql.cpp"
#elif (defined Q_OS_WIN)
#include "C:\\qt-everywhere-opensource-src-5.2.0\\qtbase\\src\\sql\\drivers\\psql\\qsql_psql.cpp"
#endif

#endif

DatabaseController* DatabaseController::pInstance = NULL;

DatabaseController::DatabaseController(QObject *parent) :
    QObject(parent)
{
    this->conOpen = false;
    this->con = NULL;
    this->defaultStore = NULL;

    try{
        QString uri = readDBConfig();
        QSqlDriver *drv;

#ifdef DB_POSTGRESQL
        con = PQconnectdb(uri.toLocal8Bit().constData());
        drv =  new QPSQLDriver(con);
#endif
        QSqlDatabase::addDatabase(drv); // becomes the new default connection

        this->conOpen = true;

        defineDefaultStore();
//        defineMainAccounts();
//        defineMainHistories();

    } catch(FileNotFoundException &e) {
        qDebug() << "DB Config File Exception:" << e.what();
    }
}

DatabaseController::~DatabaseController()
{
    if(pInstance)
    {

#ifdef DB_POSTGRESQL
        PQfinish(con);
        con = NULL;
#endif
        delete pInstance;
        pInstance = NULL;
    }

    if (defaultStore)
    {
        delete defaultStore;
        defaultStore = NULL;
    }
}

DatabaseController* DatabaseController::getInstance()
{
    if(pInstance == NULL){
        pInstance = new DatabaseController();
    }
    return pInstance;
}

Store *DatabaseController::getDefaultStore()
{
    return this->defaultStore;
}

////QString DatabaseController::getDefaultCustomerAccount()
////{
////    return this->customerAccount;
////}

//QString DatabaseController::getDefaultProviderAccount()
//{
//    return this->providerAccount;
//}

////QString DatabaseController::getDefaultCashAccount()
////{
////    return this->cashAccount;
////}

//QString DatabaseController::getDefaultIcmsToRecoverAccount()
//{
//    return this->icmsToRecoverAccount;
//}

//QString DatabaseController::getDefaultPisToRecoverAccount()
//{
//    return this->pisToRecoverAccount;
//}

//QString DatabaseController::getDefaultCofinsToRecoverAccount()
//{
//    return this->cofinsToRecoverAccount;
//}

//QString DatabaseController::getDefaultProductStockAccount()
//{
//    return this->productStockAccount;
//}

//QString DatabaseController::getDefaultDebtorSaleAccount()
//{
//    return this->debtorSaleAccount;
//}

//QString DatabaseController::getDefaultCreditorSaleAccount()
//{
//    return this->creditorSaleAccount;
//}

//QString DatabaseController::getDefaultIcmsInSalesDebtorAccount()
//{
//    return this->icmsInSalesDebtorAccount;
//}

//QString DatabaseController::getDefaultIcmsInSalesCreditorAccount()
//{
//    return this->icmsInSalesCreditorAccount;
//}

//QString DatabaseController::getDefaultPisInSalesDebtorAccount()
//{
//    return this->pisInSalesDebtorAccount;
//}

//QString DatabaseController::getDefaultPisInSalesCreditorAccount()
//{
//    return this->pisInSalesCreditorAccount;
//}

//QString DatabaseController::getDefaultCofinsInSalesDebtorAccount()
//{
//    return this->cofinsInSalesDebtorAccount;
//}

//QString DatabaseController::getDefaultCofinsInSalesCreditorAccount()
//{
//    return this->cofinsInSalesCreditorAccount;
//}

//QString DatabaseController::getDefaultGoodsShippingDebtorAccount()
//{
//    return this->goodsShippingDebtorAccount;
//}

//QString DatabaseController::getDefaultGoodsShippingCreditorAccount()
//{
//    return this->goodsShippingCreditorAccount;
//}

//int DatabaseController::getBuyProductHistoryId()
//{
//    return this->buyProductHistoryId;
//}

//int DatabaseController::getTaxCreditHistoryId()
//{
//    return this->taxCreditHistoryId;
//}

//int DatabaseController::getSaleHistoryId()
//{
//    return this->saleHistoryId;
//}

//int DatabaseController::getIcmsInSalesHistoryId()
//{
//    return this->icmsInSalesHistoryId;
//}

//int DatabaseController::getPisInSalesHistoryId()
//{
//    return this->pisInSalesHistoryId;
//}

//int DatabaseController::getCofinsInSalesHistoryId()
//{
//    return this->cofinsInSalesHistoryId;
//}

//int DatabaseController::getGoodsShippingHistoryId()
//{
//    return this->goodsShippingHistoryId;
//}

//---

bool DatabaseController::isConnectionOpen()
{
    return this->conOpen;
}

void DatabaseController::defineDefaultStore()
{
    QString defaultStoreCnpj;

    QString configFilepath = Utilities::getResourcesPath() + QDir::separator() + "config" + QDir::separator() + "erprock.conf";
    QFile* file = new QFile(configFilepath);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw FileNotFoundException();
    }

    while (!file->atEnd()) {
        QByteArray line = file->readLine();
        QString strLine = QString(line).trimmed();
        QStringList pieces = strLine.split("=");
        QString prefix = ((QString)pieces.at(0)).trimmed();
        if(prefix == PREFIX_DEFAULT_STORE)
        {
            defaultStoreCnpj = ((QString)pieces.at(1)).trimmed();
            break;
        }
    }
    file->close();

    if(defaultStoreCnpj.count() != 0)
    {
        this->defaultStore = this->getStoreByCNPJ(defaultStoreCnpj);
    }
}

//void DatabaseController::defineMainAccounts()
//{
//    QString configFilepath = Utilities::getResourcesPath() + QDir::separator() + "config" + QDir::separator() + "erprock.conf";
//    QFile* file = new QFile(configFilepath);
//    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        throw FileNotFoundException();
//    }

//    while (!file->atEnd()) {
//        QByteArray line = file->readLine();
//        QString strLine = QString(line).trimmed();
//        QStringList pieces = strLine.split("=");
//        QString prefix = ((QString)pieces.at(0)).trimmed();
////        if(prefix == PREFIX_CUSTOMER_ACCOUNT)
////        {
////            this->customerAccount = ((QString)pieces.at(1)).trimmed();
////        }
//        if(prefix == PREFIX_PROVIDER_ACCOUNT)
//        {
//            this->providerAccount = ((QString)pieces.at(1)).trimmed();
//        }
////        else if(prefix == PREFIX_CASH_ACCOUNT)
////        {
////            this->cashAccount = ((QString)pieces.at(1)).trimmed();
////        }
//        else if(prefix == PREFIX_ICMS_TO_RECOVER)
//        {
//            this->icmsToRecoverAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_PIS_TO_RECOVER)
//        {
//            this->pisToRecoverAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_COFINS_TO_RECOVER)
//        {
//            this->cofinsToRecoverAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_PRODUCT_STOCK)
//        {
//            this->productStockAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_DEBTOR_ACCOUNT_SALE)
//        {
//            this->debtorSaleAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_CREDITOR_ACCOUNT_SALE)
//        {
//            this->creditorSaleAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_ICMS_IN_SALES_DEBTOR_ACCOUNT)
//        {
//            this->icmsInSalesDebtorAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_ICMS_IN_SALES_CREDITOR_ACCOUNT)
//        {
//            this->icmsInSalesCreditorAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_PIS_IN_SALES_DEBTOR_ACCOUNT)
//        {
//            this->pisInSalesDebtorAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_PIS_IN_SALES_CREDITOR_ACCOUNT)
//        {
//            this->pisInSalesCreditorAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_COFINS_IN_SALES_DEBTOR_ACCOUNT)
//        {
//            this->cofinsInSalesDebtorAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_COFINS_IN_SALES_CREDITOR_ACCOUNT)
//        {
//            this->cofinsInSalesCreditorAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_GOODS_SHIPPING_DEBTOR_ACCOUNT)
//        {
//            this->goodsShippingDebtorAccount = ((QString)pieces.at(1)).trimmed();
//        }
//        else if(prefix == PREFIX_GOODS_SHIPPING_CREDITOR_ACCOUNT)
//        {
//            this->goodsShippingCreditorAccount = ((QString)pieces.at(1)).trimmed();
//        }
//    }
//    file->close();
//}

//void DatabaseController::defineMainHistories()
//{
//    QString configFilepath = Utilities::getResourcesPath() + QDir::separator() + "config" + QDir::separator() + "erprock.conf";
//    QFile* file = new QFile(configFilepath);
//    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        throw FileNotFoundException();
//    }

//    while (!file->atEnd()) {
//        QByteArray line = file->readLine();
//        QString strLine = QString(line).trimmed();
//        QStringList pieces = strLine.split("=");
//        QString prefix = ((QString)pieces.at(0)).trimmed();
//        if(prefix == PREFIX_BUY_PRODUCT_HISTORY_ID)
//        {
//            this->buyProductHistoryId = ((QString)pieces.at(1)).trimmed().toInt();
//        }
//        else if(prefix == PREFIX_TAX_CREDIT_HISTORY_ID)
//        {
//            this->taxCreditHistoryId = ((QString)pieces.at(1)).trimmed().toInt();
//        }
//        else if(prefix == PREFIX_SALE_HISTORY_ID)
//        {
//            this->saleHistoryId = ((QString)pieces.at(1)).trimmed().toInt();
//        }
//        else if(prefix == PREFIX_ICMS_IN_SALES_HISTORY_ID)
//        {
//            this->icmsInSalesHistoryId = ((QString)pieces.at(1)).trimmed().toInt();
//        }
//        else if(prefix == PREFIX_PIS_IN_SALES_HISTORY_ID)
//        {
//            this->pisInSalesHistoryId = ((QString)pieces.at(1)).trimmed().toInt();
//        }
//        else if(prefix == PREFIX_COFINS_IN_SALES_HISTORY_ID)
//        {
//            this->cofinsInSalesHistoryId = ((QString)pieces.at(1)).trimmed().toInt();
//        }
//        else if(prefix == PREFIX_GOODS_SHIPPING_HISTORY_ID)
//        {
//            this->goodsShippingHistoryId = ((QString)pieces.at(1)).trimmed().toInt();
//        }
//    }
//    file->close();
//}

QString DatabaseController::readDBConfig()
{
    QString ret = "";

    //QString configFilepath = Utilities::getResourcesPath() + QDir::separator() + "config" + QDir::separator() + "db.conf";
	QString configFilepath = "config";
	configFilepath += QDir::separator();
	configFilepath += "db.conf";

    QFile* file = new QFile(configFilepath);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw FileNotFoundException();
    }

    QString str = "";
    while (!file->atEnd()) {
        QByteArray line = file->readLine();
        QString strLine = QString(line).trimmed();
        str = str + strLine + " ";
    }
    file->close();

    ret = str.trimmed();

    return ret;
}

bool DatabaseController::userAlreadyExists(QString cpf)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_users WHERE cpf='"+cpf+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewUser(QString cpf, User::UserRole role, QString name, QString password)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_users (cpf, role, name, password) VALUES(:cpf, :role, :name, :password)");
    insertQuery.bindValue(":cpf", cpf);
    insertQuery.bindValue(":role", role);
    insertQuery.bindValue(":name", name);
    insertQuery.bindValue(":password", password);

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateUser(QString cpf, User::UserRole role, QString name, QString password)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_users SET role=:role, name=:name, password=:password WHERE cpf=:cpf");
    updateQuery.bindValue(":cpf", cpf);
    updateQuery.bindValue(":role", role);
    updateQuery.bindValue(":name", name);
    updateQuery.bindValue(":password", password);

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeUser(QString cpf)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_users WHERE cpf=:cpf");
    deleteQuery.bindValue(":cpf", cpf);

    ret = deleteQuery.exec();

    return ret;
}

User *DatabaseController::getUserByCPF(QString cpf)
{
    User *user;
    QSqlQuery query("SELECT role, name, password FROM erprock_users WHERE cpf='"+cpf+"'");
    if (query.next()) {
        User::UserRole role = (User::UserRole) query.value(0).toString().toInt();
        QString name = query.value(1).toString();
        QString password = query.value(2).toString();

        user = new User(cpf, role, name, password);
    }

    return user;
}

QList<User*> *DatabaseController::getUsers()
{
    QList<User*> *users = new QList<User*>();
    QSqlQuery query("SELECT * FROM erprock_users ORDER BY name");
    while (query.next()) {
        QString cpf = query.value(0).toString();
        User::UserRole role = (User::UserRole) query.value(1).toString().toInt();
        QString name = query.value(2).toString();
        QString password = query.value(3).toString();

        User *user = new User(cpf, role, name, password);
        users->append(user);
    }

    return users;
}

QString DatabaseController::getUserRoleName(User::UserRole role)
{
    QString roleName;
    QSqlQuery query("SELECT role FROM erprock_user_roles WHERE id='"+QString::number(role)+"'");
    if (query.next()) {
        roleName = query.value(0).toString();
    }

    return roleName;
}

QStringList *DatabaseController::getUsersRoles()
{
    QStringList *roles = new QStringList();
    QSqlQuery query("SELECT role FROM erprock_user_roles");
    while (query.next()) {
        QString name = query.value(0).toString();
        roles->append(name);
    }

    return roles;
}

bool DatabaseController::validateLogin(QString cpf, QString password)
{
    bool ret = false;
    QSqlQuery query("SELECT password FROM erprock_users WHERE cpf='"+cpf+"'");
    if (query.next()) {
        if(password == query.value(0).toString())
        {
            ret = true;
        }
    }

    return ret;
}

bool DatabaseController::manufacturerAlreadyExists(QString cnpj)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_manufacturers WHERE cnpj='"+cnpj+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewManufacturer(Manufacturer *manufacturer)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_manufacturers (cnpj, state_number, name, fantasy_name, phone_number, fax_number, contact_name, email, address_street, address_number, address_complement, address_square, address_city, address_state, address_postal_code) VALUES(:cnpj, :state_number, :name, :fantasy_name, :phone_number, :fax_number, :contact_name, :email, :address_street, :address_number, :address_complement, :address_square, :address_city, :address_state, :address_postal_code)");
    insertQuery.bindValue(":cnpj", manufacturer->getCNPJ());
    insertQuery.bindValue(":state_number", manufacturer->getStateNumber());
    insertQuery.bindValue(":name", manufacturer->getName());
    insertQuery.bindValue(":fantasy_name", manufacturer->getFantasyName());
    insertQuery.bindValue(":phone_number", manufacturer->getPhoneNumber());
    insertQuery.bindValue(":fax_number", manufacturer->getFaxNumber());
    insertQuery.bindValue(":contact_name", manufacturer->getContactName());
    insertQuery.bindValue(":email", manufacturer->getEmail());
    insertQuery.bindValue(":address_street", manufacturer->getAddressStreet());
    insertQuery.bindValue(":address_number", manufacturer->getAddressNumber());
    insertQuery.bindValue(":address_complement", manufacturer->getAddressComplement());
    insertQuery.bindValue(":address_square", manufacturer->getAddressSquare());
    insertQuery.bindValue(":address_city", manufacturer->getAddressCity());
    insertQuery.bindValue(":address_state", manufacturer->getAddressState());
    insertQuery.bindValue(":address_postal_code", manufacturer->getAddressPostalCode());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateManufacturer(Manufacturer *manufacturer)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_manufacturers SET state_number=:state_number, name=:name, fantasy_name=:fantasy_name, phone_number=:phone_number, fax_number=:fax_number, contact_name=:contact_name, email=:email, address_street=:address_street, address_number=:address_number, address_complement=:address_complement, address_square=:address_square, address_city=:address_city, address_state=:address_state, address_postal_code=:address_postal_code WHERE cnpj=:cnpj");
    updateQuery.bindValue(":cnpj", manufacturer->getCNPJ());
    updateQuery.bindValue(":state_number", manufacturer->getStateNumber());
    updateQuery.bindValue(":name", manufacturer->getName());
    updateQuery.bindValue(":fantasy_name", manufacturer->getFantasyName());
    updateQuery.bindValue(":phone_number", manufacturer->getPhoneNumber());
    updateQuery.bindValue(":fax_number", manufacturer->getFaxNumber());
    updateQuery.bindValue(":contact_name", manufacturer->getContactName());
    updateQuery.bindValue(":email", manufacturer->getEmail());
    updateQuery.bindValue(":address_street", manufacturer->getAddressStreet());
    updateQuery.bindValue(":address_number", manufacturer->getAddressNumber());
    updateQuery.bindValue(":address_complement", manufacturer->getAddressComplement());
    updateQuery.bindValue(":address_square", manufacturer->getAddressSquare());
    updateQuery.bindValue(":address_city", manufacturer->getAddressCity());
    updateQuery.bindValue(":address_state", manufacturer->getAddressState());
    updateQuery.bindValue(":address_postal_code", manufacturer->getAddressPostalCode());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeManufacturer(QString cnpj)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_manufacturers WHERE cnpj=:cnpj");
    deleteQuery.bindValue(":cnpj", cnpj);

    ret = deleteQuery.exec();

    return ret;
}

Manufacturer *DatabaseController::getManufacturerByCNPJ(QString cnpj)
{
    Manufacturer *manufacturer;
    QSqlQuery query("SELECT state_number, name, fantasy_name, phone_number, fax_number, contact_name, email, address_street, address_number, address_complement, address_square, address_city, address_state, address_postal_code FROM erprock_manufacturers WHERE cnpj='"+cnpj+"'");
    if (query.next()) {
        QString stateNumber = query.value(0).toString();
        QString name = query.value(1).toString();
        QString fantasyName = query.value(2).toString();
        QString phoneNumber = query.value(3).toString();
        QString faxNumber = query.value(4).toString();
        QString contactName = query.value(5).toString();
        QString email = query.value(6).toString();
        QString addressStreet = query.value(7).toString();
        int addressNumber = query.value(8).toString().toInt();
        QString addressComplement = query.value(9).toString();
        QString adddressSquare = query.value(10).toString();
        QString addressCity = query.value(11).toString();
        QString addressState = query.value(12).toString();
        QString addressPostalCode = query.value(13).toString();

        manufacturer = new Manufacturer(cnpj, stateNumber, name, fantasyName, phoneNumber, faxNumber, contactName, email,
                                        addressStreet, addressNumber, addressComplement, adddressSquare, addressCity,
                                        addressState, addressPostalCode);
    }

    return manufacturer;
}

QList<Manufacturer*> *DatabaseController::getManufacturers()
{
    QList<Manufacturer*> *manufacturers = new QList<Manufacturer*>();
    QSqlQuery query("SELECT * FROM erprock_manufacturers ORDER BY name");
    while (query.next()) {
        QString cnpj = query.value(0).toString();
        QString stateNumber = query.value(1).toString();
        QString name = query.value(2).toString();
        QString fantasyName = query.value(3).toString();
        QString phoneNumber = query.value(4).toString();
        QString faxNumber = query.value(5).toString();
        QString contactName = query.value(6).toString();
        QString email = query.value(7).toString();
        QString addressStreet = query.value(8).toString();
        int addressNumber = query.value(9).toString().toInt();
        QString addressComplement = query.value(10).toString();
        QString adddressSquare = query.value(11).toString();
        QString addressCity = query.value(12).toString();
        QString addressState = query.value(13).toString();
        QString addressPostalCode = query.value(14).toString();

        Manufacturer *manufacturer = new Manufacturer(cnpj, stateNumber, name, fantasyName, phoneNumber, faxNumber, contactName, email,
                                                      addressStreet, addressNumber, addressComplement, adddressSquare, addressCity,
                                                      addressState, addressPostalCode);
        manufacturers->append(manufacturer);
    }

    return manufacturers;
}

bool DatabaseController::providerAlreadyExists(QString cnpj)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_providers WHERE cnpj='"+cnpj+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewProvider(Provider *provider)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_providers (cnpj, state_number, name, fantasy_name, phone_number, fax_number, contact_name, email, address_street, address_number, address_complement, address_square, address_city, address_state, address_postal_code) VALUES(:cnpj, :state_number, :name, :fantasy_name, :phone_number, :fax_number, :contact_name, :email, :address_street, :address_number, :address_complement, :address_square, :address_city, :address_state, :address_postal_code)");
    insertQuery.bindValue(":cnpj", provider->getCNPJ());
    insertQuery.bindValue(":state_number", provider->getStateNumber());
    insertQuery.bindValue(":name", provider->getName());
    insertQuery.bindValue(":fantasy_name", provider->getFantasyName());
    insertQuery.bindValue(":phone_number", provider->getPhoneNumber());
    insertQuery.bindValue(":fax_number", provider->getFaxNumber());
    insertQuery.bindValue(":contact_name", provider->getContactName());
    insertQuery.bindValue(":email", provider->getEmail());
    insertQuery.bindValue(":address_street", provider->getAddressStreet());
    insertQuery.bindValue(":address_number", provider->getAddressNumber());
    insertQuery.bindValue(":address_complement", provider->getAddressComplement());
    insertQuery.bindValue(":address_square", provider->getAddressSquare());
    insertQuery.bindValue(":address_city", provider->getAddressCity());
    insertQuery.bindValue(":address_state", provider->getAddressState());
    insertQuery.bindValue(":address_postal_code", provider->getAddressPostalCode());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateProvider(Provider *provider)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_providers SET state_number=:state_number, name=:name, fantasy_name=:fantasy_name, phone_number=:phone_number, fax_number=:fax_number, contact_name=:contact_name, email=:email, address_street=:address_street, address_number=:address_number, address_complement=:address_complement, address_square=:address_square, address_city=:address_city, address_state=:address_state, address_postal_code=:address_postal_code WHERE cnpj=:cnpj");
    updateQuery.bindValue(":cnpj", provider->getCNPJ());
    updateQuery.bindValue(":state_number", provider->getStateNumber());
    updateQuery.bindValue(":name", provider->getName());
    updateQuery.bindValue(":fantasy_name", provider->getFantasyName());
    updateQuery.bindValue(":phone_number", provider->getPhoneNumber());
    updateQuery.bindValue(":fax_number", provider->getFaxNumber());
    updateQuery.bindValue(":contact_name", provider->getContactName());
    updateQuery.bindValue(":email", provider->getEmail());
    updateQuery.bindValue(":address_street", provider->getAddressStreet());
    updateQuery.bindValue(":address_number", provider->getAddressNumber());
    updateQuery.bindValue(":address_complement", provider->getAddressComplement());
    updateQuery.bindValue(":address_square", provider->getAddressSquare());
    updateQuery.bindValue(":address_city", provider->getAddressCity());
    updateQuery.bindValue(":address_state", provider->getAddressState());
    updateQuery.bindValue(":address_postal_code", provider->getAddressPostalCode());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeProvider(QString cnpj)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_providers WHERE cnpj=:cnpj");
    deleteQuery.bindValue(":cnpj", cnpj);

    ret = deleteQuery.exec();

    return ret;
}

Provider *DatabaseController::getProviderByCNPJ(QString cnpj)
{
    Provider *provider;
    QSqlQuery query("SELECT state_number, name, fantasy_name, phone_number, fax_number, contact_name, email, address_street, address_number, address_complement, address_square, address_city, address_state, address_postal_code FROM erprock_providers WHERE cnpj='"+cnpj+"'");
    if (query.next()) {
        QString stateNumber = query.value(0).toString();
        QString name = query.value(1).toString();
        QString fantasyName = query.value(2).toString();
        QString phoneNumber = query.value(3).toString();
        QString faxNumber = query.value(4).toString();
        QString contactName = query.value(5).toString();
        QString email = query.value(6).toString();
        QString addressStreet = query.value(7).toString();
        int addressNumber = query.value(8).toString().toInt();
        QString addressComplement = query.value(9).toString();
        QString adddressSquare = query.value(10).toString();
        QString addressCity = query.value(11).toString();
        QString addressState = query.value(12).toString();
        QString addressPostalCode = query.value(13).toString();

        provider = new Provider(cnpj, stateNumber, name, fantasyName, phoneNumber, faxNumber, contactName, email,
                                addressStreet, addressNumber, addressComplement, adddressSquare, addressCity,
                                addressState, addressPostalCode);
    }

    return provider;
}

QList<Provider*> *DatabaseController::getProviders()
{
    QList<Provider*> *providers = new QList<Provider*>();
    QSqlQuery query("SELECT * FROM erprock_providers ORDER BY name");
    while (query.next()) {
        QString cnpj = query.value(0).toString();
        QString stateNumber = query.value(1).toString();
        QString name = query.value(2).toString();
        QString fantasyName = query.value(3).toString();
        QString phoneNumber = query.value(4).toString();
        QString faxNumber = query.value(5).toString();
        QString contactName = query.value(6).toString();
        QString email = query.value(7).toString();
        QString addressStreet = query.value(8).toString();
        int addressNumber = query.value(9).toString().toInt();
        QString addressComplement = query.value(10).toString();
        QString adddressSquare = query.value(11).toString();
        QString addressCity = query.value(12).toString();
        QString addressState = query.value(13).toString();
        QString addressPostalCode = query.value(14).toString();

        Provider *provider = new Provider(cnpj, stateNumber, name, fantasyName, phoneNumber, faxNumber, contactName, email,
                                          addressStreet, addressNumber, addressComplement, adddressSquare, addressCity,
                                          addressState, addressPostalCode);
        providers->append(provider);
    }

    return providers;
}

bool DatabaseController::productCategoryAlreadyExists(QString name)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_product_categories WHERE name='"+name+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewProductCategory(ProductCategory *productCategory)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_product_categories (name) VALUES(:name)");
    insertQuery.bindValue(":name", productCategory->getName());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateProductCategory(ProductCategory *productCategory)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_product_categories SET name=:name WHERE id=:id");
    updateQuery.bindValue(":id", productCategory->getId());
    updateQuery.bindValue(":name", productCategory->getName());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeProductCategory(int id)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_product_categories WHERE id=:id");
    deleteQuery.bindValue(":id", id);

    ret = deleteQuery.exec();

    return ret;
}

ProductCategory *DatabaseController::getProductCategoryById(int id)
{
    ProductCategory *productCategory;
    QSqlQuery query("SELECT name FROM erprock_product_categories WHERE id='"+QString::number(id)+"'");
    if (query.next()) {
        QString name = query.value(0).toString();
        productCategory = new ProductCategory(id, name);
    }

    return productCategory;
}

QList<ProductCategory*> *DatabaseController::getProductCategories()
{
    QList<ProductCategory*> *productCategories = new QList<ProductCategory*>();
    QSqlQuery query("SELECT * FROM erprock_product_categories ORDER BY name");
    while (query.next()) {
        int id = query.value(0).toString().toInt();
        QString name = query.value(1).toString();

        ProductCategory *productCategory = new ProductCategory(id, name);
        productCategories->append(productCategory);
    }

    return productCategories;
}

bool DatabaseController::productAlreadyExists(QString code)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_products WHERE code='"+code+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::barCodeAlreadyExists(QString barCode)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_products WHERE bar_code='"+barCode+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewProduct(Product *product)
{
    bool ret = false;

    QString cstIcmsCode = product->getCstIcms();
    QString cstIpiCode = product->getCstIpi();
    QString cstPisCode = product->getCstPis();
    QString cstCofinsCode = product->getCstCofins();

    QString icmsPercentName = product->getIcmsPercentName();
    QString ipiPercentName = product->getIcmsPercentName();
    QString pisPercentName = product->getIcmsPercentName();
    QString cofinsPercentName = product->getIcmsPercentName();

    QString cfopCode = product->getCfopCode();

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_products (code, bar_code, product_category_id, manufacturer_cnpj, name, description, cst_icms_code, cst_ipi_code, cst_pis_code, cst_cofins_code, icms_percent_name, ipi_percent_name, pis_percent_name, cofins_percent_name, cfop_code) VALUES(:code, :bar_code, :product_category_id, :manufacturer_cnpj, :name, :description, :cst_icms_code, :cst_ipi_code, :cst_pis_code, :cst_cofins_code, :icms_percent_name, :ipi_percent_name, :pis_percent_name, :cofins_percent_name, :cfop_code)");
    insertQuery.bindValue(":code", product->getCode());
    insertQuery.bindValue(":bar_code", product->getBarCode());
    insertQuery.bindValue(":product_category_id", product->getProductCategoryId());
    insertQuery.bindValue(":manufacturer_cnpj", product->getManufacturerCnpj());
    insertQuery.bindValue(":name", product->getName());
    insertQuery.bindValue(":description", product->getDescription());
    insertQuery.bindValue(":cst_icms_code", (cstIcmsCode.length() == 0) ? NULL : cstIcmsCode);
    insertQuery.bindValue(":cst_ipi_code", (cstIpiCode.length() == 0) ? NULL : cstIpiCode);
    insertQuery.bindValue(":cst_pis_code", (cstPisCode.length() == 0) ? NULL : cstPisCode);
    insertQuery.bindValue(":cst_cofins_code", (cstCofinsCode.length() == 0) ? NULL : cstCofinsCode);
    insertQuery.bindValue(":icms_percent_name", (icmsPercentName.length() == 0) ? NULL : icmsPercentName);
    insertQuery.bindValue(":ipi_percent_name", (ipiPercentName.length() == 0) ? NULL : ipiPercentName);
    insertQuery.bindValue(":pis_percent_name", (pisPercentName.length() == 0) ? NULL : pisPercentName);
    insertQuery.bindValue(":cofins_percent_name", (cofinsPercentName.length() == 0) ? NULL : cofinsPercentName);
    insertQuery.bindValue(":cfop_code", (cfopCode.length() == 0) ? NULL : cfopCode);

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateProduct(QString code, Product *product)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_products SET code=:code, bar_code=:bar_code, product_category_id=:product_category_id, manufacturer_cnpj=:manufacturer_cnpj, name=:name, description=:description, cst_icms_code=:cst_icms_code, cst_ipi_code=:cst_ipi_code, cst_pis_code=:cst_pis_code, cst_cofins_code=:cst_cofins_code, icms_percent_name=:icms_percent_name, ipi_percent_name=:ipi_percent_name, pis_percent_name=:pis_percent_name, cofins_percent_name=:cofins_percent_name, cfop_code=:cfop_code WHERE code=:current_code");
    updateQuery.bindValue(":current_code", code);
    updateQuery.bindValue(":code", product->getCode());
    updateQuery.bindValue(":bar_code", product->getBarCode());
    updateQuery.bindValue(":product_category_id", product->getProductCategoryId());
    updateQuery.bindValue(":manufacturer_cnpj", product->getManufacturerCnpj());
    updateQuery.bindValue(":name", product->getName());
    updateQuery.bindValue(":description", product->getDescription());
    updateQuery.bindValue(":cst_icms_code", product->getCstIcms());
    updateQuery.bindValue(":cst_ipi_code", product->getCstIpi());
    updateQuery.bindValue(":cst_pis_code", product->getCstPis());
    updateQuery.bindValue(":cst_cofins_code", product->getCstCofins());
    updateQuery.bindValue(":icms_percent_name", product->getIcmsPercentName());
    updateQuery.bindValue(":ipi_percent_name", product->getIpiPercentName());
    updateQuery.bindValue(":pis_percent_name", product->getPisPercentName());
    updateQuery.bindValue(":cofins_percent_name", product->getCofinsPercentName());
    updateQuery.bindValue(":cfop_code", product->getCfopCode());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeProduct(QString code)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_products WHERE code=:code");
    deleteQuery.bindValue(":code", code);

    ret = deleteQuery.exec();

    return ret;
}

Product *DatabaseController::getProductByCode(QString code)
{
    Product *product;
    QSqlQuery query("SELECT bar_code, product_category_id, manufacturer_cnpj, name, description, cst_icms_code, cst_ipi_code, cst_pis_code, cst_cofins_code, icms_percent_name, ipi_percent_name, pis_percent_name, cofins_percent_name, cfop_code FROM erprock_products WHERE code='"+code+"'");
    if (query.next()) {
        QString barCode = query.value(0).toString();
        int productCategoryId = query.value(1).toString().toInt();
        QString manufacturerCnpj = query.value(2).toString();
        QString name = query.value(3).toString();
        QString description = query.value(4).toString();
        QString cstIcmsCode = query.value(5).toString();
        QString cstIpiCode = query.value(6).toString();
        QString cstPisCode = query.value(7).toString();
        QString cstCofinsCode = query.value(8).toString();
        QString icmsPercentName = query.value(9).toString();
        QString ipiPercentName = query.value(10).toString();
        QString pisPercentName = query.value(11).toString();
        QString cofinsPercentName = query.value(12).toString();
        QString cfopCode = query.value(13).toString();

        product = new Product(code, barCode, productCategoryId, manufacturerCnpj, name, description,
                              cstIcmsCode, cstIpiCode, cstPisCode, cstCofinsCode, icmsPercentName,
                              ipiPercentName, pisPercentName, cofinsPercentName, cfopCode);
    }

    return product;
}

QList<Product*> *DatabaseController::getProducts()
{
    QList<Product*> *products = new QList<Product*>();
    QSqlQuery query("SELECT * FROM erprock_products ORDER BY name");
    while (query.next()) {
        QString code = query.value(0).toString();
        QString barCode = query.value(1).toString();
        int productCategoryId = query.value(2).toString().toInt();
        QString manufacturerCnpj = query.value(3).toString();
        QString name = query.value(4).toString();
        QString description = query.value(5).toString();
        QString cstIcmsCode = query.value(6).toString();
        QString cstIpiCode = query.value(7).toString();
        QString cstPisCode = query.value(8).toString();
        QString cstCofinsCode = query.value(9).toString();
        QString icmsPercentName = query.value(10).toString();
        QString ipiPercentName = query.value(11).toString();
        QString pisPercentName = query.value(12).toString();
        QString cofinsPercentName = query.value(13).toString();
        QString cfopCode = query.value(14).toString();

        Product *product = new Product(code, barCode, productCategoryId, manufacturerCnpj, name, description,
                                       cstIcmsCode, cstIpiCode, cstPisCode, cstCofinsCode, icmsPercentName,
                                       ipiPercentName, pisPercentName, cofinsPercentName, cfopCode);
        products->append(product);
    }

    return products;
}

int DatabaseController::getProductsQuantityByCode(QString code)
{
    int ret = -1;

    int purchases = 0;
    QSqlQuery queryPurchases("SELECT SUM(quantity) FROM erprock_purchase_product_orders WHERE product_code = '"+code+"'");
    if (queryPurchases.next()) {
        purchases = queryPurchases.value(0).toInt();
    }

    int sales = 0;
    QSqlQuery querySales("SELECT SUM(quantity) FROM erprock_sale_product_orders WHERE product_code = '"+code+"'");
    if (querySales.next()) {
        sales = querySales.value(0).toInt();
    }

    ret = purchases - sales;

    return ret;
}

bool DatabaseController::enterpriseCustomerAlreadyExists(QString cnpj)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_enterprise_customers WHERE cnpj='"+cnpj+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewEnterpriseCustomer(EnterpriseCustomer *enterpriseCustomer)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_enterprise_customers (cnpj, state_number, name, fantasy_name, phone_number, fax_number, contact_name, email, address_street, address_number, address_complement, address_square, address_city, address_state, address_postal_code) VALUES(:cnpj, :state_number, :name, :fantasy_name, :phone_number, :fax_number, :contact_name, :email, :address_street, :address_number, :address_complement, :address_square, :address_city, :address_state, :address_postal_code)");
    insertQuery.bindValue(":cnpj", enterpriseCustomer->getCnpj());
    insertQuery.bindValue(":state_number", enterpriseCustomer->getStateNumber());
    insertQuery.bindValue(":name", enterpriseCustomer->getName());
    insertQuery.bindValue(":fantasy_name", enterpriseCustomer->getFantasyName());
    insertQuery.bindValue(":phone_number", enterpriseCustomer->getPhoneNumber());
    insertQuery.bindValue(":fax_number", enterpriseCustomer->getFaxNumber());
    insertQuery.bindValue(":contact_name", enterpriseCustomer->getContactName());
    insertQuery.bindValue(":email", enterpriseCustomer->getEmail());
    insertQuery.bindValue(":address_street", enterpriseCustomer->getAddressStreet());
    insertQuery.bindValue(":address_number", enterpriseCustomer->getAddressNumber());
    insertQuery.bindValue(":address_complement", enterpriseCustomer->getAddressComplement());
    insertQuery.bindValue(":address_square", enterpriseCustomer->getAddressSquare());
    insertQuery.bindValue(":address_city", enterpriseCustomer->getAddressCity());
    insertQuery.bindValue(":address_state", enterpriseCustomer->getAddressState());
    insertQuery.bindValue(":address_postal_code", enterpriseCustomer->getAddressPostalCode());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateEnterpriseCustomer(EnterpriseCustomer *enterpriseCustomer)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_enterprise_customers SET state_number=:state_number, name=:name, fantasy_name=:fantasy_name, phone_number=:phone_number, fax_number=:fax_number, contact_name=:contact_name, email=:email, address_street=:address_street, address_number=:address_number, address_complement=:address_complement, address_square=:address_square, address_city=:address_city, address_state=:address_state, address_postal_code=:address_postal_code WHERE cnpj=:cnpj");
    updateQuery.bindValue(":cnpj", enterpriseCustomer->getCnpj());
    updateQuery.bindValue(":state_number", enterpriseCustomer->getStateNumber());
    updateQuery.bindValue(":name", enterpriseCustomer->getName());
    updateQuery.bindValue(":fantasy_name", enterpriseCustomer->getFantasyName());
    updateQuery.bindValue(":phone_number", enterpriseCustomer->getPhoneNumber());
    updateQuery.bindValue(":fax_number", enterpriseCustomer->getFaxNumber());
    updateQuery.bindValue(":contact_name", enterpriseCustomer->getContactName());
    updateQuery.bindValue(":email", enterpriseCustomer->getEmail());
    updateQuery.bindValue(":address_street", enterpriseCustomer->getAddressStreet());
    updateQuery.bindValue(":address_number", enterpriseCustomer->getAddressNumber());
    updateQuery.bindValue(":address_complement", enterpriseCustomer->getAddressComplement());
    updateQuery.bindValue(":address_square", enterpriseCustomer->getAddressSquare());
    updateQuery.bindValue(":address_city", enterpriseCustomer->getAddressCity());
    updateQuery.bindValue(":address_state", enterpriseCustomer->getAddressState());
    updateQuery.bindValue(":address_postal_code", enterpriseCustomer->getAddressPostalCode());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeEnterpriseCustomer(QString cnpj)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_enterprise_customers WHERE cnpj=:cnpj");
    deleteQuery.bindValue(":cnpj", cnpj);

    ret = deleteQuery.exec();

    return ret;
}

EnterpriseCustomer *DatabaseController::getEnterpriseCustomerByCNPJ(QString cnpj)
{
    EnterpriseCustomer *enterpriseCustomer;
    QSqlQuery query("SELECT state_number, name, fantasy_name, phone_number, fax_number, contact_name, email, address_street, address_number, address_complement, address_square, address_city, address_state, address_postal_code FROM erprock_enterprise_customers WHERE cnpj='"+cnpj+"'");
    if (query.next()) {
        QString stateNumber = query.value(0).toString();
        QString name = query.value(1).toString();
        QString fantasyName = query.value(2).toString();
        QString phoneNumber = query.value(3).toString();
        QString faxNumber = query.value(4).toString();
        QString contactName = query.value(5).toString();
        QString email = query.value(6).toString();
        QString addressStreet = query.value(7).toString();
        int addressNumber = query.value(8).toString().toInt();
        QString addressComplement = query.value(9).toString();
        QString adddressSquare = query.value(10).toString();
        QString addressCity = query.value(11).toString();
        QString addressState = query.value(12).toString();
        QString addressPostalCode = query.value(13).toString();

        enterpriseCustomer = new EnterpriseCustomer(cnpj, stateNumber, name, fantasyName, phoneNumber, faxNumber,
                                                    contactName, email, addressStreet, addressNumber, addressComplement,
                                                    adddressSquare, addressCity, addressState, addressPostalCode);
    }

    return enterpriseCustomer;
}

QList<EnterpriseCustomer*> *DatabaseController::getEnterpriseCustomers()
{
    QList<EnterpriseCustomer*> *enterpriseCustomers = new QList<EnterpriseCustomer*>();
    QSqlQuery query("SELECT * FROM erprock_enterprise_customers ORDER BY name");
    while (query.next()) {
        QString cnpj = query.value(0).toString();
        QString stateNumber = query.value(1).toString();
        QString name = query.value(2).toString();
        QString fantasyName = query.value(3).toString();
        QString phoneNumber = query.value(4).toString();
        QString faxNumber = query.value(5).toString();
        QString contactName = query.value(6).toString();
        QString email = query.value(7).toString();
        QString addressStreet = query.value(8).toString();
        int addressNumber = query.value(9).toString().toInt();
        QString addressComplement = query.value(10).toString();
        QString adddressSquare = query.value(11).toString();
        QString addressCity = query.value(12).toString();
        QString addressState = query.value(13).toString();
        QString addressPostalCode = query.value(14).toString();

        EnterpriseCustomer *enterpriseCustomer = new EnterpriseCustomer(cnpj, stateNumber, name, fantasyName, phoneNumber,
                                                                        faxNumber, contactName, email, addressStreet,
                                                                        addressNumber, addressComplement, adddressSquare,
                                                                        addressCity, addressState, addressPostalCode);
        enterpriseCustomers->append(enterpriseCustomer);
    }

    return enterpriseCustomers;
}

bool DatabaseController::physicalCustomerAlreadyExists(QString cpf)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_physical_customers WHERE cpf='"+cpf+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewPhysicalCustomer(PhysicalCustomer *physicalCustomer)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_physical_customers (cpf, name, birth_date, phone_number, email, address_street, address_number, address_complement, address_square, address_city, address_state, address_postal_code) VALUES(:cpf, :name, :birth_date, :phone_number, :email, :address_street, :address_number, :address_complement, :address_square, :address_city, :address_state, :address_postal_code)");
    insertQuery.bindValue(":cpf", physicalCustomer->getCpf());
    insertQuery.bindValue(":name", physicalCustomer->getName());
    insertQuery.bindValue(":birth_date", physicalCustomer->getBirthDate());
    insertQuery.bindValue(":phone_number", physicalCustomer->getPhoneNumber());
    insertQuery.bindValue(":email", physicalCustomer->getEmail());
    insertQuery.bindValue(":address_street", physicalCustomer->getAddressStreet());
    insertQuery.bindValue(":address_number", physicalCustomer->getAddressNumber());
    insertQuery.bindValue(":address_complement", physicalCustomer->getAddressComplement());
    insertQuery.bindValue(":address_square", physicalCustomer->getAddressSquare());
    insertQuery.bindValue(":address_city", physicalCustomer->getAddressCity());
    insertQuery.bindValue(":address_state", physicalCustomer->getAddressState());
    insertQuery.bindValue(":address_postal_code", physicalCustomer->getAddressPostalCode());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updatePhysicalCustomer(PhysicalCustomer *physicalCustomer)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_physical_customers SET name=:name, birth_date=:birth_date, phone_number=:phone_number, email=:email, address_street=:address_street, address_number=:address_number, address_complement=:address_complement, address_square=:address_square, address_city=:address_city, address_state=:address_state, address_postal_code=:address_postal_code WHERE cpf=:cpf");
    updateQuery.bindValue(":cpf", physicalCustomer->getCpf());
    updateQuery.bindValue(":name", physicalCustomer->getName());
    updateQuery.bindValue(":birth_date", physicalCustomer->getBirthDate());
    updateQuery.bindValue(":phone_number", physicalCustomer->getPhoneNumber());
    updateQuery.bindValue(":email", physicalCustomer->getEmail());
    updateQuery.bindValue(":address_street", physicalCustomer->getAddressStreet());
    updateQuery.bindValue(":address_number", physicalCustomer->getAddressNumber());
    updateQuery.bindValue(":address_complement", physicalCustomer->getAddressComplement());
    updateQuery.bindValue(":address_square", physicalCustomer->getAddressSquare());
    updateQuery.bindValue(":address_city", physicalCustomer->getAddressCity());
    updateQuery.bindValue(":address_state", physicalCustomer->getAddressState());
    updateQuery.bindValue(":address_postal_code", physicalCustomer->getAddressPostalCode());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removePhysicalCustomer(QString cpf)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_physical_customers WHERE cpf=:cpf");
    deleteQuery.bindValue(":cpf", cpf);

    ret = deleteQuery.exec();

    return ret;
}

PhysicalCustomer *DatabaseController::getPhysicalCustomerByCPF(QString cpf)
{
    PhysicalCustomer *physicalCustomer;
    QSqlQuery query("SELECT name, birth_date, phone_number, email, address_street, address_number, address_complement, address_square, address_city, address_state, address_postal_code FROM erprock_physical_customers WHERE cpf='"+cpf+"'");
    if (query.next()) {
        QString name = query.value(0).toString();

        //====== Date =======
        QString dateTimeStr = query.value(1).toString();
        QStringList dateTime = dateTimeStr.split("T");
        QString dateStr = dateTime.at(0);
        QStringList pieces = dateStr.split("-");
        dateStr = pieces.at(2) + "/" + pieces.at(1) + "/" + pieces.at(0);
        QDateTime birthDate = QDateTime::fromString(dateStr, PhysicalCustomer::DATE_FORMAT);

        QString phoneNumber = query.value(2).toString();
        QString email = query.value(3).toString();
        QString addressStreet = query.value(4).toString();
        int addressNumber = query.value(5).toString().toInt();
        QString addressComplement = query.value(6).toString();
        QString adddressSquare = query.value(7).toString();
        QString addressCity = query.value(8).toString();
        QString addressState = query.value(9).toString();
        QString addressPostalCode = query.value(10).toString();

        physicalCustomer = new PhysicalCustomer(cpf, name, birthDate, phoneNumber, email, addressStreet,
                                                addressNumber, addressComplement,adddressSquare, addressCity,
                                                addressState, addressPostalCode);
    }

    return physicalCustomer;
}

QList<PhysicalCustomer*> *DatabaseController::getPhysicalCustomers()
{
    QList<PhysicalCustomer*> *physicalCustomers = new QList<PhysicalCustomer*>();
    QSqlQuery query("SELECT * FROM erprock_physical_customers ORDER BY name");
    while (query.next()) {
        QString cpf = query.value(0).toString();
        QString name = query.value(1).toString();

        //====== Date =======
        QString dateTimeStr = query.value(2).toString();
        QStringList dateTime = dateTimeStr.split("T");
        QString dateStr = dateTime.at(0);
        QStringList pieces = dateStr.split("-");
        dateStr = pieces.at(2) + "/" + pieces.at(1) + "/" + pieces.at(0);
        QDateTime birthDate = QDateTime::fromString(dateStr, PhysicalCustomer::DATE_FORMAT);

        QString phoneNumber = query.value(3).toString();
        QString email = query.value(4).toString();
        QString addressStreet = query.value(5).toString();
        int addressNumber = query.value(6).toString().toInt();
        QString addressComplement = query.value(7).toString();
        QString adddressSquare = query.value(8).toString();
        QString addressCity = query.value(9).toString();
        QString addressState = query.value(10).toString();
        QString addressPostalCode = query.value(11).toString();

        PhysicalCustomer *physicalCustomer = new PhysicalCustomer(cpf, name, birthDate, phoneNumber, email, addressStreet,
                                                                  addressNumber, addressComplement, adddressSquare,
                                                                  addressCity, addressState, addressPostalCode);
        physicalCustomers->append(physicalCustomer);
    }

    return physicalCustomers;
}

bool DatabaseController::stockUnitAlreadyExists(QString name)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_stock_units WHERE name='"+name+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewStockUnit(StockUnit *stockUnit)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_stock_units (name) VALUES(:name)");
    insertQuery.bindValue(":name", stockUnit->getName());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateStockUnit(StockUnit *stockUnit)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_stock_units SET name=:name WHERE id=:id");
    updateQuery.bindValue(":id", stockUnit->getId());
    updateQuery.bindValue(":name", stockUnit->getName());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeStockUnit(int id)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_stock_units WHERE id=:id");
    deleteQuery.bindValue(":id", id);

    ret = deleteQuery.exec();

    return ret;
}

StockUnit *DatabaseController::getStockUnitById(int id)
{
    StockUnit *stockUnit;
    QSqlQuery query("SELECT name FROM erprock_stock_units WHERE id='"+QString::number(id)+"'");
    if (query.next()) {
        QString name = query.value(0).toString();
        stockUnit = new StockUnit(id, name);
    }

    return stockUnit;
}

QList<StockUnit*> *DatabaseController::getStockUnits()
{
    QList<StockUnit*> *stockUnits = new QList<StockUnit*>();
    QSqlQuery query("SELECT * FROM erprock_stock_units ORDER BY name");
    while (query.next()) {
        int id = query.value(0).toString().toInt();
        QString name = query.value(1).toString();

        StockUnit *stockUnit = new StockUnit(id, name);
        stockUnits->append(stockUnit);
    }

    return stockUnits;
}

bool DatabaseController::productOriginAlreadyExists(QString code)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_product_origins WHERE code='"+code+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewProductOrigin(ProductOrigin *productOrigin)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_product_origins (code, name) VALUES(:code, :name)");
    insertQuery.bindValue(":code", productOrigin->getCode());
    insertQuery.bindValue(":name", productOrigin->getName());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateProductOrigin(QString code, ProductOrigin *productOrigin)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_product_origins SET code=:code, name=:name WHERE code=:current_code");
    updateQuery.bindValue(":current_code", code);
    updateQuery.bindValue(":code", productOrigin->getCode());
    updateQuery.bindValue(":name", productOrigin->getName());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeProductOrigin(QString code)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_product_origins WHERE code=:code");
    deleteQuery.bindValue(":code", code);

    ret = deleteQuery.exec();

    return ret;
}

ProductOrigin *DatabaseController::getProductOriginByCode(QString code)
{
    ProductOrigin *productOrigin;
    QSqlQuery query("SELECT name FROM erprock_product_origins WHERE code='"+code+"'");
    if (query.next()) {
        QString name = query.value(0).toString();
        productOrigin = new ProductOrigin(code, name);
    }

    return productOrigin;
}

QList<ProductOrigin*> *DatabaseController::getProductOrigins()
{
    QList<ProductOrigin*> *productOrigins = new QList<ProductOrigin*>();
    QSqlQuery query("SELECT * FROM erprock_product_origins ORDER BY code");
    while (query.next()) {
        QString code = query.value(0).toString();
        QString name = query.value(1).toString();

        ProductOrigin *productOrigin = new ProductOrigin(code, name);
        productOrigins->append(productOrigin);
    }

    return productOrigins;
}

bool DatabaseController::cstIcmsAlreadyExists(QString code)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_cst_icms WHERE code='"+code+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewCstIcms(CstIcms *cstIcms)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_cst_icms (code, name) VALUES(:code, :name)");
    insertQuery.bindValue(":code", cstIcms->getCode());
    insertQuery.bindValue(":name", cstIcms->getName());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateCstIcms(QString code, CstIcms *cstIcms)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_cst_icms SET code=:code, name=:name WHERE code=:current_code");
    updateQuery.bindValue(":current_code", code);
    updateQuery.bindValue(":code", cstIcms->getCode());
    updateQuery.bindValue(":name", cstIcms->getName());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeCstIcms(QString code)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_cst_icms WHERE code=:code");
    deleteQuery.bindValue(":code", code);

    ret = deleteQuery.exec();

    return ret;
}

CstIcms *DatabaseController::getCstIcmsByCode(QString code)
{
    CstIcms *cstIcms;
    QSqlQuery query("SELECT name FROM erprock_cst_icms WHERE code='"+code+"'");
    if (query.next()) {
        QString name = query.value(0).toString();
        cstIcms = new CstIcms(code, name);
    }

    return cstIcms;
}

QList<CstIcms*> *DatabaseController::getCstIcmss()
{
    QList<CstIcms*> *cstIcmss = new QList<CstIcms*>();
    QSqlQuery query("SELECT * FROM erprock_cst_icms ORDER BY code");
    while (query.next()) {
        QString code = query.value(0).toString();
        QString name = query.value(1).toString();

        CstIcms *cstIcms = new CstIcms(code, name);
        cstIcmss->append(cstIcms);
    }

    return cstIcmss;
}

bool DatabaseController::cstIpiAlreadyExists(QString code)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_cst_ipi WHERE code='"+code+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewCstIpi(CstIpi *cstIpi)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_cst_ipi (code, name) VALUES(:code, :name)");
    insertQuery.bindValue(":code", cstIpi->getCode());
    insertQuery.bindValue(":name", cstIpi->getName());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateCstIpi(QString code, CstIpi *cstIpi)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_cst_ipi SET code=:code, name=:name WHERE code=:current_code");
    updateQuery.bindValue(":current_code", code);
    updateQuery.bindValue(":code", cstIpi->getCode());
    updateQuery.bindValue(":name", cstIpi->getName());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeCstIpi(QString code)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_cst_ipi WHERE code=:code");
    deleteQuery.bindValue(":code", code);

    ret = deleteQuery.exec();

    return ret;
}

CstIpi *DatabaseController::getCstIpiByCode(QString code)
{
    CstIpi *cstIpi;
    QSqlQuery query("SELECT name FROM erprock_cst_ipi WHERE code='"+code+"'");
    if (query.next()) {
        QString name = query.value(0).toString();
        cstIpi = new CstIpi(code, name);
    }

    return cstIpi;
}

QList<CstIpi*> *DatabaseController::getCstIpis()
{
    QList<CstIpi*> *cstIpis = new QList<CstIpi*>();
    QSqlQuery query("SELECT * FROM erprock_cst_ipi ORDER BY code");
    while (query.next()) {
        QString code = query.value(0).toString();
        QString name = query.value(1).toString();

        CstIpi *cstIpi = new CstIpi(code, name);
        cstIpis->append(cstIpi);
    }

    return cstIpis;
}

bool DatabaseController::cstPisAlreadyExists(QString code)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_cst_pis WHERE code='"+code+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewCstPis(CstPis *cstPis)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_cst_pis (code, name) VALUES(:code, :name)");
    insertQuery.bindValue(":code", cstPis->getCode());
    insertQuery.bindValue(":name", cstPis->getName());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateCstPis(QString code, CstPis *cstPis)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_cst_pis SET code=:code, name=:name WHERE code=:current_code");
    updateQuery.bindValue(":current_code", code);
    updateQuery.bindValue(":code", cstPis->getCode());
    updateQuery.bindValue(":name", cstPis->getName());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeCstPis(QString code)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_cst_pis WHERE code=:code");
    deleteQuery.bindValue(":code", code);

    ret = deleteQuery.exec();

    return ret;
}

CstPis *DatabaseController::getCstPisByCode(QString code)
{
    CstPis *cstPis;
    QSqlQuery query("SELECT name FROM erprock_cst_pis WHERE code='"+code+"'");
    if (query.next()) {
        QString name = query.value(0).toString();
        cstPis = new CstPis(code, name);
    }

    return cstPis;
}

QList<CstPis*> *DatabaseController::getCstPiss()
{
    QList<CstPis*> *cstPiss = new QList<CstPis*>();
    QSqlQuery query("SELECT * FROM erprock_cst_pis ORDER BY code");
    while (query.next()) {
        QString code = query.value(0).toString();
        QString name = query.value(1).toString();

        CstPis *cstPis = new CstPis(code, name);
        cstPiss->append(cstPis);
    }

    return cstPiss;
}

bool DatabaseController::cstCofinsAlreadyExists(QString code)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_cst_cofins WHERE code='"+code+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewCstCofins(CstCofins *cstCofins)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_cst_cofins (code, name) VALUES(:code, :name)");
    insertQuery.bindValue(":code", cstCofins->getCode());
    insertQuery.bindValue(":name", cstCofins->getName());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateCstCofins(QString code, CstCofins *cstCofins)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_cst_cofins SET code=:code, name=:name WHERE code=:current_code");
    updateQuery.bindValue(":current_code", code);
    updateQuery.bindValue(":code", cstCofins->getCode());
    updateQuery.bindValue(":name", cstCofins->getName());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeCstCofins(QString code)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_cst_cofins WHERE code=:code");
    deleteQuery.bindValue(":code", code);

    ret = deleteQuery.exec();

    return ret;
}

CstCofins *DatabaseController::getCstCofinsByCode(QString code)
{
    CstCofins *cstCofins;
    QSqlQuery query("SELECT name FROM erprock_cst_cofins WHERE code='"+code+"'");
    if (query.next()) {
        QString name = query.value(0).toString();
        cstCofins = new CstCofins(code, name);
    }

    return cstCofins;
}

QList<CstCofins*> *DatabaseController::getCstCofinss()
{
    QList<CstCofins*> *cstCofinss = new QList<CstCofins*>();
    QSqlQuery query("SELECT * FROM erprock_cst_cofins ORDER BY code");
    while (query.next()) {
        QString code = query.value(0).toString();
        QString name = query.value(1).toString();

        CstCofins *cstCofins = new CstCofins(code, name);
        cstCofinss->append(cstCofins);
    }

    return cstCofinss;
}

bool DatabaseController::taxRateAlreadyExists(QString name)
{
    bool ret = false;
    QSqlQuery query("SELECT value FROM erprock_tax_rates WHERE name='"+name+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewTaxRate(TaxRate *taxRate)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_tax_rates (name, value) VALUES(:name, :value)");
    insertQuery.bindValue(":name", taxRate->getName());
    insertQuery.bindValue(":value", taxRate->getValue());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateTaxRate(QString name, TaxRate *taxRate)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_tax_rates SET name=:name, value=:value WHERE name=:current_name");
    updateQuery.bindValue(":current_name", name);
    updateQuery.bindValue(":name", taxRate->getName());
    updateQuery.bindValue(":value", taxRate->getValue());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeTaxRate(QString name)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_tax_rates WHERE name=:name");
    deleteQuery.bindValue(":name", name);

    ret = deleteQuery.exec();

    return ret;
}

TaxRate *DatabaseController::getTaxRateByName(QString name)
{
    TaxRate *taxRate;
    QSqlQuery query("SELECT value FROM erprock_tax_rates WHERE name='"+name+"'");
    if (query.next()) {
        double value = query.value(0).toString().toDouble();
        taxRate = new TaxRate(name, value);
    }

    return taxRate;
}

QList<TaxRate*> *DatabaseController::getTaxRates()
{
    QList<TaxRate*> *taxRates = new QList<TaxRate*>();
    QSqlQuery query("SELECT * FROM erprock_tax_rates ORDER BY name");
    while (query.next()) {
        QString name = query.value(0).toString();
        double value = query.value(1).toString().toDouble();

        TaxRate *taxRate = new TaxRate(name, value);
        taxRates->append(taxRate);
    }

    return taxRates;
}

bool DatabaseController::cfopAlreadyExists(QString cfop)
{
    bool ret = false;
    QSqlQuery query("SELECT cfop FROM erprock_cfop WHERE cfop='"+cfop+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewCfop(Cfop *cfopObj)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_cfop (cfop, description, application) VALUES(:cfop, :description, :application)");
    insertQuery.bindValue(":cfop", cfopObj->getCfop());
    insertQuery.bindValue(":description", cfopObj->getDescription());
    insertQuery.bindValue(":application", cfopObj->getApplication());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateCfop(QString cfop, Cfop *cfopObj)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_cfop SET cfop=:cfop, description=:description, application=:application WHERE cfop=:current_cfop");
    updateQuery.bindValue(":current_cfop", cfop);
    updateQuery.bindValue(":cfop", cfopObj->getCfop());
    updateQuery.bindValue(":description", cfopObj->getDescription());
    updateQuery.bindValue(":application", cfopObj->getApplication());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeCfop(QString cfop)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_cfop WHERE cfop=:cfop");
    deleteQuery.bindValue(":cfop", cfop);

    ret = deleteQuery.exec();

    return ret;
}

Cfop *DatabaseController::getCfopByCfop(QString cfop)
{
    Cfop *cfopObj;
    QSqlQuery query("SELECT description, application FROM erprock_cfop WHERE cfop='"+cfop+"'");
    if (query.next()) {
        QString description = query.value(0).toString();
        QString application = query.value(1).toString();
        cfopObj = new Cfop(cfop, description, application);
    }

    return cfopObj;
}

QList<Cfop*> *DatabaseController::getCfops()
{
    QList<Cfop*> *cfops = new QList<Cfop*>();
    QSqlQuery query("SELECT * FROM erprock_cfop ORDER BY cfop");
    while (query.next()) {
        QString cfop = query.value(0).toString();
        QString description = query.value(1).toString();
        QString application = query.value(2).toString();

        Cfop *cfopObj = new Cfop(cfop, description, application);
        cfops->append(cfopObj);
    }

    return cfops;
}

bool DatabaseController::priceAlreadyExists(int id, QString productCode, QString storeCnpj)
{
    bool ret = false;
    QSqlQuery query("SELECT value FROM erprock_prices WHERE id<>'"+QString::number(id)+"' AND product_code='"+productCode+"' AND store_cnpj='"+storeCnpj+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::priceNameAlreadyExists(int id, QString name)
{
    bool ret = false;
    QSqlQuery query("SELECT value FROM erprock_prices WHERE id<>'"+QString::number(id)+"'AND name='"+name+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewPrice(Price *price)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_prices (product_code, value, store_cnpj, name) VALUES(:product_code, :value, :store_cnpj, :name)");
    insertQuery.bindValue(":product_code", price->getProductCode());
    insertQuery.bindValue(":value", price->getValue());
    insertQuery.bindValue(":store_cnpj", price->getStoreCnpj());
    insertQuery.bindValue(":name", price->getName());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updatePrice(Price *price)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_prices SET product_code=:product_code, value=:value, store_cnpj=:store_cnpj, name=:name WHERE id=:id");
    updateQuery.bindValue(":id", price->getId());
    updateQuery.bindValue(":product_code", price->getProductCode());
    updateQuery.bindValue(":value", price->getValue());
    updateQuery.bindValue(":store_cnpj", price->getStoreCnpj());
    updateQuery.bindValue(":name", price->getName());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removePrice(int id)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_prices WHERE id=:id");
    deleteQuery.bindValue(":id", id);

    ret = deleteQuery.exec();

    return ret;
}

Price *DatabaseController::getPriceById(int id)
{
    Price *price;
    QSqlQuery query("SELECT product_code, value, store_cnpj, name FROM erprock_prices WHERE id='"+QString::number(id)+"'");
    if (query.next()) {
        QString productCode = query.value(0).toString();
        double value = query.value(1).toDouble();
        QString storeCnpj = query.value(2).toString();
        QString name = query.value(3).toString();
        price = new Price(id, productCode, value, storeCnpj, name);
    }

    return price;
}

Price *DatabaseController::getPriceByName(QString name)
{
    Price *price;
    QSqlQuery query("SELECT id, product_code, value, store_cnpj FROM erprock_prices WHERE name='"+name+"'");
    if (query.next()) {
        int id = query.value(0).toInt();
        QString productCode = query.value(1).toString();
        double value = query.value(2).toDouble();
        QString storeCnpj = query.value(3).toString();
        price = new Price(id, productCode, value, storeCnpj, name);
    }

    return price;
}

Price *DatabaseController::getPriceByProductCodeAndStoreCnpj(QString productCode, QString storeCnpj)
{
    Price *price = NULL;
    QSqlQuery query("SELECT id, value, name FROM erprock_prices WHERE product_code='"+productCode+"' AND store_cnpj='"+storeCnpj+"'");
    if (query.next()) {
        int id = query.value(0).toInt();
        double value = query.value(1).toDouble();
        QString name = query.value(2).toString();
        price = new Price(id, productCode, value, storeCnpj, name);
    }

    return price;
}

QList<Price*> *DatabaseController::getPrices()
{
    QList<Price*> *prices = new QList<Price*>();
    QSqlQuery query("SELECT * FROM erprock_prices ORDER BY name");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString productCode = query.value(1).toString();
        double value = query.value(2).toDouble();
        QString storeCnpj = query.value(3).toString();
        QString name = query.value(4).toString();

        Price *price = new Price(id, productCode, value, storeCnpj, name);
        prices->append(price);
    }

    return prices;
}

bool DatabaseController::storeAlreadyExists(QString cnpj)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_stores WHERE cnpj='"+cnpj+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewStore(Store *store)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_stores (cnpj, state_number, name, fantasy_name, phone_number, fax_number, contact_name, email, address_street, address_number, address_complement, address_square, address_city, address_state, address_postal_code) VALUES(:cnpj, :state_number, :name, :fantasy_name, :phone_number, :fax_number, :contact_name, :email, :address_street, :address_number, :address_complement, :address_square, :address_city, :address_state, :address_postal_code)");
    insertQuery.bindValue(":cnpj", store->getCNPJ());
    insertQuery.bindValue(":state_number", store->getStateNumber());
    insertQuery.bindValue(":name", store->getName());
    insertQuery.bindValue(":fantasy_name", store->getFantasyName());
    insertQuery.bindValue(":phone_number", store->getPhoneNumber());
    insertQuery.bindValue(":fax_number", store->getFaxNumber());
    insertQuery.bindValue(":contact_name", store->getContactName());
    insertQuery.bindValue(":email", store->getEmail());
    insertQuery.bindValue(":address_street", store->getAddressStreet());
    insertQuery.bindValue(":address_number", store->getAddressNumber());
    insertQuery.bindValue(":address_complement", store->getAddressComplement());
    insertQuery.bindValue(":address_square", store->getAddressSquare());
    insertQuery.bindValue(":address_city", store->getAddressCity());
    insertQuery.bindValue(":address_state", store->getAddressState());
    insertQuery.bindValue(":address_postal_code", store->getAddressPostalCode());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateStore(Store *store)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_stores SET state_number=:state_number, name=:name, fantasy_name=:fantasy_name, phone_number=:phone_number, fax_number=:fax_number, contact_name=:contact_name, email=:email, address_street=:address_street, address_number=:address_number, address_complement=:address_complement, address_square=:address_square, address_city=:address_city, address_state=:address_state, address_postal_code=:address_postal_code WHERE cnpj=:cnpj");
    updateQuery.bindValue(":cnpj", store->getCNPJ());
    updateQuery.bindValue(":state_number", store->getStateNumber());
    updateQuery.bindValue(":name", store->getName());
    updateQuery.bindValue(":fantasy_name", store->getFantasyName());
    updateQuery.bindValue(":phone_number", store->getPhoneNumber());
    updateQuery.bindValue(":fax_number", store->getFaxNumber());
    updateQuery.bindValue(":contact_name", store->getContactName());
    updateQuery.bindValue(":email", store->getEmail());
    updateQuery.bindValue(":address_street", store->getAddressStreet());
    updateQuery.bindValue(":address_number", store->getAddressNumber());
    updateQuery.bindValue(":address_complement", store->getAddressComplement());
    updateQuery.bindValue(":address_square", store->getAddressSquare());
    updateQuery.bindValue(":address_city", store->getAddressCity());
    updateQuery.bindValue(":address_state", store->getAddressState());
    updateQuery.bindValue(":address_postal_code", store->getAddressPostalCode());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeStore(QString cnpj)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_stores WHERE cnpj=:cnpj");
    deleteQuery.bindValue(":cnpj", cnpj);

    ret = deleteQuery.exec();

    return ret;
}

Store *DatabaseController::getStoreByCNPJ(QString cnpj)
{
    Store *store;
    QSqlQuery query("SELECT state_number, name, fantasy_name, phone_number, fax_number, contact_name, email, address_street, address_number, address_complement, address_square, address_city, address_state, address_postal_code FROM erprock_stores WHERE cnpj='"+cnpj+"'");
    if (query.next()) {
        QString stateNumber = query.value(0).toString();
        QString name = query.value(1).toString();
        QString fantasyName = query.value(2).toString();
        QString phoneNumber = query.value(3).toString();
        QString faxNumber = query.value(4).toString();
        QString contactName = query.value(5).toString();
        QString email = query.value(6).toString();
        QString addressStreet = query.value(7).toString();
        int addressNumber = query.value(8).toString().toInt();
        QString addressComplement = query.value(9).toString();
        QString adddressSquare = query.value(10).toString();
        QString addressCity = query.value(11).toString();
        QString addressState = query.value(12).toString();
        QString addressPostalCode = query.value(13).toString();

        store = new Store(cnpj, stateNumber, name, fantasyName, phoneNumber, faxNumber, contactName, email,
                          addressStreet, addressNumber, addressComplement, adddressSquare, addressCity,
                          addressState, addressPostalCode);
    }

    return store;
}

QList<Store*> *DatabaseController::getStores()
{
    QList<Store*> *stores = new QList<Store*>();
    QSqlQuery query("SELECT * FROM erprock_stores ORDER BY name");
    while (query.next()) {
        QString cnpj = query.value(0).toString();
        QString stateNumber = query.value(1).toString();
        QString name = query.value(2).toString();
        QString fantasyName = query.value(3).toString();
        QString phoneNumber = query.value(4).toString();
        QString faxNumber = query.value(5).toString();
        QString contactName = query.value(6).toString();
        QString email = query.value(7).toString();
        QString addressStreet = query.value(8).toString();
        int addressNumber = query.value(9).toString().toInt();
        QString addressComplement = query.value(10).toString();
        QString adddressSquare = query.value(11).toString();
        QString addressCity = query.value(12).toString();
        QString addressState = query.value(13).toString();
        QString addressPostalCode = query.value(14).toString();

        Store *store = new Store(cnpj, stateNumber, name, fantasyName, phoneNumber, faxNumber, contactName, email,
                                 addressStreet, addressNumber, addressComplement, adddressSquare, addressCity,
                                 addressState, addressPostalCode);
        stores->append(store);
    }

    return stores;
}

bool DatabaseController::salesOrderAlreadyExists(QString receipt)
{
    bool ret = false;
    QSqlQuery query("SELECT id FROM erprock_sale_orders WHERE receipt='"+receipt+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::storeSalesOrder(SalesOrder *salesOrder)
{
    bool ret = false;

    QList<SaleProductOrder*> *saleProductOrders = salesOrder->getSaleProductOrders();
    QDateTime date = salesOrder->getDate();
    QString receipt = salesOrder->getReceipt();
    int paymentCondition = salesOrder->getPaymentCondition();
    Utilities::PaymentForm paymentForm = salesOrder->getPaymentForm();
    double discount = salesOrder->getDiscount();
    QString observation = salesOrder->getObservation();
    double valuePaid = salesOrder->getValuePaid();
    QString customerId = salesOrder->getCustomerId();

    QString queryStr = "SELECT store_sales_order(\n";
    queryStr += "CAST ('"+receipt+"' AS  character varying),\n";
    queryStr += "CAST ("+QString::number(paymentCondition)+" AS smallint),\n";
    queryStr += "CAST ("+QString::number(paymentForm)+" AS smallint),\n";
    queryStr += "CAST ("+QString::number(discount)+" AS double precision),\n";
    queryStr += "CAST ('"+observation+"' AS text),\n";
    queryStr += "CAST ("+QString::number(valuePaid)+" AS double precision),\n";
    queryStr += "CAST ('"+customerId+"' AS character varying),\n";

    int count = saleProductOrders->count();

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString productCode = saleProductOrders->at(i)->getProductCode();
        queryStr += (i == (count-1)) ? "'"+productCode+"'] AS character varying[]),\n" : "'"+productCode+"',";
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        int quantity = saleProductOrders->at(i)->getQuantity();
        queryStr += (i == (count-1)) ? "'"+QString::number(quantity)+"'] AS integer[]),\n" : "'"+QString::number(quantity)+"',";
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString cstIcmsCode = saleProductOrders->at(i)->getCstIcmsCode();
        if(cstIcmsCode.isNull())
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+cstIcmsCode+"'] AS character varying[]),\n" : "'"+cstIcmsCode+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString cstIpiCode = saleProductOrders->at(i)->getCstIpiCode();
        if(cstIpiCode.isNull())
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+cstIpiCode+"'] AS character varying[]),\n" : "'"+cstIpiCode+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString cstPisCode = saleProductOrders->at(i)->getCstPisCode();
        if(cstPisCode.isNull())
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+cstPisCode+"'] AS character varying[]),\n" : "'"+cstPisCode+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString cstCofinsCode = saleProductOrders->at(i)->getCstCofinsCode();
        if(cstCofinsCode.isNull())
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+cstCofinsCode+"'] AS character varying[]),\n" : "'"+cstCofinsCode+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString icmsPercentName = saleProductOrders->at(i)->getIcmsPercentName();
        if(icmsPercentName.isNull())
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+icmsPercentName+"'] AS character varying[]),\n" : "'"+icmsPercentName+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString ipiPercentName = saleProductOrders->at(i)->getIpiPercentName();
        if(ipiPercentName.isNull())
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+ipiPercentName+"'] AS character varying[]),\n" : "'"+ipiPercentName+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString pisPercentName = saleProductOrders->at(i)->getPisPercentName();
        if(pisPercentName.isNull())
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+pisPercentName+"'] AS character varying[]),\n" : "'"+pisPercentName+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString cofinsPercentName = saleProductOrders->at(i)->getCofinsPercentName();
        if(cofinsPercentName.isNull())
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+cofinsPercentName+"'] AS character varying[]),\n" : "'"+cofinsPercentName+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString cfopCode = saleProductOrders->at(i)->getCfopCode();
        if(cfopCode.isNull())
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+cfopCode+"'] AS character varying[]),\n" : "'"+cfopCode+"',";
        }
    }

//    queryStr += "CAST (ARRAY[";
//    for(int i=0; i<count; i++)
//    {
//        int priceId = saleProductOrders->at(i)->getPriceId();
//        queryStr += (i == (count-1)) ? "'"+QString::number(priceId)+"'] AS integer[]),\n" : "'"+QString::number(priceId)+"',";
//    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString storeCnpj = saleProductOrders->at(i)->getStoreCnpj();
        queryStr += (i == (count-1)) ? "'"+storeCnpj+"'] AS character varying[]),\n" : "'"+storeCnpj+"',";
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        //Price *price = getPriceByProductCodeAndStoreCnpj(saleProductOrders->at(i)->getProductCode(), this->defaultStore->getCNPJ());
        double productValue = saleProductOrders->at(i)->getValue();
        queryStr += (i == (count-1)) ? "'"+QString::number(productValue)+"'] AS double precision[])" : "'"+QString::number(productValue)+"',";
    }

    int salesOrderId = salesOrder->getId();
    if(salesOrderId != 0)
    {
        queryStr += ",\nCAST ("+QString::number(salesOrderId)+" AS integer),\n";

        queryStr += "CAST (ARRAY[";
        for(int i=0; i<count; i++)
        {
            int saleProductOrderId = saleProductOrders->at(i)->getId();
            queryStr += (i == (count-1)) ? "'"+QString::number(saleProductOrderId)+"'] AS integer[]),\n" : "'"+QString::number(saleProductOrderId)+"',";
        }

        queryStr += "CAST ('"+date.toString()+"' AS timestamp with time zone)\n";
    }

    queryStr += ");";

    qDebug() << queryStr;
//    return true;

    QSqlQuery query(queryStr);
    if (query.next()) {
        ret = query.value(0).toBool();
    }
    return ret;
}

bool DatabaseController::removeSalesOrder(int id, bool removeRelatedEntries)
{
    bool ret = false;

//    QSqlQuery deleteQuery;
//    deleteQuery.prepare("DELETE FROM erprock_sale_orders WHERE id=:id");
//    deleteQuery.bindValue(":id", id);

    QString removeRelatedEntriesStr = (removeRelatedEntries) ? "TRUE" : "FALSE";

    QString deleteQueryStr = "SELECT remove_sales_order(\n";
    deleteQueryStr += "CAST ('"+QString::number(id)+"' AS  integer),\n";
    deleteQueryStr += "CAST ('" + removeRelatedEntriesStr + "' AS boolean)";
    deleteQueryStr += ");";

    QSqlQuery deleteQuery;
    deleteQuery.prepare(deleteQueryStr);
    ret = deleteQuery.exec();

    return ret;
}

SalesOrder *DatabaseController::getSalesOrderById(int id)
{
    SalesOrder *salesOrder;
    QSqlQuery query("SELECT receipt, date, payment_condition, payment_form, discount, observation, value_paid, physical_customer_id, enterprise_customer_id FROM erprock_sale_orders WHERE id='"+QString::number(id)+"'");
    if (query.next()) {

        QList<SaleProductOrder*> *saleProductOrders = getSaleProductOrdersBySalesOrderId(id);

        QString receipt = query.value(0).toString();
        QDateTime date = query.value(1).toDateTime();
        int paymentCondition = query.value(2).toInt();
        Utilities::PaymentForm paymentForm = (Utilities::PaymentForm)query.value(3).toInt();
        double discount = query.value(4).toDouble();
        QString observation = query.value(5).toString();
        double valuePaid = query.value(6).toDouble();

        QString physicalCustomerCpf = query.value(7).toString();
        QString enterpriseCustomerCnpj = query.value(8).toString();
        QString customerId = (physicalCustomerCpf == NULL) ? enterpriseCustomerCnpj : physicalCustomerCpf;

        salesOrder = new SalesOrder(id, saleProductOrders, receipt, date, paymentCondition, paymentForm,
                                    discount, observation, valuePaid, customerId);
    }

    return salesOrder;
}

SalesOrder *DatabaseController::getSalesOrderByReceipt(QString receipt)
{
    SalesOrder *salesOrder;
    QSqlQuery query("SELECT id, date, payment_condition, payment_form, discount, observation, value_paid, physical_customer_id, enterprise_customer_id FROM erprock_sale_orders WHERE receipt='"+receipt+"'");
    if (query.next()) {

        int id = query.value(0).toInt();

        QList<SaleProductOrder*> *saleProductOrders = getSaleProductOrdersBySalesOrderId(id);

        QDateTime date = query.value(1).toDateTime();
        int paymentCondition = query.value(2).toInt();
        Utilities::PaymentForm paymentForm = (Utilities::PaymentForm)query.value(3).toInt();
        double discount = query.value(4).toDouble();
        QString observation = query.value(5).toString();
        double valuePaid = query.value(6).toDouble();

        QString physicalCustomerCpf = query.value(7).toString();
        QString enterpriseCustomerCnpj = query.value(8).toString();
        QString customerId = (physicalCustomerCpf == NULL) ? enterpriseCustomerCnpj : physicalCustomerCpf;

        salesOrder = new SalesOrder(id, saleProductOrders, receipt, date, paymentCondition,
                                    paymentForm, discount, observation, valuePaid, customerId);
    }

    return salesOrder;
}

QList<SalesOrder*> *DatabaseController::getSalesOrdersByDateRange(QDateTime startDate, QDateTime endDate)
{
    QList<SalesOrder*> *salesOrders = new QList<SalesOrder*>();

    QSqlQuery query;
    query.prepare("SELECT id, receipt, date, payment_condition, payment_form, discount, observation, value_paid, physical_customer_id, enterprise_customer_id FROM erprock_sale_orders WHERE date BETWEEN :start_date AND :end_date");
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);
    query.exec();
    while (query.next()) {

        int id = query.value(0).toInt();

        QList<SaleProductOrder*> *saleProductOrders = getSaleProductOrdersBySalesOrderId(id);

        QString receipt = query.value(1).toString();
        QDateTime date = query.value(2).toDateTime();
        int paymentCondition = query.value(3).toInt();
        Utilities::PaymentForm paymentForm = (Utilities::PaymentForm)query.value(4).toInt();
        double discount = query.value(5).toDouble();
        QString observation = query.value(6).toString();
        double valuePaid = query.value(7).toDouble();

        QString physicalCustomerCpf = query.value(8).toString();
        QString enterpriseCustomerCnpj = query.value(9).toString();
        QString customerId = (physicalCustomerCpf == NULL) ? enterpriseCustomerCnpj : physicalCustomerCpf;

        SalesOrder *salesOrder = new SalesOrder(id, saleProductOrders, receipt, date, paymentCondition,
                                                paymentForm, discount, observation, valuePaid, customerId);

        salesOrders->append(salesOrder);
    }

    return salesOrders;
}

QList<SalesOrder*> *DatabaseController::getSalesOrders()
{
    QList<SalesOrder*> *salesOrders = new QList<SalesOrder*>();
    QSqlQuery query("SELECT * FROM erprock_sale_orders ORDER BY date");
    while (query.next()) {

        int id = query.value(0).toInt();

        QList<SaleProductOrder*> *saleProductOrders = getSaleProductOrdersBySalesOrderId(id);

        QString receipt = query.value(1).toString();
        QDateTime date = query.value(2).toDateTime();
        int paymentCondition = query.value(3).toInt();
        Utilities::PaymentForm paymentForm = (Utilities::PaymentForm)query.value(4).toInt();
        double discount = query.value(5).toDouble();
        QString observation = query.value(6).toString();
        double valuePaid = query.value(7).toDouble();

        QString physicalCustomerCpf = query.value(8).toString();
        QString enterpriseCustomerCnpj = query.value(9).toString();
        QString customerId = (physicalCustomerCpf == NULL) ? enterpriseCustomerCnpj : physicalCustomerCpf;

        SalesOrder *salesOrder = new SalesOrder(id, saleProductOrders, receipt, date, paymentCondition,
                                                paymentForm, discount, observation, valuePaid, customerId);

        salesOrders->append(salesOrder);
    }

    return salesOrders;
}

QList<SaleProductOrder*> *DatabaseController::getSaleProductOrdersBySalesOrderId(int id)
{
    QList<SaleProductOrder*> *saleProductOrders = new QList<SaleProductOrder*>;
    QSqlQuery queryProductOrders("SELECT * FROM erprock_sale_product_orders WHERE order_id='"+QString::number(id)+"'");
    while (queryProductOrders.next()) {
        int id = queryProductOrders.value(0).toInt();
        QString productCode = queryProductOrders.value(2).toString();
        int quantity = queryProductOrders.value(3).toInt();
        QString cstIcmsCode = queryProductOrders.value(4).toString();
        QString cstIpiCode = queryProductOrders.value(5).toString();
        QString cstPisCode = queryProductOrders.value(6).toString();
        QString cstCofinsCode = queryProductOrders.value(7).toString();
        QString icmsPercentName = queryProductOrders.value(8).toString();
        QString ipiPercentName = queryProductOrders.value(9).toString();
        QString pisPercentName = queryProductOrders.value(10).toString();
        QString cofinsPercentName = queryProductOrders.value(11).toString();
        QString cfopCode = queryProductOrders.value(12).toString();
        //int priceId = queryProductOrders.value(13).toInt();
        QString storeCnpj = queryProductOrders.value(13).toString();
        double value = queryProductOrders.value(14).toDouble();

        SaleProductOrder * saleProductOrder =
                new SaleProductOrder(id, productCode, quantity, cstIcmsCode, cstIpiCode, cstPisCode, cstCofinsCode,
                                     icmsPercentName, ipiPercentName, pisPercentName, cofinsPercentName, cfopCode,
                                     storeCnpj, value);

        saleProductOrders->append(saleProductOrder);

    }

    return saleProductOrders;
}

SaleProductOrder *DatabaseController::getSaleProductOrderById(int id)
{
    SaleProductOrder *saleProductOrder;
    QSqlQuery queryProductOrders("SELECT product_code, quantity, cst_icms_code, cst_ipi_code, cst_pis_code, cst_cofins_code, icms_percent_name, ipi_percent_name, pis_percent_name, cofins_percent_name, cfop_code, store_cnpj value, FROM erprock_sale_product_orders WHERE id='"+QString::number(id)+"'");
    if(queryProductOrders.next()) {
        QString productCode = queryProductOrders.value(0).toString();
        int quantity = queryProductOrders.value(1).toInt();
        QString cstIcmsCode = queryProductOrders.value(2).toString();
        QString cstIpiCode = queryProductOrders.value(3).toString();
        QString cstPisCode = queryProductOrders.value(4).toString();
        QString cstCofinsCode = queryProductOrders.value(5).toString();
        QString icmsPercentName = queryProductOrders.value(6).toString();
        QString ipiPercentName = queryProductOrders.value(7).toString();
        QString pisPercentName = queryProductOrders.value(8).toString();
        QString cofinsPercentName = queryProductOrders.value(9).toString();
        QString cfopCode = queryProductOrders.value(10).toString();
        QString storeCnpj = queryProductOrders.value(11).toString();
        double value = queryProductOrders.value(12).toDouble();

        saleProductOrder = new SaleProductOrder(id, productCode, quantity, cstIcmsCode, cstIpiCode, cstPisCode,
                                                cstCofinsCode, icmsPercentName, ipiPercentName, pisPercentName,
                                                cofinsPercentName, cfopCode, storeCnpj, value);

    }

    return saleProductOrder;
}

bool DatabaseController::purchasesOrderAlreadyExists(QString receipt, QString providerId)
{
    bool ret = false;
    QSqlQuery query("SELECT id FROM erprock_purchase_orders WHERE receipt='"+receipt+"' AND provider_id='"+providerId+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::storePurchasesOrder(PurchasesOrder *purchasesOrder)
{
    bool ret = false;

    QList<PurchaseProductOrder*> *purchaseProductOrders = purchasesOrder->getPurchaseProductOrders();
    QDateTime date = purchasesOrder->getDate();
    QString receipt = purchasesOrder->getReceipt();
    QString providerId = purchasesOrder->getProviderId();
    int paymentCondition = purchasesOrder->getPaymentCondition();
    Utilities::PaymentForm paymentForm = purchasesOrder->getPaymentForm();
    QString observation = purchasesOrder->getObservation();
    double valuePaid = purchasesOrder->getValuePaid();
    double cargo = purchasesOrder->getCargo();

    QString queryStr = "SELECT store_purchases_order(\n";
    queryStr += "CAST ('"+receipt+"' AS  character varying),\n";
    queryStr += "CAST ('"+date.toString()+"' AS timestamp with time zone),\n";
    queryStr += "CAST ('"+providerId+"' AS character varying),\n";
    queryStr += "CAST ("+QString::number(paymentCondition)+" AS smallint),\n";
    queryStr += "CAST ("+QString::number(paymentForm)+" AS smallint),\n";
    queryStr += "CAST ('"+observation+"' AS text),\n";
    queryStr += "CAST ("+QString::number(valuePaid)+" AS double precision),\n";
    queryStr += "CAST ("+QString::number(cargo)+" AS double precision),\n";

    int count = purchaseProductOrders->count();

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString productCode = purchaseProductOrders->at(i)->getProductCode();
        queryStr += (i == (count-1)) ? "'"+productCode+"'] AS character varying[]),\n" : "'"+productCode+"',";
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        int quantity = purchaseProductOrders->at(i)->getQuantity();
        queryStr += (i == (count-1)) ? "'"+QString::number(quantity)+"'] AS integer[]),\n" : "'"+QString::number(quantity)+"',";
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QChar productOriginCode = purchaseProductOrders->at(i)->getProductOriginCode();
        queryStr += (i == (count-1)) ? "'"+QString(productOriginCode)+"'] AS character varying[]),\n" : "'"+QString(productOriginCode)+"',";
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString cstIcmsCode = purchaseProductOrders->at(i)->getCstIcmsCode();
        if((cstIcmsCode.isNull()) || (cstIcmsCode.length() == 0))
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+cstIcmsCode+"'] AS character varying[]),\n" : "'"+cstIcmsCode+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString cstIpiCode = purchaseProductOrders->at(i)->getCstIpiCode();
        if((cstIpiCode.isNull()) || (cstIpiCode.length() == 0))
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+cstIpiCode+"'] AS character varying[]),\n" : "'"+cstIpiCode+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString cstPisCode = purchaseProductOrders->at(i)->getCstPisCode();
        if((cstPisCode.isNull()) || (cstPisCode.length() == 0))
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+cstPisCode+"'] AS character varying[]),\n" : "'"+cstPisCode+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString cstCofinsCode = purchaseProductOrders->at(i)->getCstCofinsCode();
        if((cstCofinsCode.isNull()) || (cstCofinsCode.length() == 0))
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+cstCofinsCode+"'] AS character varying[]),\n" : "'"+cstCofinsCode+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        double icmsValue = purchaseProductOrders->at(i)->getIcmsValue();
        if(icmsValue == 0)
        {
            queryStr += (i == (count-1)) ? "NULL] AS double precision[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+QString::number(icmsValue)+"'] AS double precision[]),\n" : "'"+QString::number(icmsValue)+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        double ipiValue = purchaseProductOrders->at(i)->getIpiValue();
        if(ipiValue == 0)
        {
            queryStr += (i == (count-1)) ? "NULL] AS double precision[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+QString::number(ipiValue)+"'] AS double precision[]),\n" : "'"+QString::number(ipiValue)+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        double pisValue = purchaseProductOrders->at(i)->getPisValue();
        if(pisValue == 0)
        {
            queryStr += (i == (count-1)) ? "NULL] AS double precision[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+QString::number(pisValue)+"'] AS double precision[]),\n" : "'"+QString::number(pisValue)+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        double cofinsValue = purchaseProductOrders->at(i)->getCofinsValue();
        if(cofinsValue == 0)
        {
            queryStr += (i == (count-1)) ? "NULL] AS double precision[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+QString::number(cofinsValue)+"'] AS double precision[]),\n" : "'"+QString::number(cofinsValue)+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString cfopCode = purchaseProductOrders->at(i)->getCfopCode();
        if((cfopCode.isNull()) || (cfopCode.length() == 0))
        {
            queryStr += (i == (count-1)) ? "NULL] AS character varying[]),\n" : "NULL,";
        }
        else
        {
            queryStr += (i == (count-1)) ? "'"+cfopCode+"'] AS character varying[]),\n" : "'"+cfopCode+"',";
        }
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        double unitPrice = purchaseProductOrders->at(i)->getUnitPrice();
        queryStr += (i == (count-1)) ? "'"+QString::number(unitPrice)+"'] AS double precision[]),\n" : "'"+QString::number(unitPrice)+"',";
    }

    queryStr += "CAST (ARRAY[";
    for(int i=0; i<count; i++)
    {
        QString storeCnpj = purchaseProductOrders->at(i)->getStoreCnpj();
        queryStr += (i == (count-1)) ? "'"+storeCnpj+"'] AS character varying[])" : "'"+storeCnpj+"',";
    }

    int purchasesOrderId = purchasesOrder->getId();
    if(purchasesOrderId != 0)
    {
        queryStr += ",\nCAST ("+QString::number(purchasesOrderId)+" AS integer),\n";

        queryStr += "CAST (ARRAY[";
        for(int i=0; i<count; i++)
        {
            int purchaseProductOrderId = purchaseProductOrders->at(i)->getId();
            queryStr += (i == (count-1)) ? "'"+QString::number(purchaseProductOrderId)+"'] AS integer[])\n" : "'"+QString::number(purchaseProductOrderId)+"',";
        }
    }

    queryStr += ");";

    qDebug() << queryStr;
//    return true;

    QSqlQuery query(queryStr);
    if (query.next()) {
        ret = query.value(0).toBool();
    }
    return ret;
}

bool DatabaseController::removePurchasesOrder(int id, bool removeRelatedEntries)
{
    bool ret = false;

//    QSqlQuery deleteQuery;
//    deleteQuery.prepare("DELETE FROM erprock_purchase_orders WHERE id=:id");
//    deleteQuery.bindValue(":id", id);

    QString removeRelatedEntriesStr = (removeRelatedEntries) ? "TRUE" : "FALSE";

    QString deleteQueryStr = "SELECT remove_purchases_order(\n";
    deleteQueryStr += "CAST ('"+QString::number(id)+"' AS  integer),\n";
    deleteQueryStr += "CAST ('" + removeRelatedEntriesStr + "' AS boolean)";
    deleteQueryStr += ");";

    QSqlQuery deleteQuery;
    deleteQuery.prepare(deleteQueryStr);
    ret = deleteQuery.exec();

    return ret;
}

PurchasesOrder *DatabaseController::getPurchasesOrderById(int id)
{
    PurchasesOrder *purchasesOrder;
    QSqlQuery query("SELECT receipt, date, provider_id, payment_condition, payment_form, observation, value_paid, cargo FROM erprock_purchase_orders WHERE id='"+QString::number(id)+"'");
    if (query.next()) {

        QList<PurchaseProductOrder*> *purchaseProductOrders = getPurchaseProductOrdersByPurchasesOrderId(id);

        QString receipt = query.value(0).toString();
        QDateTime date = query.value(1).toDateTime();
        QString providerId = query.value(2).toString();
        int paymentCondition = query.value(3).toInt();
        Utilities::PaymentForm paymentForm = (Utilities::PaymentForm)query.value(4).toInt();
        QString observation = query.value(5).toString();
        double valuePaid = query.value(6).toDouble();
        double cargo = query.value(7).toDouble();

        purchasesOrder = new PurchasesOrder(id, purchaseProductOrders, receipt, date, providerId, paymentCondition,
                                            paymentForm, observation, valuePaid, cargo);
    }

    return purchasesOrder;
}

PurchasesOrder *DatabaseController::getPurchasesOrderByReceipt(QString receipt)
{
    PurchasesOrder *purchasesOrder;
    QSqlQuery query("SELECT id, date, provider_id, payment_condition, payment_form, observation, value_paid, cargo FROM erprock_purchase_orders WHERE receipt='"+receipt+"'");
    if (query.next()) {

        int id = query.value(0).toInt();

        QList<PurchaseProductOrder*> *purchaseProductOrders = getPurchaseProductOrdersByPurchasesOrderId(id);

        QDateTime date = query.value(1).toDateTime();
        QString providerId = query.value(2).toString();
        int paymentCondition = query.value(3).toInt();
        Utilities::PaymentForm paymentForm = (Utilities::PaymentForm)query.value(4).toInt();
        QString observation = query.value(5).toString();
        double valuePaid = query.value(6).toDouble();
        double cargo = query.value(7).toDouble();

        purchasesOrder = new PurchasesOrder(id, purchaseProductOrders, receipt, date, providerId, paymentCondition,
                                            paymentForm, observation, valuePaid, cargo);
    }

    return purchasesOrder;
}

QList<PurchasesOrder*> *DatabaseController::getPurchasesOrdersByDateRange(QDateTime startDate, QDateTime endDate)
{
    QList<PurchasesOrder*> *purchasesOrders = new QList<PurchasesOrder*>();

    QSqlQuery query;
    query.prepare("SELECT id, receipt, date, provider_id, payment_condition, payment_form, observation, value_paid, cargo FROM erprock_purchase_orders WHERE date BETWEEN :start_date AND :end_date");
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);
    query.exec();
    while (query.next()) {

        int id = query.value(0).toInt();

        QList<PurchaseProductOrder*> *purchaseProductOrders = getPurchaseProductOrdersByPurchasesOrderId(id);

        QString receipt = query.value(1).toString();
        QDateTime date = query.value(2).toDateTime();
        QString providerId = query.value(3).toString();
        int paymentCondition = query.value(4).toInt();
        Utilities::PaymentForm paymentForm = (Utilities::PaymentForm)query.value(5).toInt();
        QString observation = query.value(6).toString();
        double valuePaid = query.value(7).toDouble();
        double cargo = query.value(8).toDouble();

        PurchasesOrder *purchasesOrder = new PurchasesOrder(id, purchaseProductOrders, receipt, date, providerId,
                                                            paymentCondition, paymentForm, observation, valuePaid, cargo);

        purchasesOrders->append(purchasesOrder);
    }

    return purchasesOrders;
}

QList<PurchasesOrder*> *DatabaseController::getPurchasesOrders()
{
    QList<PurchasesOrder*> *purchasesOrders = new QList<PurchasesOrder*>();
    QSqlQuery query("SELECT * FROM erprock_purchase_orders ORDER BY date");
    while (query.next()) {

        int id = query.value(0).toInt();

        QList<PurchaseProductOrder*> *purchaseProductOrders = getPurchaseProductOrdersByPurchasesOrderId(id);

        QString receipt = query.value(1).toString();
        QDateTime date = query.value(2).toDateTime();
        QString providerId = query.value(3).toString();
        int paymentCondition = query.value(4).toInt();
        Utilities::PaymentForm paymentForm = (Utilities::PaymentForm)query.value(5).toInt();
        QString observation = query.value(6).toString();
        double valuePaid = query.value(7).toDouble();
        double cargo = query.value(8).toDouble();

        PurchasesOrder *purchasesOrder = new PurchasesOrder(id, purchaseProductOrders, receipt, date, providerId,
                                                            paymentCondition,paymentForm, observation, valuePaid, cargo);

        purchasesOrders->append(purchasesOrder);
    }

    return purchasesOrders;
}

QList<PurchaseProductOrder*> *DatabaseController::getPurchaseProductOrdersByPurchasesOrderId(int id)
{
    QList<PurchaseProductOrder*> *purchaseProductOrders = new QList<PurchaseProductOrder*>;
    QSqlQuery queryProductOrders("SELECT * FROM erprock_purchase_product_orders WHERE order_id='"+QString::number(id)+"'");
    while (queryProductOrders.next()) {
        int id = queryProductOrders.value(0).toInt();
        QString productCode = queryProductOrders.value(2).toString();
        int quantity = queryProductOrders.value(3).toInt();
        QString productOriginCode = queryProductOrders.value(4).toString();
        QString cstIcmsCode = queryProductOrders.value(5).toString();
        QString cstIpiCode = queryProductOrders.value(6).toString();
        QString cstPisCode = queryProductOrders.value(7).toString();
        QString cstCofinsCode = queryProductOrders.value(8).toString();
        double icmsValue = queryProductOrders.value(9).toDouble();
        double ipiValue = queryProductOrders.value(10).toDouble();
        double pisValue = queryProductOrders.value(11).toDouble();
        double cofinsValue = queryProductOrders.value(12).toDouble();
        QString cfopCode = queryProductOrders.value(13).toString();
        double unitPrice = queryProductOrders.value(14).toDouble();
        QString storeCnpj = queryProductOrders.value(15).toString();

        PurchaseProductOrder * purchaseProductOrder =
                new PurchaseProductOrder(id, productCode, quantity, productOriginCode.at(0), cstIcmsCode, cstIpiCode, cstPisCode,
                                         cstCofinsCode,icmsValue, ipiValue, pisValue, cofinsValue,
                                         cfopCode, unitPrice, storeCnpj);

        purchaseProductOrders->append(purchaseProductOrder);

    }

    return purchaseProductOrders;
}

PurchaseProductOrder *DatabaseController::getPurchaseProductOrderById(int id)
{
    PurchaseProductOrder *purchaseProductOrder;
    QSqlQuery queryProductOrders("SELECT product_code, quantity, product_origin_code, cst_icms_code, cst_ipi_code, cst_pis_code, cst_cofins_code, icms_value, ipi_value, pis_value, cofins_value, cfop_code, store_cnpj FROM erprock_purchase_product_orders WHERE id='"+QString::number(id)+"'");
    if(queryProductOrders.next()) {
        QString productCode = queryProductOrders.value(0).toString();
        int quantity = queryProductOrders.value(1).toInt();
        QChar productOriginCode = queryProductOrders.value(2).toChar();
        QString cstIcmsCode = queryProductOrders.value(3).toString();
        QString cstIpiCode = queryProductOrders.value(4).toString();
        QString cstPisCode = queryProductOrders.value(5).toString();
        QString cstCofinsCode = queryProductOrders.value(6).toString();
        double icmsValue = queryProductOrders.value(7).toDouble();
        double ipiValue = queryProductOrders.value(8).toDouble();
        double pisValue = queryProductOrders.value(9).toDouble();
        double cofinsValue = queryProductOrders.value(10).toDouble();
        QString cfopCode = queryProductOrders.value(11).toString();
        double unitPrice = queryProductOrders.value(12).toDouble();
        QString storeCnpj = queryProductOrders.value(13).toString();

        purchaseProductOrder = new PurchaseProductOrder(id, productCode, quantity, productOriginCode, cstIcmsCode,
                                                        cstIpiCode, cstPisCode, cstCofinsCode, icmsValue,
                                                        ipiValue, pisValue, cofinsValue, cfopCode,
                                                        unitPrice, storeCnpj);

    }

    return purchaseProductOrder;
}

bool DatabaseController::accountAlreadyExists(QString code)
{
    bool ret = false;
    QSqlQuery query("SELECT name FROM erprock_accounts WHERE code='"+code+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewAccount(Account *account, bool isAnalytic)
{
    bool ret = false;

    QSqlQuery insertQuery;

    if(isAnalytic)
    {
        insertQuery.prepare("INSERT INTO erprock_accounts (code, name, type, reductive) VALUES(:code, :name, :type, :reductive)");
        insertQuery.bindValue(":code", account->getCode());
        insertQuery.bindValue(":name", account->getName());
        insertQuery.bindValue(":type", account->getType());
        insertQuery.bindValue(":reductive", account->isReductive());
    }
    else
    {
        insertQuery.prepare("INSERT INTO erprock_accounts (code, name, type) VALUES(:code, :name, :type)");
        insertQuery.bindValue(":code", account->getCode());
        insertQuery.bindValue(":name", account->getName());
        insertQuery.bindValue(":type", account->getType());
    }

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateAccount(QString code, Account *account, bool isAnalytic)
{
    bool ret = false;

    QSqlQuery updateQuery;

    if(isAnalytic)
    {
        updateQuery.prepare("UPDATE erprock_accounts SET code=:code, name=:name, type=:type, reductive=:reductive WHERE code=:originalCode");
        updateQuery.bindValue(":originalCode", code);
        updateQuery.bindValue(":code", account->getCode());
        updateQuery.bindValue(":name", account->getName());
        updateQuery.bindValue(":type", account->getType());
        updateQuery.bindValue(":reductive", account->isReductive());
    }
    else
    {
        updateQuery.prepare("UPDATE erprock_accounts SET code=:code, name=:name, type=:type WHERE code=:originalCode");
        updateQuery.bindValue(":originalCode", code);
        updateQuery.bindValue(":code", account->getCode());
        updateQuery.bindValue(":name", account->getName());
        updateQuery.bindValue(":type", account->getType());
    }

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeAccount(QString code)
{
    bool ret = false;

    QString deleteQueryStr = "DELETE FROM erprock_accounts WHERE code LIKE '"+code+"%'";
    QSqlQuery deleteQuery;
    deleteQuery.prepare(deleteQueryStr);
    //deleteQuery.bindValue(":code", code);

    ret = deleteQuery.exec();

    return ret;
}

Account *DatabaseController::getAccountByCode(QString code)
{
    Account *account;
    QSqlQuery query("SELECT name, type, reductive FROM erprock_accounts WHERE code='"+code+"'");
    if (query.next()) {
        QString name = query.value(0).toString();
        Account::AccountType type = (Account::AccountType) query.value(1).toInt();
        bool isReductive = query.value(2).toBool();

        account = new Account(code, name, type, isReductive);
    }

    return account;
}

QList<Account*> *DatabaseController::getAccounts(QString filter)
{
    QList<Account*> *accounts = new QList<Account*>();
    QSqlQuery query("SELECT * FROM erprock_accounts "+filter+" ORDER BY code");
    while (query.next()) {
        QString code = query.value(0).toString();
        QString name = query.value(1).toString();
        Account::AccountType type = (Account::AccountType) query.value(2).toInt();
        bool isReductive = query.value(3).toBool();

        Account *account = new Account(code, name, type, isReductive);
        accounts->append(account);
    }

    return accounts;
}

QStringList *DatabaseController::getAccountTypes()
{
    QStringList *types = new QStringList();
    QSqlQuery query("SELECT name FROM erprock_account_types");
    while (query.next()) {
        QString name = query.value(0).toString();
        types->append(name);
    }

    return types;
}

bool DatabaseController::historyAlreadyExists(QString name)
{
    bool ret = false;
    QSqlQuery query("SELECT id FROM erprock_histories WHERE name='"+name+"'");
    if (query.next()) {
        ret = true;
    }
    return ret;
}

bool DatabaseController::createNewHistory(History *history)
{
    bool ret = false;

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO erprock_histories (name) VALUES(:name)");
    insertQuery.bindValue(":name", history->getName());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateHistory(History *history)
{
    bool ret = false;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE erprock_histories SET name=:name WHERE id=:id");
    updateQuery.bindValue(":id", history->getId());
    updateQuery.bindValue(":name", history->getName());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeHistory(int id)
{
    bool ret = false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM erprock_histories WHERE id=:id");
    deleteQuery.bindValue(":id", id);

    ret = deleteQuery.exec();

    return ret;
}

History *DatabaseController::getHistoryById(int id)
{
    History *history;
    QSqlQuery query("SELECT name FROM erprock_histories WHERE id='"+QString::number(id)+"'");
    if (query.next()) {
        QString name = query.value(0).toString();
        history = new History(id, name);
    }

    return history;
}

QList<History*> *DatabaseController::getHistories()
{
    QList<History*> *histories = new QList<History*>();
    QSqlQuery query("SELECT * FROM erprock_histories ORDER BY id");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();

        History *history = new History(id, name);
        histories->append(history);
    }

    return histories;
}

bool DatabaseController::createNewEntry(Entry *entry)
{
    bool ret = false;

    QSqlQuery insertQuery;

    insertQuery.prepare("INSERT INTO erprock_entries (date, store, debtor_account, creditor_account, value, history, complement) VALUES(:date, :store, :debtor_account, :creditor_account, :value, :history, :complement)");
    insertQuery.bindValue(":date", entry->getDate());
    insertQuery.bindValue(":store", entry->getStoreCnpj());
    insertQuery.bindValue(":debtor_account", entry->getDebtorAccount());
    insertQuery.bindValue(":creditor_account", entry->getCreditorAccount());
    insertQuery.bindValue(":value", entry->getValue());
    insertQuery.bindValue(":history", entry->getHistory());
    insertQuery.bindValue(":complement", entry->getComplement());

    ret = insertQuery.exec();

    return ret;
}

bool DatabaseController::updateEntry(Entry *entry)
{
    bool ret = false;

    QSqlQuery updateQuery;

    updateQuery.prepare("UPDATE erprock_entries SET date=:date, store=:store, debtor_account=:debtor_account, creditor_account=:creditor_account, value=:value, history=:history, complement=:complement WHERE id=:id");
    updateQuery.bindValue(":id", entry->getId());
    updateQuery.bindValue(":date", entry->getDate());
    updateQuery.bindValue(":store", entry->getStoreCnpj());
    updateQuery.bindValue(":debtor_account", entry->getDebtorAccount());
    updateQuery.bindValue(":creditor_account", entry->getCreditorAccount());
    updateQuery.bindValue(":value", entry->getValue());
    updateQuery.bindValue(":history", entry->getHistory());
    updateQuery.bindValue(":complement", entry->getComplement());

    ret = updateQuery.exec();

    return ret;
}

bool DatabaseController::removeEntry(int id)
{
    bool ret = false;

    QString deleteQueryStr = "DELETE FROM erprock_entries WHERE id='"+QString::number(id)+"'";
    QSqlQuery deleteQuery;
    deleteQuery.prepare(deleteQueryStr);

    ret = deleteQuery.exec();

    return ret;
}

Entry *DatabaseController::getEntryById(int id)
{
    Entry *entry;
    QSqlQuery query("SELECT date, store, debtor_account, creditor_account, value, history, complement, purchase_order_id, sale_order_id FROM erprock_entries WHERE id='"+QString::number(id)+"'");
    if (query.next()) {
        QDateTime date = query.value(0).toDateTime();
        QString storeCnpj = query.value(1).toString();
        QString debtorAccount = query.value(2).toString();
        QString creditorAccount = query.value(3).toString();
        double value = query.value(4).toDouble();
        int history = query.value(5).toInt();
        QString complement = query.value(6).toString();
        int purchaseOrderId = query.value(7).toInt();
        int saleOrderId = query.value(8).toInt();

        entry = new Entry(id, date, storeCnpj, debtorAccount, creditorAccount, value, history, complement, purchaseOrderId, saleOrderId);
    }

    return entry;
}

QList<Entry*> *DatabaseController::getEntriesBetweenDates(QDateTime startDate, QDateTime endDate)
{
    QList<Entry*> *entries = new QList<Entry*>();

    QSqlQuery query;
    query.prepare("SELECT id, date, store, debtor_account, creditor_account, value, history, complement, purchase_order_id, sale_order_id FROM erprock_entries WHERE date BETWEEN :start_date AND :end_date");
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);
    query.exec();
    while (query.next()) {
        int id = query.value(0).toInt();
        QDateTime date = query.value(1).toDateTime();
        QString storeCnpj = query.value(2).toString();
        QString debtorAccount = query.value(3).toString();
        QString creditorAccount = query.value(4).toString();
        double value = query.value(5).toDouble();
        int history = query.value(6).toInt();
        QString complement = query.value(7).toString();
        int purchaseOrderId = query.value(8).toInt();
        int saleOrderId = query.value(9).toInt();

        Entry *entry = new Entry(id, date, storeCnpj, debtorAccount, creditorAccount, value, history, complement, purchaseOrderId, saleOrderId);
        entries->append(entry);
    }

    return entries;
}

QList<Entry*> *DatabaseController::getEntries()
{
    QList<Entry*> *entries = new QList<Entry*>();
    QSqlQuery query("SELECT * FROM erprock_entries ORDER BY id");
    while (query.next()) {
        int id = query.value(0).toInt();
        QDateTime date = query.value(1).toDateTime();
        QString storeCnpj = query.value(2).toString();
        QString debtorAccount = query.value(3).toString();
        QString creditorAccount = query.value(4).toString();
        double value = query.value(5).toDouble();
        int history = query.value(6).toInt();
        QString complement = query.value(7).toString();
        int purchaseOrderId = query.value(8).toInt();
        int saleOrderId = query.value(9).toInt();

        Entry *entry = new Entry(id, date, storeCnpj, debtorAccount, creditorAccount, value, history, complement, purchaseOrderId, saleOrderId);
        entries->append(entry);
    }

    return entries;
}
