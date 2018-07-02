#ifndef IMAINWINDOW_H
#define IMAINWINDOW_H

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

class AddSalesOrderView;
class AddPurchasesOrderView;

//!  Main Window Interface
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This interface tells what methods must be implemented on all MainWindow's.
*/
class IMainWindow
{
public:

    //! Adds the form, that will handle the user management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "Manage User" context menu, inside "System" menu.
      There will be placed a child dialog into MDI to allow user mantain user's database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormAddUserToMDI(), removeFormAddUserMDI(), addFormEditUserToMDI() and removeFormEditUserMDI()
    */
    virtual void addFormManageUsersToMDI() = 0;

    //! Adds the form, that will add an user, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add User" button, located at AddUserView form.
      There will be placed a child dialog into MDI to allow the current user to add more users into database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageUsersToMDI() and removeFormAddUserMDI()
    */
    virtual void addFormAddUserToMDI() = 0;

    //! Removes the form, that adds an user, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more users into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageUsersToMDI() and addFormAddUserToMDI()
    */
    virtual void removeFormAddUserMDI() = 0;

    //! Adds the form, that will edit an user, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit User" button, located at AddUserView form.
      There will be placed a child dialog into MDI to allow the current user to edit users from database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageUsersToMDI() and removeFormEditUserMDI()
    */
    virtual void addFormEditUserToMDI(User *user) = 0;


    //! Removes the form, that edits an user, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit users into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageUsersToMDI() and addFormEditUserToMDI()
    */
    virtual void removeFormEditUserMDI() = 0;


    //! Sets the user currently logged in
    /*!
      This is an abstract method that will get called, when an user logs in successfully.
    */
    virtual void setUser(User *user) = 0;

    //! Adds the form, that will handle the manufacturers management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "manufacturers" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain manufacturer's database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddManufacturerToMDI(), removeFormAddManufacturerMDI(), addFormEditManufacturerToMDI() and removeFormEditManufacturerMDI()
    */
    virtual void addFormManageManufacturersToMDI() = 0;

    //! Adds the form, that will add a manufacturer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Manufacturer" button, located at AddManufacturerView form.
      There will be placed a child dialog into MDI to allow the user to add more manufacturers into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageManufacturersToMDI() and removeFormAddManufacturerMDI()
    */
    virtual void addFormAddManufacturerToMDI() = 0;

    //! Removes the form, that adds a manufacturer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more manufacturers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageManufacturersToMDI() and addFormAddManufacturerToMDI()
    */
    virtual void removeFormAddManufacturerMDI() = 0;

    //! Adds the form, that will edit a manufacturer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit manufacturer" button, located at AddManufacturerView form.
      There will be placed a child dialog into MDI to allow the current user to edit manufacturers from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageManufacturersToMDI() and removeFormEditManufacturerMDI()
    */
    virtual void addFormEditManufacturerToMDI(Manufacturer *manufacturer) = 0;

    //! Removes the form, that edits a manufacturer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit manufacturers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageManufacturersToMDI() and addFormEditManufacturerToMDI()
    */
    virtual void removeFormEditManufacturerMDI() = 0;

    //! Adds the form, that will handle the providers management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "providers" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain provider's database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddProviderToMDI(), removeFormAddProviderMDI(), addFormEditProviderToMDI() and removeFormEditProviderMDI()
    */
    virtual void addFormManageProvidersToMDI() = 0;

    //! Adds the form, that will add a provider, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Provider" button, located at AddProviderView form.
      There will be placed a child dialog into MDI to allow the user to add more providers into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProvidersToMDI() and removeFormAddProviderMDI()
    */
    virtual void addFormAddProviderToMDI() = 0;

    //! Removes the form, that adds a provider, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more providers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProvidersToMDI() and addFormAddProviderToMDI()
    */
    virtual void removeFormAddProviderMDI() = 0;

    //! Adds the form, that will edit a provider, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit provider" button, located at AddProviderView form.
      There will be placed a child dialog into MDI to allow the current user to edit providers from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProvidersToMDI() and removeFormEditProviderMDI()
    */
    virtual void addFormEditProviderToMDI(Provider *provider) = 0;

    //! Removes the form, that edits a provider, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit providers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProvidersToMDI() and addFormEditProviderToMDI()
    */
    virtual void removeFormEditProviderMDI() = 0;

    //! Adds the form, that will handle the product categories management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "product categories" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain product category database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddProductCategoryToMDI(), removeFormAddProductCategoryMDI(), addFormEditProductCategoryToMDI() and removeFormEditProductCategoryMDI()
    */
    virtual void addFormManageProductCategoriesToMDI() = 0;

    //! Adds the form, that will add a product category, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add product category" button, located at AddProductCategoryView form.
      There will be placed a child dialog into MDI to allow the user to add more product categories into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductCategoriesToMDI() and removeFormAddProductCategoryMDI()
    */
    virtual void addFormAddProductCategoryToMDI() = 0;

    //! Removes the form, that adds a product category, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more product categories into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductCategoriesToMDI() and addFormAddProductCategoryToMDI()
    */
    virtual void removeFormAddProductCategoryMDI() = 0;

    //! Adds the form, that will edit a product category, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit product category" button, located at AddProductCategoryView form.
      There will be placed a child dialog into MDI to allow the current user to edit product categories from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductCategoriesToMDI() and removeFormEditProductCategoryMDI()
    */
    virtual void addFormEditProductCategoryToMDI(ProductCategory *productCategory) = 0;

    //! Removes the form, that edits a product category, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit product categories into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductCategoriesToMDI() and addFormEditProductCategoryToMDI()
    */
    virtual void removeFormEditProductCategoryMDI() = 0;

    //! Adds the form, that will handle the products management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "products" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain product database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddProductToMDI(), removeFormAddProductMDI(), addFormEditProductToMDI() and removeFormEditProductMDI()
    */
    virtual void addFormManageProductsToMDI() = 0;

    //! Adds the form, that will add a product, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add product" button, located at AddProductView form.
      There will be placed a child dialog into MDI to allow the user to add more products into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductsToMDI() and removeFormAddProductMDI()
    */
    virtual void addFormAddProductToMDI() = 0;

    //! Removes the form, that adds a product, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more products into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductsToMDI() and addFormAddProductToMDI()
    */
    virtual void removeFormAddProductMDI() = 0;

    //! Adds the form, that will edit a product, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit product" button, located at AddProductView form.
      There will be placed a child dialog into MDI to allow the current user to edit products from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductsToMDI() and removeFormEditProductMDI()
    */
    virtual void addFormEditProductToMDI(Product *product) = 0;

    //! Removes the form, that edits a product, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit products into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductsToMDI() and addFormEditProductToMDI()
    */
    virtual void removeFormEditProductMDI() = 0;

    //! Adds the form, that will handle the customers management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "Canage Customers" context menu, inside "Customers" menu.
      There will be placed a child dialog into MDI to allow user mantain customer database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddEnterpriseCustomerToMDI(), removeFormAddEnterpriseCustomerMDI(), addFormEditEnterpriseCustomerToMDI(), removeFormEditEnterpriseCustomerMDI(), addFormAddPhysicalCustomerToMDI(), removeFormAddPhysicalCustomerMDI(), addFormEditPhysicalCustomerToMDI() and removeFormEditPhysicalCustomerMDI()
    */
    virtual void addFormManageCustomersToMDI() = 0;

    //! Adds the form, that will add a enterprise customer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add enterprise customer" button, located at AddEnterpriseCustomerView form.
      There will be placed a child dialog into MDI to allow the user to add more enterprise customers into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and removeFormAddEnterpriseCustomerMDI()
    */
    virtual void addFormAddEnterpriseCustomerToMDI() = 0;

    //! Removes the form, that adds a enterprise customer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more enterprise customers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and addFormAddEnterpriseCustomerToMDI()
    */
    virtual void removeFormAddEnterpriseCustomerMDI() = 0;

    //! Adds the form, that will edit a enterprise customer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit enterprise customer" button, located at AddEnterpriseCustomerView form.
      There will be placed a child dialog into MDI to allow the current user to edit enterprise customers from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and removeFormEditEnterpriseCustomerMDI()
    */
    virtual void addFormEditEnterpriseCustomerToMDI(EnterpriseCustomer *enterpriseCustomer) = 0;

    //! Removes the form, that edits a enterprise customer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit enterprise customers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and addFormEditEnterpriseCustomerToMDI()
    */
    virtual void removeFormEditEnterpriseCustomerMDI() = 0;

    //! Adds the form, that will add a physical customer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add physical customer" button, located at AddPhysicalCustomerView form.
      There will be placed a child dialog into MDI to allow the user to add more physical customers into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and removeFormAddPhysicalCustomerMDI()
    */
    virtual void addFormAddPhysicalCustomerToMDI() = 0;

    //! Removes the form, that adds a physical customer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more physical customers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and addFormAddPhysicalCustomerToMDI()
    */
    virtual void removeFormAddPhysicalCustomerMDI() = 0;

    //! Adds the form, that will edit a physical customer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit physical customer" button, located at AddPhysicalCustomerView form.
      There will be placed a child dialog into MDI to allow the current user to edit physical customers from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and removeFormEditPhysicalCustomerMDI()
    */
    virtual void addFormEditPhysicalCustomerToMDI(PhysicalCustomer *physicalCustomer) = 0;

    //! Removes the form, that edits a physical customer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit physical customers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and addFormEditPhysicalCustomerToMDI()
    */
    virtual void removeFormEditPhysicalCustomerMDI() = 0;

    //! Adds the form, that will handle the stock units management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "stock units" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain stock unit database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddStockUnitToMDI(), removeFormAddStockUnitMDI(), addFormEditStockUnitToMDI() and removeFormEditStockUnitMDI()
    */
    virtual void addFormManageStockUnitsToMDI() = 0;

    //! Adds the form, that will add a stock unit, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add stock unit" button, located at AddStockUnitView form.
      There will be placed a child dialog into MDI to allow the user to add more stock units into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageStockUnitsToMDI() and removeFormAddStockUnitMDI()
    */
    virtual void addFormAddStockUnitToMDI() = 0;

    //! Removes the form, that adds a stock unit, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more stock units into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageStockUnitsToMDI() and addFormAddStockUnitToMDI()
    */
    virtual void removeFormAddStockUnitMDI() = 0;

    //! Adds the form, that will edit a stock unit, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit stock unit" button, located at AddStockUnitView form.
      There will be placed a child dialog into MDI to allow the current user to edit stock units from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageStockUnitsToMDI() and removeFormEditStockUnitMDI()
    */
    virtual void addFormEditStockUnitToMDI(StockUnit *stockUnit) = 0;

    //! Removes the form, that edits a stock unit, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit stock units into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageStockUnitsToMDI() and addFormEditStockUnitToMDI()
    */
    virtual void removeFormEditStockUnitMDI() = 0;

    //! Adds the form, that will handle the product origins management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "product origins" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain product origin database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddProductOriginToMDI(), removeFormAddProductOriginMDI(), addFormEditProductOriginToMDI() and removeFormEditProductOriginMDI()
    */
    virtual void addFormManageProductOriginsToMDI() = 0;

    //! Adds the form, that will add a product origin, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add product origin" button, located at AddProductOriginView form.
      There will be placed a child dialog into MDI to allow the user to add more product origins into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductOriginsToMDI() and removeFormAddProductOriginMDI()
    */
    virtual void addFormAddProductOriginToMDI() = 0;

    //! Removes the form, that adds a product origin, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more product origins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductOriginsToMDI() and addFormAddProductOriginToMDI()
    */
    virtual void removeFormAddProductOriginMDI() = 0;

    //! Adds the form, that will edit a product origin, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit product origin" button, located at AddProductOriginView form.
      There will be placed a child dialog into MDI to allow the current user to edit product origins from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductOriginsToMDI() and removeFormEditProductOriginMDI()
    */
    virtual void addFormEditProductOriginToMDI(ProductOrigin *productOrigin) = 0;

    //! Removes the form, that edits a product origin, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit product origins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductOriginsToMDI() and addFormEditProductOriginToMDI()
    */
    virtual void removeFormEditProductOriginMDI() = 0;

    //! Adds the form, that will handle the icms management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "icms" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain icms database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddCstIcmsToMDI(), removeFormAddCstIcmsMDI(), addFormEditCstIcmsToMDI() and removeFormEditCstIcmsMDI()
    */
    virtual void addFormManageCstIcmssToMDI() = 0;

    //! Adds the form, that will add a icms, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add icms" button, located at AddCstIcmsView form.
      There will be placed a child dialog into MDI to allow the user to add more icms into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIcmssToMDI() and removeFormAddCstIcmsMDI()
    */
    virtual void addFormAddCstIcmsToMDI() = 0;

    //! Removes the form, that adds a icms, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more icms into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIcmssToMDI() and addFormAddCstIcmsToMDI()
    */
    virtual void removeFormAddCstIcmsMDI() = 0;

    //! Adds the form, that will edit a icms, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit icms" button, located at AddCstIcmsView form.
      There will be placed a child dialog into MDI to allow the current user to edit icms from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIcmssToMDI() and removeFormEditCstIcmsMDI()
    */
    virtual void addFormEditCstIcmsToMDI(CstIcms *cstIcms) = 0;

    //! Removes the form, that edits a icms, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit icms into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIcmssToMDI() and addFormEditCstIcmsToMDI()
    */
    virtual void removeFormEditCstIcmsMDI() = 0;

    //! Adds the form, that will handle the ipi management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "ipi" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain ipi database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddCstIpiToMDI(), removeFormAddCstIpiMDI(), addFormEditCstIpiToMDI() and removeFormEditCstIpiMDI()
    */
    virtual void addFormManageCstIpisToMDI() = 0;

    //! Adds the form, that will add a ipi, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add ipi" button, located at AddCstIpiView form.
      There will be placed a child dialog into MDI to allow the user to add more ipi into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIpisToMDI() and removeFormAddCstIpiMDI()
    */
    virtual void addFormAddCstIpiToMDI() = 0;

    //! Removes the form, that adds a ipi, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more ipi into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIpisToMDI() and addFormAddCstIpiToMDI()
    */
    virtual void removeFormAddCstIpiMDI() = 0;

    //! Adds the form, that will edit a ipi, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit ipi" button, located at AddCstIpiView form.
      There will be placed a child dialog into MDI to allow the current user to edit ipi from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIpisToMDI() and removeFormEditCstIpiMDI()
    */
    virtual void addFormEditCstIpiToMDI(CstIpi *cstIpi) = 0;

    //! Removes the form, that edits a ipi, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit ipi into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIpisToMDI() and addFormEditCstIpiToMDI()
    */
    virtual void removeFormEditCstIpiMDI() = 0;

    //! Adds the form, that will handle the ipi management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "pis" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain pis database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddCstPisToMDI(), removeFormAddCstPisMDI(), addFormEditCstPisToMDI() and removeFormEditCstPisMDI()
    */
    virtual void addFormManageCstPissToMDI() = 0;

    //! Adds the form, that will add a pis, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add pis" button, located at AddCstPisView form.
      There will be placed a child dialog into MDI to allow the user to add more pis into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstPissToMDI() and removeFormAddCstPisMDI()
    */
    virtual void addFormAddCstPisToMDI() = 0;

    //! Removes the form, that adds a pis, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more pis into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstPissToMDI() and addFormAddCstPisToMDI()
    */
    virtual void removeFormAddCstPisMDI() = 0;

    //! Adds the form, that will edit a pis, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit pis" button, located at AddCstPisView form.
      There will be placed a child dialog into MDI to allow the current user to edit pis from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstPissToMDI() and removeFormEditCstPisMDI()
    */
    virtual void addFormEditCstPisToMDI(CstPis *cstPis) = 0;

    //! Removes the form, that edits a pis, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit pis into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstPissToMDI() and addFormEditCstPisToMDI()
    */
    virtual void removeFormEditCstPisMDI() = 0;

    //! Adds the form, that will handle the cofins management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "cofins" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain cofins database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddCstCofinsToMDI(), removeFormAddCstCofinsMDI(), addFormEditCstCofinsToMDI() and removeFormEditCstCofinsMDI()
    */
    virtual void addFormManageCstCofinssToMDI() = 0;

    //! Adds the form, that will add a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add cofins" button, located at AddCstCofinsView form.
      There will be placed a child dialog into MDI to allow the user to add more cofins into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstCofinssToMDI() and removeFormAddCstCofinsMDI()
    */
    virtual void addFormAddCstCofinsToMDI() = 0;

    //! Removes the form, that adds a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstCofinssToMDI() and addFormAddCstCofinsToMDI()
    */
    virtual void removeFormAddCstCofinsMDI() = 0;

    //! Adds the form, that will edit a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit cofins" button, located at AddCstCofinsView form.
      There will be placed a child dialog into MDI to allow the current user to edit cofins from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstCofinssToMDI() and removeFormEditCstCofinsMDI()
    */
    virtual void addFormEditCstCofinsToMDI(CstCofins *cstCofins) = 0;

    //! Removes the form, that edits a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstCofinssToMDI() and addFormEditCstCofinsToMDI()
    */
    virtual void removeFormEditCstCofinsMDI() = 0;

    //! Adds the form, that will handle the cofins management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "cofins" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain cofins database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddTaxRateToMDI(), removeFormAddTaxRateMDI(), addFormEditTaxRateToMDI() and removeFormEditTaxRateMDI()
    */
    virtual void addFormManageTaxRatesToMDI() = 0;

    //! Adds the form, that will add a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add cofins" button, located at AddTaxRateView form.
      There will be placed a child dialog into MDI to allow the user to add more cofins into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageTaxRatesToMDI() and removeFormAddTaxRateMDI()
    */
    virtual void addFormAddTaxRateToMDI() = 0;

    //! Removes the form, that adds a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageTaxRatesToMDI() and addFormAddTaxRateToMDI()
    */
    virtual void removeFormAddTaxRateMDI() = 0;

    //! Adds the form, that will edit a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit cofins" button, located at AddTaxRateView form.
      There will be placed a child dialog into MDI to allow the current user to edit cofins from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageTaxRatesToMDI() and removeFormEditTaxRateMDI()
    */
    virtual void addFormEditTaxRateToMDI(TaxRate *taxRate) = 0;

    //! Removes the form, that edits a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageTaxRatesToMDI() and addFormEditTaxRateToMDI()
    */
    virtual void removeFormEditTaxRateMDI() = 0;

    //! Adds the form, that will handle the cofins management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "cofins" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain cofins database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddCfopToMDI(), removeFormAddCfopMDI(), addFormEditCfopToMDI() and removeFormEditCfopMDI()
    */
    virtual void addFormManageCfopsToMDI() = 0;

    //! Adds the form, that will add a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add cofins" button, located at AddCfopView form.
      There will be placed a child dialog into MDI to allow the user to add more cofins into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCfopsToMDI() and removeFormAddCfopMDI()
    */
    virtual void addFormAddCfopToMDI() = 0;

    //! Removes the form, that adds a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCfopsToMDI() and addFormAddCfopToMDI()
    */
    virtual void removeFormAddCfopMDI() = 0;

    //! Adds the form, that will edit a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit cofins" button, located at AddCfopView form.
      There will be placed a child dialog into MDI to allow the current user to edit cofins from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCfopsToMDI() and removeFormEditCfopMDI()
    */
    virtual void addFormEditCfopToMDI(Cfop *cfop) = 0;

    //! Removes the form, that edits a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCfopsToMDI() and addFormEditCfopToMDI()
    */
    virtual void removeFormEditCfopMDI() = 0;

    //! Adds the form, that will handle the cofins management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "prices" context menu.
      There will be placed a child dialog into MDI to allow user mantain prices database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddPriceToMDI(), removeFormAddPriceMDI(), addFormEditPriceToMDI() and removeFormEditPriceMDI()
    */
    virtual void addFormManagePricesToMDI() = 0;

    //! Adds the form, that will add a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add price" button, located at PricesListView form.
      There will be placed a child dialog into MDI to allow the user to add more prices into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManagePricesToMDI() and removeFormAddPriceMDI()
    */
    virtual void addFormAddPriceToMDI() = 0;

    //! Removes the form, that adds a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more prices into database, will be removed from MDI.
      Only Managers,Supervisors and Stockers are allowed to get into this option.
      \sa addFormManagePricesToMDI() and addFormAddPriceToMDI()
    */
    virtual void removeFormAddPriceMDI() = 0;

    //! Adds the form, that will edit a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit price" button, located at PricesListView form.
      There will be placed a child dialog into MDI to allow the current user to edit price from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManagePricesToMDI() and removeFormEditPriceMDI()
    */
    virtual void addFormEditPriceToMDI(Price *price) = 0;

    //! Removes the form, that edits a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit price into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManagePricesToMDI() and addFormEditPriceToMDI()
    */
    virtual void removeFormEditPriceMDI() = 0;

    //! Adds the form, that will handle the stores management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "stores" context menu, inside "System" menu.
      There will be placed a child dialog into MDI to allow user mantain store's database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormAddStoreToMDI(), removeFormAddStoreMDI(), addFormEditStoreToMDI() and removeFormEditStoreMDI()
    */
    virtual void addFormManageStoresToMDI() = 0;

    //! Adds the form, that will add a store, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Store" button, located at StoresListView form.
      There will be placed a child dialog into MDI to allow the user to add more stores into database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageStoresToMDI() and removeFormAddStoreMDI()
    */
    virtual void addFormAddStoreToMDI() = 0;

    //! Removes the form, that adds a store, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more stores into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageStoresToMDI() and addFormAddStoreToMDI()
    */
    virtual void removeFormAddStoreMDI() = 0;

    //! Adds the form, that will edit a store, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit store" button, located at StoresListView form.
      There will be placed a child dialog into MDI to allow the current user to edit stores from database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageStoresToMDI() and removeFormEditStoreMDI()
    */
    virtual void addFormEditStoreToMDI(Store *store) = 0;

    //! Removes the form, that edits a store, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit stores into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageStoresToMDI() and addFormEditStoreToMDI()
    */
    virtual void removeFormEditStoreMDI() = 0;

    //! Adds the form, that will handle the sales orders management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "sales orders" context menu, inside "Sales" menu.
      There will be placed a child dialog into MDI to allow user mantain sales order's database.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormAddSalesOrderToMDI(), removeFormAddSalesOrderMDI(), addFormEditSalesOrderToMDI() and removeFormEditSalesOrderMDI()
    */
    virtual void addFormManageSalesOrdersToMDI() = 0;

    //! Adds the form, that will add a sales order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Sales Order" button, located at SalesOrdersListView form.
      There will be placed a child dialog into MDI to allow the user to add more sales orders into database.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormManageSalesOrdersToMDI() and removeFormAddSalesOrderMDI()
    */
    virtual void addFormAddSalesOrderToMDI() = 0;

    //! Removes the form, that adds a sales order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more sales orders into database, will be removed from MDI.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormManageSalesOrdersToMDI() and addFormAddSalesOrderToMDI()
    */
    virtual void removeFormAddSalesOrderMDI() = 0;

    //! Adds the form, that will edit a sales order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit sales order" button, located at SalesOrdersListView form.
      There will be placed a child dialog into MDI to allow the current user to edit sales orders from database.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormManageSalesOrdersToMDI() and removeFormEditSalesOrderMDI()
    */
    virtual void addFormEditSalesOrderToMDI(SalesOrder *salesOrder) = 0;

    //! Removes the form, that edits a sales order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit sales orders into database, will be removed from MDI.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormManageSalesOrdersToMDI() and addFormEditSalesOrderToMDI()
    */
    virtual void removeFormEditSalesOrderMDI() = 0;

    //! Adds the form, that will add a sale product order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Sale Product Order" button, located at AddSalesOrderView form.
      There will be placed a child dialog into MDI to allow the user to add more sale product orders into database.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa removeFormAddSaleProductOrderToMDI()
    */
    virtual void addFormAddSaleProductOrderToMDI(AddSalesOrderView *addSalesOrderView) = 0;

    //! Removes the form, that adds a sale product order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more sale product orders into database, will be removed from MDI.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormAddSaleProductOrderToMDI()
    */
    virtual void removeFormAddSaleProductOrderMDI() = 0;

    //! Adds the form, that will edit a sale product order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit sale product order order" button, located at AddSalesOrderView form.
      There will be placed a child dialog into MDI to allow the current user to edit sale product orders from database.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa removeFormEditSaleProductOrderMDI()
    */
    virtual void addFormEditSaleProductOrderToMDI(SaleProductOrder *saleProductOrder, AddSalesOrderView *addSalesOrderView) = 0;

    //! Removes the form, that edits a sales order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit sales orders into database, will be removed from MDI.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormEditSaleProductOrderToMDI()
    */
    virtual void removeFormEditSaleProductOrderMDI() = 0;

    //==

    //! Adds the form, that will handle the purchases orders management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "purchases orders" context menu, inside "Sales" menu.
      There will be placed a child dialog into MDI to allow user mantain purchases order's database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormAddPurchasesOrderToMDI(), removeFormAddPurchasesOrderMDI(), addFormEditPurchasesOrderToMDI() and removeFormEditPurchasesOrderMDI()
    */
    virtual void addFormManagePurchasesOrdersToMDI() = 0;

    //! Adds the form, that will add a purchases order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Purchases Order" button, located at PurchasesOrdersListView form.
      There will be placed a child dialog into MDI to allow the user to add more purchases orders into database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManagePurchasesOrdersToMDI() and removeFormAddPurchasesOrderMDI()
    */
    virtual void addFormAddPurchasesOrderToMDI() = 0;

    //! Removes the form, that adds a purchases order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more purchases orders into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManagePurchasesOrdersToMDI() and addFormAddPurchasesOrderToMDI()
    */
    virtual void removeFormAddPurchasesOrderMDI() = 0;

    //! Adds the form, that will edit a purchases order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit purchases order" button, located at PurchasesOrdersListView form.
      There will be placed a child dialog into MDI to allow the current user to edit purchases orders from database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManagePurchasesOrdersToMDI() and removeFormEditPurchasesOrderMDI()
    */
    virtual void addFormEditPurchasesOrderToMDI(PurchasesOrder *purchasesOrder) = 0;

    //! Removes the form, that edits a purchases order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit purchases orders into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManagePurchasesOrdersToMDI() and addFormEditPurchasesOrderToMDI()
    */
    virtual void removeFormEditPurchasesOrderMDI() = 0;

    //! Adds the form, that will add a purchase product order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Purchase Product Order" button, located at AddPurchasesOrderView form.
      There will be placed a child dialog into MDI to allow the user to add more purchase product orders into database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa removeFormAddPurchaseProductOrderToMDI()
    */
    virtual void addFormAddPurchaseProductOrderToMDI(AddPurchasesOrderView *addPurchasesOrderView) = 0;

    //! Removes the form, that adds a purchase product order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more purchase product orders into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormAddPurchaseProductOrderToMDI()
    */
    virtual void removeFormAddPurchaseProductOrderMDI() = 0;

    //! Adds the form, that will edit a purchase product order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit purchase product order order" button, located at AddPurchasesOrderView form.
      There will be placed a child dialog into MDI to allow the current user to edit purchase product orders from database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa removeFormEditPurchaseProductOrderMDI()
    */
    virtual void addFormEditPurchaseProductOrderToMDI(PurchaseProductOrder *purchaseProductOrder, AddPurchasesOrderView *addPurchasesOrderView) = 0;

    //! Removes the form, that edits a purchases order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit purchases orders into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormEditPurchaseProductOrderToMDI()
    */
    virtual void removeFormEditPurchaseProductOrderMDI() = 0;

    //! Adds the form, that will handle the account management, into MDI area
    /*!
      This is an abstract method that will get called, when an account select "Manage Account" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow account mantain account's database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormAddAccountToMDI(), removeFormAddAccountMDI(), addFormEditAccountToMDI() and removeFormEditAccountMDI()
    */
    virtual void addFormManageAccountsToMDI() = 0;

    //! Adds the form, that will add an account, into MDI area
    /*!
      This is an abstract method that will get called, when an account clicks on "Add Account" button, located at AddAccountView form.
      There will be placed a child dialog into MDI to allow the current account to add more accounts into database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageAccountsToMDI() and removeFormAddAccountMDI()
    */
    virtual void addFormAddAccountToMDI() = 0;

    //! Removes the form, that adds an account, from MDI area
    /*!
      This is an abstract method that will get called, when an account dismisses the dialog.
      The child dialog that allows an account to add more accounts into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageAccountsToMDI() and addFormAddAccountToMDI()
    */
    virtual void removeFormAddAccountMDI() = 0;

    //! Adds the form, that will edit an account, into MDI area
    /*!
      This is an abstract method that will get called, when an account clicks on "Edit Account" button, located at AddAccountView form.
      There will be placed a child dialog into MDI to allow the current account to edit accounts from database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageAccountsToMDI() and removeFormEditAccountMDI()
    */
    virtual void addFormEditAccountToMDI(Account *account) = 0;


    //! Removes the form, that edits an account, from MDI area
    /*!
      This is an abstract method that will get called, when an account dismisses the dialog.
      The child dialog that allows an account to edit accounts into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageAccountsToMDI() and addFormEditAccountToMDI()
    */
    virtual void removeFormEditAccountMDI() = 0;

	//! Adds the form, that will edit a History, into MDI area
    /*!
      This is an abstract method that will get called, when an account clicks on "Edit History" button, located at AddHistoryView form.
      There will be placed a child dialog into MDI to allow the current account to edit Histories from database.
      Only Managers and Supervisors are allowed to get into this option.
    */
	virtual void addFormManageHistoriesToMDI() = 0;

	
    //! Adds the form, that will add a History, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add History" button, located at AddHistoryView form.
      There will be placed a child dialog into MDI to allow the user to add more Histories into database.
      Only Managers and Supervisors are allowed to get into this option.
    */
    virtual void addFormAddHistoryToMDI() = 0;

    //! Removes the form, that adds a History, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more Histories into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
    */
    virtual void removeFormAddHistoryMDI() = 0;

    //! Adds the form, that will edit a History, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit History" button, located at AddHistoryView form.
      There will be placed a child dialog into MDI to allow the current user to edit Histories from database.
      Only Managers and Supervisors are allowed to get into this option.
	*/
    virtual void addFormEditHistoryToMDI(History *history) = 0;

    //! Removes the form, that edits a History, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit Histories into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
    */
    virtual void removeFormEditHistoryMDI() = 0;

	//! Adds the form, that will edit an Entry, into MDI area
    /*!
      This is an abstract method that will get called, when an Entry clicks on "Edit Entry" button, located at AddEntryView form.
      There will be placed a child dialog into MDI to allow the current account to edit Entries from database.
      Only Managers and Supervisors are allowed to get into this option.
    */
	virtual void addFormManageEntriesToMDI() = 0;

    //! Adds the form, that will add an Entry, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Entry" button, located at AddEntryView form.
      There will be placed a child dialog into MDI to allow the user to add more Entries into database.
      Only Managers and Supervisors are allowed to get into this option.
    */
    virtual void addFormAddEntryToMDI() = 0;

    //! Removes the form, that adds an Entry, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more Entries into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
    */
    virtual void removeFormAddEntryMDI() = 0;

    //! Adds the form, that will edit an Entry, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit Entry" button, located at AddEntryView form.
      There will be placed a child dialog into MDI to allow the current user to edit Entries from database.
      Only Managers and Supervisors are allowed to get into this option.
    */
    virtual void addFormEditEntryToMDI(Entry *entry) = 0;

    //! Removes the form, that edits an Entry, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit Entries into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
    */
    virtual void removeFormEditEntryMDI() = 0;


};

#endif // IMAINWINDOW_H
