#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#ifdef DB_POSTGRESQL

#ifdef Q_OS_UNIX
#include "/usr/local/qt-everywhere-opensource-src-4.8.0/src/sql/drivers/psql/qsql_psql.h"
#elif (defined Q_OS_WIN)
#include "C:\\qt-everywhere-opensource-src-5.2.0\\qtbase\\src\\sql\\drivers\\psql\\qsql_psql_p.h"
#endif

#endif

#define PREFIX_DEFAULT_STORE "default_store"
////#define PREFIX_CUSTOMER_ACCOUNT "customer_account"
//#define PREFIX_PROVIDER_ACCOUNT "provider_account"
////#define PREFIX_CASH_ACCOUNT "cash_account"
//#define PREFIX_ICMS_TO_RECOVER "icms_to_recover"
//#define PREFIX_PIS_TO_RECOVER "pis_to_recover"
//#define PREFIX_COFINS_TO_RECOVER "cofins_to_recover"
//#define PREFIX_PRODUCT_STOCK "product_stock"
//#define PREFIX_DEBTOR_ACCOUNT_SALE "debtor_account_sale"
//#define PREFIX_CREDITOR_ACCOUNT_SALE "creditor_account_sale"
//#define PREFIX_ICMS_IN_SALES_DEBTOR_ACCOUNT "icms_in_sales_debtor_account"
//#define PREFIX_ICMS_IN_SALES_CREDITOR_ACCOUNT "icms_in_sales_creditor_account"
//#define PREFIX_PIS_IN_SALES_DEBTOR_ACCOUNT "pis_in_sales_debtor_account"
//#define PREFIX_PIS_IN_SALES_CREDITOR_ACCOUNT "pis_in_sales_creditor_account"
//#define PREFIX_COFINS_IN_SALES_DEBTOR_ACCOUNT "cofins_in_sales_debtor_account"
//#define PREFIX_COFINS_IN_SALES_CREDITOR_ACCOUNT "cofins_in_sales_creditor_account"
//#define PREFIX_GOODS_SHIPPING_DEBTOR_ACCOUNT "goods_shipping_debtor_account"
//#define PREFIX_GOODS_SHIPPING_CREDITOR_ACCOUNT "goods_shipping_creditor_account"
//#define PREFIX_BUY_PRODUCT_HISTORY_ID "buy_product_history_id"
//#define PREFIX_TAX_CREDIT_HISTORY_ID "tax_credit_history_id"
//#define PREFIX_SALE_HISTORY_ID "sale_history_id"
//#define PREFIX_ICMS_IN_SALES_HISTORY_ID "icms_in_sales_history_id"
//#define PREFIX_PIS_IN_SALES_HISTORY_ID "pis_in_sales_history_id"
//#define PREFIX_COFINS_IN_SALES_HISTORY_ID "cofins_in_sales_history_id"
//#define PREFIX_GOODS_SHIPPING_HISTORY_ID "goods_shipping_history_id"

#include "user.h"
#include "manufacturer.h"
#include "provider.h"
#include "productcategory.h"
#include "product.h"
#include "enterprisecustomer.h"
#include "physicalcustomer.h"
#include "stockunit.h"
#include "productorigin.h"
#include "csticms.h"
#include "cstipi.h"
#include "cstpis.h"
#include "cstcofins.h"
#include "taxrate.h"
#include "cfop.h"
#include "price.h"
#include "store.h"
#include "salesorder.h"
#include "purchasesorder.h"
#include "account.h"
#include "history.h"
#include "entry.h"

//!  Controller for database
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is responsible for database management.
*/
class DatabaseController : public QObject
{
    Q_OBJECT
public:

    //! Returns unique instance.
    /*!
    * This method returns the unique instance of database controller singleton.
    */
    static DatabaseController* getInstance();

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~DatabaseController();

    /*!
    This method tells if the database connection is already stablished.
      \return Returns if it is connected to database.
      \sa userAlreadyExists(), createNewUser(), updateUser(), removeUser(), getUsers(), getUserByCPF(), getUserRoleName() and getUsersRoles()
    */
    bool isConnectionOpen();

    Store *getDefaultStore();

//    //QString getDefaultCustomerAccount();

//    QString getDefaultProviderAccount();

//    //QString getDefaultCashAccount();

//    QString getDefaultIcmsToRecoverAccount();

//    QString getDefaultPisToRecoverAccount();

//    QString getDefaultCofinsToRecoverAccount();

//    QString getDefaultProductStockAccount();

//    QString getDefaultDebtorSaleAccount();

//    QString getDefaultCreditorSaleAccount();

//    QString getDefaultIcmsInSalesDebtorAccount();

//    QString getDefaultIcmsInSalesCreditorAccount();

//    QString getDefaultPisInSalesDebtorAccount();

//    QString getDefaultPisInSalesCreditorAccount();

//    QString getDefaultCofinsInSalesDebtorAccount();

//    QString getDefaultCofinsInSalesCreditorAccount();

//    QString getDefaultGoodsShippingDebtorAccount();

//    QString getDefaultGoodsShippingCreditorAccount();

//    int getBuyProductHistoryId();

//    int getTaxCreditHistoryId();

//    int getSaleHistoryId();

//    int getIcmsInSalesHistoryId();

//    int getPisInSalesHistoryId();

//    int getCofinsInSalesHistoryId();

//    int getGoodsShippingHistoryId();

    /*!
    Validates the user login.
      \param cpf The User's CPF.
      \param password The User's encrypted password.
      \return Returns true if the credentials match, otherwise return false.
    */
    bool validateLogin(QString cpf, QString password);

    //============== USERS ===============
    /*!
    Check if the cpf belongs to an user that is already stored at database.
      \param cpf The User's CPF.
      \return Returns if it is already stored at database.
      \sa isConnectionOpen(), createNewUser(), updateUser(), removeUser(), getUsers(), getUserByCPF(), getUserRoleName() and getUsersRoles()
    */
    bool userAlreadyExists(QString cpf);

    /*!
    Stores a new user at database.
      \param cpf The User's CPF.
      \param role The User's Role.
      \param name The User's Name.
      \param password The User's Password.
      \return Returns if it is succeeded or not.
      \sa isConnectionOpen(), userAlreadyExists(), updateUser(), removeUser(), getUsers(), getUserByCPF(), getUserRoleName() and getUsersRoles()
    */
    bool createNewUser(QString cpf, User::UserRole role, QString name, QString password);

    /*!
    Updates an user from database.
      \param cpf The User's CPF.
      \param role The User's Role.
      \param name The User's Name.
      \param password The User's Password.
      \return Returns if it is succeeded or not.
      \sa isConnectionOpen(), userAlreadyExists(), createNewUser(), removeUser(), getUsers(), getUserByCPF(), getUserRoleName() and getUsersRoles()
    */
    bool updateUser(QString cpf, User::UserRole role, QString name, QString password);

    /*!
    Removes an user from database.
      \param cpf The User's CPF.
      \return Returns if it is succeeded or not.
      \sa isConnectionOpen(), userAlreadyExists(), createNewUser(), updateUser(), getUsers(), getUserByCPF(), getUserRoleName() and getUsersRoles()
    */
    bool removeUser(QString cpf);

    /*!
    Get an user by his CPF.
      \param cpf The User's CPF.
      \return Returns the user object associated with the given CPF.
      \sa isConnectionOpen(), userAlreadyExists(), createNewUser(), updateUser(), removeUser(), getUsers(), getUserRoleName() and getUsersRoles()
    */
    User *getUserByCPF(QString cpf);

    /*!
    This method returns all the users that were previously stored at database.
      \return Returns all stored users.
      \sa isConnectionOpen(), userAlreadyExists(), createNewUser(), updateUser(), removeUser(), getUserByCPF(), getUserRoleName() and getUsersRoles()
    */
    QList<User*> *getUsers();

    /*!
    This method returns the user's role name by its id.
      \return Returns the role name.
      \sa isConnectionOpen(), userAlreadyExists(), createNewUser(), updateUser(), removeUser(), getUserByCPF(), getUsers() and getUsersRoles()
    */
    QString getUserRoleName(User::UserRole id);

    /*!
    This method returns all the user's roles that were previously stored at database.
      \return Returns all stored user's roles.
      \sa isConnectionOpen(), userAlreadyExists(), createNewUser(), updateUser(), removeUser(), getUserByCPF(), getUsers() and getUserRoleName()
    */
    QStringList *getUsersRoles();

    //=========== MANUFACTURERS =============
    /*!
    Check if the cnpj belongs to a manufacturer that is already stored at database.
      \param cnpj The Manufacturer's CNPJ.
      \return Returns if it is already stored at database.
      \sa createNewManufacturer(), updateManufacturer(), removeManufacturer(), getManufacturers() and getManufacturerByCNPJ()
    */
    bool manufacturerAlreadyExists(QString cnpj);

    /*!
    Stores a new manufacturer at database.
      \param manufacturer The new manufacturer.
      \return Returns if it is succeeded or not.
      \sa manufacturerAlreadyExists(), updateManufacturer(), removeManufacturer(), getManufacturers() and getManufacturerByCNPJ()
    */
    bool createNewManufacturer(Manufacturer *manufacturer);

    /*!
    Updates a manufacturer from database.
      \param manufacturer The manufacturer to be updated.
      \return Returns if it is succeeded or not.
      \sa manufacturerAlreadyExists(), createNewManufacturer(), removeManufacturer(), getManufacturers() and getManufacturerByCNPJ()
    */
    bool updateManufacturer(Manufacturer *manufacturer);

    /*!
    Removes a manufacturer from database.
      \param cnpj The Manufacturer's CNPJ.
      \return Returns if it is succeeded or not.
      \sa manufacturerAlreadyExists(), createNewManufacturer(), updateManufacturer(), getManufacturers() and getManufacturerByCNPJ()
    */
    bool removeManufacturer(QString cnpj);

    /*!
    Get a manufacturer by its CNPJ.
      \param cnpj The manufacturer's CNPJ.
      \return Returns the manufacturer object associated with the given CNPJ.
      \sa manufacturerAlreadyExists(), createNewManufacturer(), updateManufacturer(), removeManufacturer() and getManufacturers()
    */
    Manufacturer *getManufacturerByCNPJ(QString cnpj);

    /*!
    This method returns all the manufacturers that were previously stored at database.
      \return Returns all stored manufacturers.
      \sa manufacturerAlreadyExists(), createNewManufacturer(), updateManufacturer(), removeManufacturer() and getManufacturerByCNPJ()
    */
    QList<Manufacturer*> *getManufacturers();

    //=========== PROVIDERS =============
    /*!
    Check if the cnpj belongs to a provider that is already stored at database.
      \param cnpj The Provider's CNPJ.
      \return Returns if it is already stored at database.
      \sa createNewProvider(), updateProvider(), removeProvider(), getProviders() and getProviderByCNPJ()
    */
    bool providerAlreadyExists(QString cnpj);

    /*!
    Stores a new provider at database.
      \param provider The new provider.
      \return Returns if it is succeeded or not.
      \sa providerAlreadyExists(), updateProvider(), removeProvider(), getProviders() and getProviderByCNPJ()
    */
    bool createNewProvider(Provider *provider);

    /*!
    Updates a provider from database.
      \param provider The provider to be updated.
      \return Returns if it is succeeded or not.
      \sa providerAlreadyExists(), createNewProvider(), removeProvider(), getProviders() and getProviderByCNPJ()
    */
    bool updateProvider(Provider *provider);

    /*!
    Removes a provider from database.
      \param cnpj The Provider's CNPJ.
      \return Returns if it is succeeded or not.
      \sa providerAlreadyExists(), createNewProvider(), updateProvider(), getProviders() and getProviderByCNPJ()
    */
    bool removeProvider(QString cnpj);

    /*!
    Get a provider by its CNPJ.
      \param cnpj The provider's CNPJ.
      \return Returns the provider object associated with the given CNPJ.
      \sa providerAlreadyExists(), createNewProvider(), updateProvider(), removeProvider() and getProviders()
    */
    Provider *getProviderByCNPJ(QString cnpj);

    /*!
    This method returns all the providers that were previously stored at database.
      \return Returns all stored providers.
      \sa providerAlreadyExists(), createNewProvider(), updateProvider(), removeProvider() and getProviderByCNPJ()
    */
    QList<Provider*> *getProviders();

    //================ PRODUCT CATEGORIES ===================
    /*!
    Check if the name belongs to a product category that is already stored at database.
      \param name The Product Categories' name.
      \return Returns if it is already stored at database.
      \sa createNewProductCategory(), updateProductCategory(), removeProductCategory(), getProductCategoryById() and getProductCategories()
    */
    bool productCategoryAlreadyExists(QString name);

    /*!
    Stores a new product category at database.
      \param productCategory The new product category.
      \return Returns if it is succeeded or not.
      \sa productCategoryAlreadyExists(), updateProductCategory(), removeProductCategory(), getProductCategoryById() and getProductCategories()
    */
    bool createNewProductCategory(ProductCategory *productCategory);

    /*!
    Updates a product category from database.
      \param productCategory The product category to be updated.
      \return Returns if it is succeeded or not.
      \sa productCategoryAlreadyExists(), createNewProductCategory(), removeProductCategory(), getProductCategoryById() and getProductCategories()
    */
    bool updateProductCategory(ProductCategory *productCategory);

    /*!
    Removes a product category from database.
      \param id The product category id.
      \return Returns if it is succeeded or not.
      \sa productCategoryAlreadyExists(), createNewProductCategory(), updateProductCategory(), getProductCategoryById() and getProductCategories()
    */
    bool removeProductCategory(int id);

    /*!
    Get a product category by its id.
      \param id The product category id.
      \return Returns the product category object associated with the given id.
      \sa productCategoryAlreadyExists(), createNewProductCategory(), updateProductCategory(), removeProductCategory() and getProductCategories()
    */
    ProductCategory *getProductCategoryById(int id);

    /*!
    This method returns all the product categories that were previously stored at database.
      \return Returns all stored product categories.
      \sa productCategoryAlreadyExists(), createNewProductCategory(), updateProductCategory(), removeProductCategory() and getProductCategoryById()
    */
    QList<ProductCategory*> *getProductCategories();

    //================ PRODUCTS ===================
    /*!
    Check if the code belongs to a product that is already stored at database.
      \param code The Product's code.
      \return Returns if it is already stored at database.
      \sa createNewProduct(), createNewProduct(), updateProduct(), removeProduct(), getProductByCode(), getProducts() and getProductsQuantityByCode()
    */
    bool productAlreadyExists(QString code);

    /*!
    Check if the bar code belongs to a product that is already stored at database.
      \param barCode The Product's bar code.
      \return Returns if it is already stored at database.
      \sa productAlreadyExists(), createNewProduct(), updateProduct(), removeProduct(), getProductByCode(), getProducts() and getProductsQuantityByCode()
    */
    bool barCodeAlreadyExists(QString barCode);

    /*!
    Stores a new product at database.
      \param product The new product.
      \return Returns if it is succeeded or not.
      \sa productAlreadyExists(), barCodeAlreadyExists(), updateProduct(), removeProduct(), getProductByCode(), getProducts() and getProductsQuantityByCode()
    */
    bool createNewProduct(Product *product);

    /*!
    Updates a product from database.
      \param code The code whose product will be updated.
      \param product The product to be updated.
      \return Returns if it is succeeded or not.
      \sa productAlreadyExists(), barCodeAlreadyExists(), createNewProduct(), removeProduct(), getProductByCode(), getProducts() and getProductsQuantityByCode()
    */
    bool updateProduct(QString code, Product *product);

    /*!
    Removes a product from database.
      \param code The product code.
      \return Returns if it is succeeded or not.
      \sa productAlreadyExists(), barCodeAlreadyExists(), createNewProduct(), updateProduct(), getProductByCode(), getProducts() and getProductsQuantityByCode()
    */
    bool removeProduct(QString code);

    /*!
    Get a product by its code.
      \param code The product code.
      \return Returns the product object associated with the given code.
      \sa productAlreadyExists(), barCodeAlreadyExists(), createNewProduct(), updateProduct(), removeProduct(), getProducts() and getProductsQuantityByCode()
    */
    Product *getProductByCode(QString code);

    /*!
    This method returns all the products that were previously stored at database.
      \return Returns all stored products.
      \sa productAlreadyExists(), barCodeAlreadyExists(), createNewProduct(), updateProduct(), removeProduct(), getProductByCode() and getProductsQuantityByCode()
    */
    QList<Product*> *getProducts();

    /*!
    Get products quantity by its code.
      \param code The product code.
      \return Returns the products quantity associated with the given code.
      \sa productAlreadyExists(), barCodeAlreadyExists(), createNewProduct(), updateProduct(), removeProduct(), getProductByCode and getProducts()
    */
    int getProductsQuantityByCode(QString code);

    //=========== ENTERPRISE CUSTOMERS =============
    /*!
    Check if the cnpj belongs to a enterprise customer that is already stored at database.
      \param cnpj The Enterprise Customer's CNPJ.
      \return Returns if it is already stored at database.
      \sa createNewEnterpriseCustomer(), updateEnterpriseCustomer(), removeEnterpriseCustomer(), getEnterpriseCustomers() and getEnterpriseCustomerByCNPJ()
    */
    bool enterpriseCustomerAlreadyExists(QString cnpj);

    /*!
    Stores a new enterprise customer at database.
      \param enterpriseCustomer The new enterprise customer.
      \return Returns if it is succeeded or not.
      \sa enterpriseCustomerAlreadyExists(), updateEnterpriseCustomer(), removeEnterpriseCustomer(), getEnterpriseCustomers() and getEnterpriseCustomerByCNPJ()
    */
    bool createNewEnterpriseCustomer(EnterpriseCustomer *enterpriseCustomer);

    /*!
    Updates a enterprise customer from database.
      \param enterpriseCustomer The enterprise customer to be updated.
      \return Returns if it is succeeded or not.
      \sa enterpriseCustomerAlreadyExists(), createNewEnterpriseCustomer(), removeEnterpriseCustomer(), getEnterpriseCustomers() and getEnterpriseCustomerByCNPJ()
    */
    bool updateEnterpriseCustomer(EnterpriseCustomer *enterpriseCustomer);

    /*!
    Removes a enterprise customer from database.
      \param cnpj The enterprise customer's CNPJ.
      \return Returns if it is succeeded or not.
      \sa enterpriseCustomerAlreadyExists(), createNewEnterpriseCustomer(), updateEnterpriseCustomer(), getEnterpriseCustomers() and getEnterpriseCustomerByCNPJ()
    */
    bool removeEnterpriseCustomer(QString cnpj);

    /*!
    Get a enterprise customer by its CNPJ.
      \param cnpj The enterprise customer's CNPJ.
      \return Returns the enterprise customer object associated with the given CNPJ.
      \sa enterpriseCustomerAlreadyExists(), createNewEnterpriseCustomer(), updateEnterpriseCustomer(), removeEnterpriseCustomer() and getEnterpriseCustomers()
    */
    EnterpriseCustomer *getEnterpriseCustomerByCNPJ(QString cnpj);

    /*!
    This method returns all the enterprise customers that were previously stored at database.
      \return Returns all stored enterprise customers.
      \sa enterpriseCustomerAlreadyExists(), createNewEnterpriseCustomer(), updateEnterpriseCustomer(), removeEnterpriseCustomer() and getEnterpriseCustomerByCNPJ()
    */
    QList<EnterpriseCustomer*> *getEnterpriseCustomers();

    //=========== PHYSICAL CUSTOMERS =============
    /*!
    Check if the cpf belongs to a physical customer that is already stored at database.
      \param cpf The Physical Customer's CPF.
      \return Returns if it is already stored at database.
      \sa createNewPhysicalCustomer(), updatePhysicalCustomer(), removePhysicalCustomer(), getPhysicalCustomers() and getPhysicalCustomerByCPF()
    */
    bool physicalCustomerAlreadyExists(QString cpf);

    /*!
    Stores a new physical customer at database.
      \param physicalCustomer The new physical customer.
      \return Returns if it is succeeded or not.
      \sa physicalCustomerAlreadyExists(), updatePhysicalCustomer(), removePhysicalCustomer(), getPhysicalCustomers() and getPhysicalCustomerByCPF()
    */
    bool createNewPhysicalCustomer(PhysicalCustomer *physicalCustomer);

    /*!
    Updates a physical customer from database.
      \param physicalCustomer The physical customer to be updated.
      \return Returns if it is succeeded or not.
      \sa physicalCustomerAlreadyExists(), createNewPhysicalCustomer(), removePhysicalCustomer(), getPhysicalCustomers() and getPhysicalCustomerByCPF()
    */
    bool updatePhysicalCustomer(PhysicalCustomer *physicalCustomer);

    /*!
    Removes a physical customer from database.
      \param cpf The physical customer's CPF.
      \return Returns if it is succeeded or not.
      \sa physicalCustomerAlreadyExists(), createNewPhysicalCustomer(), updatePhysicalCustomer(), getPhysicalCustomers() and getPhysicalCustomerByCPF()
    */
    bool removePhysicalCustomer(QString cpf);

    /*!
    Get a physical customer by its CPF.
      \param cpf The physical customer's CPF.
      \return Returns the physical customer object associated with the given CPF.
      \sa physicalCustomerAlreadyExists(), createNewPhysicalCustomer(), updatePhysicalCustomer(), removePhysicalCustomer() and getPhysicalCustomers()
    */
    PhysicalCustomer *getPhysicalCustomerByCPF(QString cpf);

    /*!
    This method returns all the physical customers that were previously stored at database.
      \return Returns all stored physical customers.
      \sa physicalCustomerAlreadyExists(), createNewPhysicalCustomer(), updatePhysicalCustomer(), removePhysicalCustomer() and getPhysicalCustomerByCPF()
    */
    QList<PhysicalCustomer*> *getPhysicalCustomers();

    //================ STOCK UNITS ===================
    /*!
    Check if the name belongs to a stock unit that is already stored at database.
      \param name The stock units' name.
      \return Returns if it is already stored at database.
      \sa createNewStockUnit(), updateStockUnit(), removeStockUnit(), getStockUnitById() and getStockUnits()
    */
    bool stockUnitAlreadyExists(QString name);

    /*!
    Stores a new stock unit at database.
      \param stockUnit The new stock unit.
      \return Returns if it is succeeded or not.
      \sa stockUnitAlreadyExists(), updateStockUnit(), removeStockUnit(), getStockUnitById() and getStockUnits()
    */
    bool createNewStockUnit(StockUnit *stockUnit);

    /*!
    Updates a stock unit from database.
      \param stockUnit The stock unit to be updated.
      \return Returns if it is succeeded or not.
      \sa stockUnitAlreadyExists(), createNewStockUnit(), removeStockUnit(), getStockUnitById() and getStockUnits()
    */
    bool updateStockUnit(StockUnit *stockUnit);

    /*!
    Removes a stock unit from database.
      \param id The stock unit id.
      \return Returns if it is succeeded or not.
      \sa stockUnitAlreadyExists(), createNewStockUnit(), updateStockUnit(), getStockUnitById() and getStockUnits()
    */
    bool removeStockUnit(int id);

    /*!
    Get a stock unit by its id.
      \param id The stock unit id.
      \return Returns the stock unit object associated with the given id.
      \sa stockUnitAlreadyExists(), createNewStockUnit(), updateStockUnit(), removeStockUnit() and getStockUnits()
    */
    StockUnit *getStockUnitById(int id);

    /*!
    This method returns all the stock units that were previously stored at database.
      \return Returns all stored stock units.
      \sa stockUnitAlreadyExists(), createNewStockUnit(), updateStockUnit(), removeStockUnit() and getStockUnitById()
    */
    QList<StockUnit*> *getStockUnits();

    //================ PRODUCT ORIGINS ===================
    /*!
    Check if the name belongs to a product origin that is already stored at database.
      \param code The Product Origins' code.
      \return Returns if it is already stored at database.
      \sa createNewProductOrigin(), updateProductOrigin(), removeProductOrigin(), getProductOriginByCode() and getProductOrigins()
    */
    bool productOriginAlreadyExists(QString code);

    /*!
    Stores a new product origin at database.
      \param productOrigin The new product origin.
      \return Returns if it is succeeded or not.
      \sa productOriginAlreadyExists(), updateProductOrigin(), removeProductOrigin(), getProductOriginByCode() and getProductOrigins()
    */
    bool createNewProductOrigin(ProductOrigin *productOrigin);

    /*!
    Updates a product origin from database.
      \param code The code whose product origin will be updated.
      \param productOrigin The product origin to be updated.
      \return Returns if it is succeeded or not.
      \sa productOriginAlreadyExists(), createNewProductOrigin(), removeProductOrigin(), getProductOriginByCode() and getProductOrigins()
    */
    bool updateProductOrigin(QString code, ProductOrigin *productOrigin);

    /*!
    Removes a product origin from database.
      \param code The product origin code.
      \return Returns if it is succeeded or not.
      \sa productOriginAlreadyExists(), createNewProductOrigin(), updateProductOrigin(), getProductOriginByCode() and getProductOrigins()
    */
    bool removeProductOrigin(QString code);

    /*!
    Get a product origin by its code.
      \param code The product origin code.
      \return Returns the product origin object associated with the given code.
      \sa productOriginAlreadyExists(), createNewProductOrigin(), updateProductOrigin(), removeProductOrigin() and getProductOrigins()
    */
    ProductOrigin *getProductOriginByCode(QString code);

    /*!
    This method returns all the product origins that were previously stored at database.
      \return Returns all stored product origins.
      \sa productOriginAlreadyExists(), createNewProductOrigin(), updateProductOrigin(), removeProductOrigin() and getProductOriginByCode()
    */
    QList<ProductOrigin*> *getProductOrigins();

    //================ CST ICMS ===================
    /*!
    Check if the name belongs to a cst icms that is already stored at database.
      \param code The cst icms' code.
      \return Returns if it is already stored at database.
      \sa createNewCstIcms(), updateCstIcms(), removeCstIcms(), getCstIcmsByCode() and getCstIcmss()
    */
    bool cstIcmsAlreadyExists(QString code);

    /*!
    Stores a new cst icms at database.
      \param cstIcms The new cst icms.
      \return Returns if it is succeeded or not.
      \sa cstIcmsAlreadyExists(), updateCstIcms(), removeCstIcms(), getCstIcmsByCode() and getCstIcmss()
    */
    bool createNewCstIcms(CstIcms *cstIcms);

    /*!
    Updates a cst icms from database.
      \param code The code whose cst icms will be updated.
      \param cstIcms The cst icms to be updated.
      \return Returns if it is succeeded or not.
      \sa cstIcmsAlreadyExists(), createNewCstIcms(), removeCstIcms(), getCstIcmsByCode() and getCstIcmss()
    */
    bool updateCstIcms(QString code, CstIcms *cstIcms);

    /*!
    Removes a cst icms from database.
      \param code The cst icms code.
      \return Returns if it is succeeded or not.
      \sa cstIcmsAlreadyExists(), createNewCstIcms(), updateCstIcms(), getCstIcmsByCode() and getCstIcmss()
    */
    bool removeCstIcms(QString code);

    /*!
    Get a cst icms by its code.
      \param code The cst icms code.
      \return Returns the cst icms object associated with the given code.
      \sa cstIcmsAlreadyExists(), createNewCstIcms(), updateCstIcms(), removeCstIcms() and getCstIcmss()
    */
    CstIcms *getCstIcmsByCode(QString code);

    /*!
    This method returns all the cst icms that were previously stored at database.
      \return Returns all stored cst icms.
      \sa cstIcmsAlreadyExists(), createNewCstIcms(), updateCstIcms(), removeCstIcms() and getCstIcmsByCode()
    */
    QList<CstIcms*> *getCstIcmss();

    //================ CST IPI ===================
    /*!
    Check if the name belongs to a cst ipi that is already stored at database.
      \param code The cst ipi's code.
      \return Returns if it is already stored at database.
      \sa createNewCstIpi(), updateCstIpi(), removeCstIpi(), getCstIpiByCode() and getCstIpis()
    */
    bool cstIpiAlreadyExists(QString code);

    /*!
    Stores a new cst ipi at database.
      \param cstIpi The new cst ipi.
      \return Returns if it is succeeded or not.
      \sa cstIpiAlreadyExists(), updateCstIpi(), removeCstIpi(), getCstIpiByCode() and getCstIpis()
    */
    bool createNewCstIpi(CstIpi *cstIpi);

    /*!
    Updates a cst ipi from database.
      \param code The code whose cst ipi will be updated.
      \param cstIpi The cst ipi to be updated.
      \return Returns if it is succeeded or not.
      \sa cstIpiAlreadyExists(), createNewCstIpi(), removeCstIpi(), getCstIpiByCode() and getCstIpis()
    */
    bool updateCstIpi(QString code, CstIpi *cstIpi);

    /*!
    Removes a cst ipi from database.
      \param code The cst ipi code.
      \return Returns if it is succeeded or not.
      \sa cstIpiAlreadyExists(), createNewCstIpi(), updateCstIpi(), getCstIpiByCode() and getCstIpis()
    */
    bool removeCstIpi(QString code);

    /*!
    Get a cst ipi by its code.
      \param code The cst ipi code.
      \return Returns the cst ipi object associated with the given code.
      \sa cstIpiAlreadyExists(), createNewCstIpi(), updateCstIpi(), removeCstIpi() and getCstIpis()
    */
    CstIpi *getCstIpiByCode(QString code);

    /*!
    This method returns all the cst ipis that were previously stored at database.
      \return Returns all stored cst ipi.
      \sa cstIpiAlreadyExists(), createNewCstIpi(), updateCstIpi(), removeCstIpi() and getCstIpiByCode()
    */
    QList<CstIpi*> *getCstIpis();

    //================ CST PIS ===================
    /*!
    Check if the name belongs to a cst pis that is already stored at database.
      \param code The cst pis' code.
      \return Returns if it is already stored at database.
      \sa createNewCstPis(), updateCstPis(), removeCstPis(), getCstPisByCode() and getCstPiss()
    */
    bool cstPisAlreadyExists(QString code);

    /*!
    Stores a new cst pis at database.
      \param cstPis The new cst pis.
      \return Returns if it is succeeded or not.
      \sa cstPisAlreadyExists(), updateCstPis(), removeCstPis(), getCstPisByCode() and getCstPiss()
    */
    bool createNewCstPis(CstPis *cstPis);

    /*!
    Updates a cst pis from database.
      \param code The code whose cst pis will be updated.
      \param cstPis The cst pis to be updated.
      \return Returns if it is succeeded or not.
      \sa cstPisAlreadyExists(), createNewCstPis(), removeCstPis(), getCstPisByCode() and getCstPiss()
    */
    bool updateCstPis(QString code, CstPis *cstPis);

    /*!
    Removes a cst pis from database.
      \param code The cst pis code.
      \return Returns if it is succeeded or not.
      \sa cstPisAlreadyExists(), createNewCstPis(), updateCstPis(), getCstPisByCode() and getCstPiss()
    */
    bool removeCstPis(QString code);

    /*!
    Get a cst pis by its code.
      \param code The cst pis code.
      \return Returns the cst pis object associated with the given code.
      \sa cstPisAlreadyExists(), createNewCstPis(), updateCstPis(), removeCstPis() and getCstPiss()
    */
    CstPis *getCstPisByCode(QString code);

    /*!
    This method returns all the cst pis that were previously stored at database.
      \return Returns all stored cst pis.
      \sa cstPisAlreadyExists(), createNewCstPis(), updateCstPis(), removeCstPis() and getCstPisByCode()
    */
    QList<CstPis*> *getCstPiss();

    //================ CST COFINS ===================
    /*!
    Check if the name belongs to a cst cofins that is already stored at database.
      \param code The cst cofins' code.
      \return Returns if it is already stored at database.
      \sa createNewCstCofins(), updateCstCofins(), removeCstCofins(), getCstCofinsByCode() and getCstCofinss()
    */
    bool cstCofinsAlreadyExists(QString code);

    /*!
    Stores a new cst cofins at database.
      \param cstCofins The new cst cofins.
      \return Returns if it is succeeded or not.
      \sa cstCofinsAlreadyExists(), updateCstCofins(), removeCstCofins(), getCstCofinsByCode() and getCstCofinss()
    */
    bool createNewCstCofins(CstCofins *cstCofins);

    /*!
    Updates a cst cofins from database.
      \param code The code whose cst cofins will be updated.
      \param cstCofins The cst cofins to be updated.
      \return Returns if it is succeeded or not.
      \sa cstCofinsAlreadyExists(), createNewCstCofins(), removeCstCofins(), getCstCofinsByCode() and getCstCofinss()
    */
    bool updateCstCofins(QString code, CstCofins *cstCofins);

    /*!
    Removes a cst cofins from database.
      \param code The cst cofins code.
      \return Returns if it is succeeded or not.
      \sa cstCofinsAlreadyExists(), createNewCstCofins(), updateCstCofins(), getCstCofinsByCode() and getCstCofinss()
    */
    bool removeCstCofins(QString code);

    /*!
    Get a cst cofins by its code.
      \param code The cst cofins code.
      \return Returns the cst cofins object associated with the given code.
      \sa cstCofinsAlreadyExists(), createNewCstCofins(), updateCstCofins(), removeCstCofins() and getCstCofinss()
    */
    CstCofins *getCstCofinsByCode(QString code);

    /*!
    This method returns all the cst cofins that were previously stored at database.
      \return Returns all stored cst cofins.
      \sa cstCofinsAlreadyExists(), createNewCstCofins(), updateCstCofins(), removeCstCofins() and getCstCofinsByCode()
    */
    QList<CstCofins*> *getCstCofinss();

    //================ TAX RATES ===================
    /*!
    Check if the name belongs to a tax rate that is already stored at database.
      \param name The tax rate's name.
      \return Returns if it is already stored at database.
      \sa createNewTaxRate(), updateTaxRate(), removeTaxRate(), getTaxRateByName() and getTaxRates()
    */
    bool taxRateAlreadyExists(QString name);

    /*!
    Stores a new tax rate at database.
      \param taxRate The new tax rate.
      \return Returns if it is succeeded or not.
      \sa taxRateAlreadyExists(), updateTaxRate(), removeTaxRate(), getTaxRateByName() and getTaxRates()
    */
    bool createNewTaxRate(TaxRate *taxRate);

    /*!
    Updates a tax rate from database.
      \param name The name whose tax rate will be updated.
      \param taxRate The tax rate to be updated.
      \return Returns if it is succeeded or not.
      \sa taxRateAlreadyExists(), createNewTaxRate(), removeTaxRate(), getTaxRateByName() and getTaxRates()
    */
    bool updateTaxRate(QString name, TaxRate *taxRate);

    /*!
    Removes a tax rate from database.
      \param name The tax rate name.
      \return Returns if it is succeeded or not.
      \sa taxRateAlreadyExists(), createNewTaxRate(), updateTaxRate(), getTaxRateByName() and getTaxRates()
    */
    bool removeTaxRate(QString name);

    /*!
    Get a tax rate by its name.
      \param name The tax rate name.
      \return Returns the tax rate object associated with the given name.
      \sa taxRateAlreadyExists(), createNewTaxRate(), updateTaxRate(), removeTaxRate() and getTaxRates()
    */
    TaxRate *getTaxRateByName(QString name);

    /*!
    This method returns all the tax rates that were previously stored at database.
      \return Returns all stored tax rates.
      \sa taxRateAlreadyExists(), createNewTaxRate(), updateTaxRate(), removeTaxRate() and getTaxRateByName()
    */
    QList<TaxRate*> *getTaxRates();

    //================ CFOP ===================
    /*!
    Check if the cfop belongs to a cfop that is already stored at database.
      \param cfop The cfop's cfop.
      \return Returns if it is already stored at database.
      \sa createNewCfop(), updateCfop(), removeCfop(), getCfopByCfop() and getCfops()
    */
    bool cfopAlreadyExists(QString cfop);

    /*!
    Stores a new cfop at database.
      \param cfopObj The new cfop.
      \return Returns if it is succeeded or not.
      \sa cfopAlreadyExists(), updateCfop(), removeCfop(), getCfopByCfop() and getCfops()
    */
    bool createNewCfop(Cfop *cfopObj);

    /*!
    Updates a cfop from database.
      \param cfop The cfop whose cfop will be updated.
      \param cfopObj The cfop to be updated.
      \return Returns if it is succeeded or not.
      \sa cfopAlreadyExists(), createNewCfop(), removeCfop(), getCfopByCfop() and getCfops()
    */
    bool updateCfop(QString cfop, Cfop *cfopObj);

    /*!
    Removes a cfop from database.
      \param cfop The cfop cfop.
      \return Returns if it is succeeded or not.
      \sa cfopAlreadyExists(), createNewCfop(), updateCfop(), getCfopByCfop() and getCfops()
    */
    bool removeCfop(QString cfop);

    /*!
    Get a cfop by its cfop.
      \param cfop The cfop cfop.
      \return Returns the cfop object associated with the given cfop.
      \sa cfopAlreadyExists(), createNewCfop(), updateCfop(), removeCfop() and getCfops()
    */
    Cfop *getCfopByCfop(QString cfop);

    /*!
    This method returns all the cfops that were previously stored at database.
      \return Returns all stored cfops.
      \sa cfopAlreadyExists(), createNewCfop(), updateCfop(), removeCfop() and getCfopByCfop()
    */
    QList<Cfop*> *getCfops();

    //================ PRICE ===================
    /*!
    Check if the pair product-store belongs to a price that is already stored at database.
      \param id The id of the price.
      \param productCode The product code of the price.
      \param storeCnpj The store where the price is defined.
      \return Returns if it is already stored at database.
      \sa priceNameAlreadyExists(), createNewPrice(), updatePrice(), removePrice(), getPriceById(), getPriceByProductCode() and getPrices()
    */
    bool priceAlreadyExists(int id, QString productCode, QString storeCnpj);

    /*!
    Check if the name belongs to a price that is already stored at database.
      \param id The id of the price.
      \param name The name of the price.
      \return Returns if it is already stored at database.
      \sa priceAlreadyExists(), createNewPrice(), updatePrice(), removePrice(), getPriceById(), getPriceByProductCode() and getPrices()
    */
    bool priceNameAlreadyExists(int id, QString name);

    /*!
    Stores a new price at database.
      \param price The new price.
      \return Returns if it is succeeded or not.
      \sa priceAlreadyExists(), priceNameAlreadyExists(), updatePrice(), removePrice(), getPriceById(), getPriceByProductCode() and getPrices()
    */
    bool createNewPrice(Price *price);

    /*!
    Updates a price from database.
      \param price The price to be updated.
      \return Returns if it is succeeded or not.
      \sa priceAlreadyExists(), priceNameAlreadyExists(), createNewPrice(), removePrice(), getPriceById(), getPriceByProductCode() and getPrices()
    */
    bool updatePrice(Price *price);

    /*!
    Removes a price from database.
      \param id The price id.
      \return Returns if it is succeeded or not.
      \sa priceAlreadyExists(), priceNameAlreadyExists(), createNewPrice(), updatePrice(), getPriceById(), getPriceByProductCode() and getPrices()
    */
    bool removePrice(int id);

    /*!
    Get a price by its id.
      \param id The price id.
      \return Returns the price object associated with the given id.
      \sa priceAlreadyExists(), priceNameAlreadyExists(), createNewPrice(), updatePrice(), removePrice(), getPriceByProductCode() and getPrices()
    */
    Price *getPriceById(int id);

    /*!
    Get a price by its name.
      \param name The price name.
      \return Returns the price object associated with the given name.
      \sa priceAlreadyExists(), priceNameAlreadyExists(), createNewPrice(), updatePrice(), removePrice(), getPriceById() and getPrices()
    */
    Price *getPriceByName(QString name);

    Price *getPriceByProductCodeAndStoreCnpj(QString productCode, QString storeCnpj);

    /*!
    This method returns all the prices that were previously stored at database.
      \return Returns all stored prices.
      \sa priceAlreadyExists(), priceNameAlreadyExists(), createNewPrice(), updatePrice(), removePrice(), getPriceById() and getPriceByProductCode()
    */
    QList<Price*> *getPrices();

    //=========== STORES =============
    /*!
    Check if the cnpj belongs to a store that is already stored at database.
      \param cnpj The Store's CNPJ.
      \return Returns if it is already stored at database.
      \sa createNewStore(), updateStore(), removeStore(), getStores() and getStoreByCNPJ()
    */
    bool storeAlreadyExists(QString cnpj);

    /*!
    Stores a new store at database.
      \param store The new store.
      \return Returns if it is succeeded or not.
      \sa storeAlreadyExists(), updateStore(), removeStore(), getStores() and getStoreByCNPJ()
    */
    bool createNewStore(Store *store);

    /*!
    Updates a store from database.
      \param store The store to be updated.
      \return Returns if it is succeeded or not.
      \sa storeAlreadyExists(), createNewStore(), removeStore(), getStores() and getStoreByCNPJ()
    */
    bool updateStore(Store *store);

    /*!
    Removes a store from database.
      \param cnpj The Store's CNPJ.
      \return Returns if it is succeeded or not.
      \sa storeAlreadyExists(), createNewStore(), updateStore(), getStores() and getStoreByCNPJ()
    */
    bool removeStore(QString cnpj);

    /*!
    Get a store by its CNPJ.
      \param cnpj The store's CNPJ.
      \return Returns the store object associated with the given CNPJ.
      \sa storeAlreadyExists(), createNewStore(), updateStore(), removeStore() and getStores()
    */
    Store *getStoreByCNPJ(QString cnpj);

    /*!
    This method returns all the stores that were previously stored at database.
      \return Returns all stored stores.
      \sa storeAlreadyExists(), createNewStore(), updateStore(), removeStore() and getStoreByCNPJ()
    */
    QList<Store*> *getStores();

    /*!
    Check if the receipt belongs to a sale order that is already stored at database.
      \param receipt The Sale order's receipt.
      \return Returns if it is already stored at database.
      \sa storeSalesOrder(), removeSalesOrder(), getSalesOrderById(), getSalesOrderByReceipt(), getSalesOrdersByDateRange() and getSalesOrders()
    */
    bool salesOrderAlreadyExists(QString receipt);

    /*!
    Stores a new sale order at database.
      \param salesOrder The new sale order.
      \return Returns if it is succeeded or not.
      \sa salesOrderAlreadyExists(), removeSalesOrder(), getSalesOrderById(), getSalesOrderByReceipt(), getSalesOrdersByDateRange() and getSalesOrders()
    */
    bool storeSalesOrder(SalesOrder *salesOrder);

//    /*!
//    Updates a sale order from database.
//      \param salesOrder The sale order to be updated.
//      \return Returns if it is succeeded or not.
//      \sa salesOrderAlreadyExists(), storeSalesOrder(), removeSalesOrder(), getSalesOrderById(), getSalesOrderByReceipt(), getSalesOrdersByDateRange() and getSalesOrders()
//    */
//    bool updateSalesOrder(SalesOrder *salesOrder);

    /*!
    Removes a sale order from database.
      \param id The Sales Order's id.
      \param removeRelatedEntries If it needs to remove the related entries.
      \return Returns if it is succeeded or not.
      \sa salesOrderAlreadyExists(), storeSalesOrder(), getSalesOrderById(), getSalesOrderByReceipt(), getSalesOrdersByDateRange() and getSalesOrders()
    */
    bool removeSalesOrder(int id, bool removeRelatedEntries = false);

    /*!
    Get a sales order by its id.
      \param id The sales order's id.
      \return Returns the sales order object associated with the given id.
      \sa salesOrderAlreadyExists(), storeSalesOrder(), removeSalesOrder(), getSalesOrderByReceipt(), getSalesOrdersByDateRange() and getSalesOrders()
    */
    SalesOrder *getSalesOrderById(int id);

    /*!
    Get a sales order by its receipt.
      \param receipt The sales order receipt.
      \return Returns the sales order object associated with the given id.
      \sa salesOrderAlreadyExists(), storeSalesOrder(), removeSalesOrder(), getSalesOrderById(), getSalesOrdersByDateRange() and getSalesOrders()
    */
    SalesOrder *getSalesOrderByReceipt(QString receipt);

    /*!
    Get all sales orders by a date range.
      \param startDate The start SalesOrder's date range.
      \param endDate The end SalesOrder's date range.
      \return Returns the sales orders objects associated with the given date range.
      \sa salesOrderAlreadyExists(), storeSalesOrder(), removeSalesOrder(), getSalesOrderById(), getSalesOrderByReceipt() and getSalesOrders()
    */
    QList<SalesOrder*> *getSalesOrdersByDateRange(QDateTime startDate, QDateTime endDate);

    /*!
    This method returns all the sales orders that were previously stored at database.
      \return Returns all stored sales orders.
      \sa salesOrderAlreadyExists(), storeSalesOrder(), removeSalesOrder(), getSalesOrderById(), getSalesOrderByReceipt() and getSalesOrdersByDateRange()
    */
    QList<SalesOrder*> *getSalesOrders();

    QList<SaleProductOrder*> *getSaleProductOrdersBySalesOrderId(int id);

    SaleProductOrder *getSaleProductOrderById(int id);

    //==

    /*!
    Check if the receipt belongs to a purchase order that is already stored at database.
      \param receipt The Purchase order's receipt.
      \param providerId The provider who sent the receipt.
      \return Returns if it is already stored at database.
      \sa storePurchasesOrder(), removePurchasesOrder(), getPurchasesOrderById(), getPurchasesOrderByReceipt(), getPurchasesOrdersByDateRange() and getPurchasesOrders()
    */
    bool purchasesOrderAlreadyExists(QString receipt, QString providerId);

    /*!
    Stores a new purchase order at database.
      \param purchasesOrder The new purchase order.
      \return Returns if it is succeeded or not.
      \sa purchasesOrderAlreadyExists(), removePurchasesOrder(), getPurchasesOrderById(), getPurchasesOrderByReceipt(), getPurchasesOrdersByDateRange() and getPurchasesOrders()
    */
    bool storePurchasesOrder(PurchasesOrder *purchasesOrder);

    /*!
    Removes a purchase order from database.
      \param id The Purchases Order's id.
      \param removeRelatedEntries If it needs to remove the related entries.
      \return Returns if it is succeeded or not.
      \sa purchasesOrderAlreadyExists(), storePurchasesOrder(), getPurchasesOrderById(), getPurchasesOrderByReceipt(), getPurchasesOrdersByDateRange() and getPurchasesOrders()
    */
    bool removePurchasesOrder(int id, bool removeRelatedEntries = false);

    /*!
    Get a purchases order by its id.
      \param id The purchases order's id.
      \return Returns the purchases order object associated with the given id.
      \sa purchasesOrderAlreadyExists(), storePurchasesOrder(), removePurchasesOrder(), getPurchasesOrderByReceipt(), getPurchasesOrdersByDateRange() and getPurchasesOrders()
    */
    PurchasesOrder *getPurchasesOrderById(int id);

    /*!
    Get a purchases order by its receipt.
      \param receipt The purchases order receipt.
      \return Returns the purchases order object associated with the given id.
      \sa purchasesOrderAlreadyExists(), storePurchasesOrder(), removePurchasesOrder(), getPurchasesOrderById(), getPurchasesOrdersByDateRange() and getPurchasesOrders()
    */
    PurchasesOrder *getPurchasesOrderByReceipt(QString receipt);

    /*!
    Get all purchases orders by a date range.
      \param startDate The start PurchasesOrder's date range.
      \param endDate The end PurchasesOrder's date range.
      \return Returns the purchases orders objects associated with the given date range.
      \sa purchasesOrderAlreadyExists(), storePurchasesOrder(), removePurchasesOrder(), getPurchasesOrderById(), getPurchasesOrderByReceipt() and getPurchasesOrders()
    */
    QList<PurchasesOrder*> *getPurchasesOrdersByDateRange(QDateTime startDate, QDateTime endDate);

    /*!
    This method returns all the purchases orders that were previously stored at database.
      \return Returns all stored purchases orders.
      \sa purchasesOrderAlreadyExists(), storePurchasesOrder(), removePurchasesOrder(), getPurchasesOrderById(), getPurchasesOrderByReceipt() and getPurchasesOrdersByDateRange()
    */
    QList<PurchasesOrder*> *getPurchasesOrders();

    QList<PurchaseProductOrder*> *getPurchaseProductOrdersByPurchasesOrderId(int id);

    PurchaseProductOrder *getPurchaseProductOrderById(int id);

    //============== ACCOUNT ===============
    /*!
    Check if the code belongs to an account that is already stored at database.
      \param code The Account's code.
      \return Returns if it is already stored at database.
      \sa createNewAccount(), updateAccount(), removeAccount(), getAccounts(), getAccountByCode() and getAccountTypes()
    */
    bool accountAlreadyExists(QString code);

    /*!
    Stores a new account at database.
      \param account The account to be added.
      \param isAnalytic If the account is analytic or not.
      \return Returns if it is succeeded or not.
      \sa accountAlreadyExists(), updateAccount(), removeAccount(), getAccounts(), getAccountByCode() and getAccountTypes()
    */
    bool createNewAccount(Account *account, bool isAnalytic);

    /*!
    Updates an account from database.
      \param code The Account's original code.
      \param account The account to be updated.
      \param isAnalytic If the account is analytic or not.
      \sa accountAlreadyExists(), createNewAccount(), removeAccount(), getAccounts(), getAccountByCode() and getAccountTypes()
    */
    bool updateAccount(QString code, Account *account, bool isAnalytic);

    /*!
    Removes an account from database.
      \param code The Account's code.
      \return Returns if it is succeeded or not.
      \sa accountAlreadyExists(), createNewAccount(), updateAccount(), getAccounts(), getAccountByCode() and getAccountTypes()
    */
    bool removeAccount(QString code);

    /*!
    Get an account by its code.
      \param code The Account's code.
      \return Returns the account object associated with the given code.
      \sa accountAlreadyExists(), createNewAccount(), updateAccount(), getAccounts(), removeAccount() and getAccountTypes()
    */
    Account *getAccountByCode(QString code);

    /*!
    This method returns all the accounts that were previously stored at database.
      \param filter Accounts filtered by a pattern. This is an optional parameter.
      \return Returns all stored accounts.
      \sa accountAlreadyExists(), createNewAccount(), updateAccount(), removeAccount(), getAccountByCode() and getAccountTypes()
    */
    QList<Account*> *getAccounts(QString filter="");

    /*!
    This method returns all the account's roles that were previously stored at database.
      \return Returns all stored account's roles.
      \sa accountAlreadyExists(), createNewAccount(), updateAccount(), removeAccount(), getAccountByCode() and getAccounts()
    */
    QStringList *getAccountTypes();

    //================ HISTORY ===================
    /*!
    Check if the name belongs to a history that is already stored at database.
      \param name The history's name.
      \return Returns if it is already stored at database.
      \sa createNewHistory(), updateHistory(), removeHistory(), getHistoryById() and getHistories()
    */
    bool historyAlreadyExists(QString name);

    /*!
    Stores a new history at database.
      \param history The new history.
      \return Returns if it is succeeded or not.
      \sa historyAlreadyExists(), updateHistory(), removeHistory(), getHistoryById() and getHistories()
    */
    bool createNewHistory(History *history);

    /*!
    Updates a history from database.
      \param history The history to be updated.
      \return Returns if it is succeeded or not.
      \sa historyAlreadyExists(), createNewHistory(), removeHistory(), getHistoryById() and getHistories()
    */
    bool updateHistory(History *history);

    /*!
    Removes a history from database.
      \param id The history id.
      \return Returns if it is succeeded or not.
      \sa historyAlreadyExists(), createNewHistory(), updateHistory(), getHistoryById() and getHistories()
    */
    bool removeHistory(int id);

    /*!
    Get a history by its id.
      \param id The history id.
      \return Returns the history object associated with the given id.
      \sa historyAlreadyExists(), createNewHistory(), updateHistory(), removeHistory() and getHistories()
    */
    History *getHistoryById(int id);

    /*!
    This method returns all the histories that were previously stored at database.
      \return Returns all stored histories.
      \sa historyAlreadyExists(), createNewHistory(), updateHistory(), removeHistory() and getHistoryById()
    */
    QList<History*> *getHistories();

    //================ ENTRY ===================
    /*!
    Stores a new entry at database.
      \param entry The new entry.
      \return Returns if it is succeeded or not.
      \sa updateEntry(), removeEntry(), getEntryById(), getEntriesBetweenDates() and getEntries()
    */
    bool createNewEntry(Entry *entry);

    /*!
    Updates an entry from database.
      \param entry The entry to be updated.
      \return Returns if it is succeeded or not.
      \sa createNewEntry(), removeEntry(), getEntryById(), getEntriesBetweenDates() and getEntries()
    */
    bool updateEntry(Entry *entry);

    /*!
    Removes an entry from database.
      \param id The entry id.
      \return Returns if it is succeeded or not.
      \sa createNewEntry(), updateEntry(), getEntryById(), getEntriesBetweenDates() and getEntries()
    */
    bool removeEntry(int id);

    /*!
    Get an entry by its id.
      \param id The entry id.
      \return Returns the entry object associated with the given id.
      \sa createNewEntry(), updateEntry(), removeEntry(), getEntriesBetweenDates() and getEntries()
    */
    Entry *getEntryById(int id);

    /*!
    Get all entries between two dates.
      \param startDate The first date.
      \param endDate The second date.
      \return Returns all entries between two given dates.
      \sa createNewEntry(), updateEntry(), removeEntry(), getEntryById() and getEntries()
    */
    QList<Entry*> *getEntriesBetweenDates(QDateTime startDate, QDateTime endDate);

    /*!
    Get all entries.
      \return Returns all entries.
      \sa createNewEntry(), updateEntry(), removeEntry(), getEntryById() and getEntriesBetweenDates()
    */
    QList<Entry*> *getEntries();

protected:

    //! Default constructor.
    /*!
    * Create a new instance of DatabaseController.
    */
    explicit DatabaseController(QObject *parent = 0);

private:

    void defineDefaultStore();
//    void defineMainAccounts();
//    void defineMainHistories();

    /*!
    This method returns the parameters to connect to database.
      \return Returns an uri to connect to database.
    */
    QString readDBConfig();

    //! Database Controller instance.
    /*!
      This is the unique instance of database controller. It's part of singleton pattern.
    */
    static DatabaseController *pInstance;

#ifdef DB_POSTGRESQL
    PGconn *con;
#endif
    bool conOpen;
    Store *defaultStore;
//    //QString customerAccount;
//    QString providerAccount;
//    //QString cashAccount;
//    QString icmsToRecoverAccount;
//    QString pisToRecoverAccount;
//    QString cofinsToRecoverAccount;
//    QString productStockAccount;
//    QString debtorSaleAccount;
//    QString creditorSaleAccount;
//    QString icmsInSalesDebtorAccount;
//    QString icmsInSalesCreditorAccount;
//    QString pisInSalesDebtorAccount;
//    QString pisInSalesCreditorAccount;
//    QString cofinsInSalesDebtorAccount;
//    QString cofinsInSalesCreditorAccount;
//    QString goodsShippingDebtorAccount;
//    QString goodsShippingCreditorAccount;
//    int buyProductHistoryId;
//    int taxCreditHistoryId;
//    int saleHistoryId;
//    int icmsInSalesHistoryId;
//    int pisInSalesHistoryId;
//    int cofinsInSalesHistoryId;
//    int goodsShippingHistoryId;

signals:

public slots:

};

#endif // DATABASECONTROLLER_H
