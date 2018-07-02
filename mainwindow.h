#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

#include "imainwindow.h"
#include "userslistview.h"
#include "adduserview.h"
#include "login.h"
#include "manufacturerslistview.h"
#include "addmanufacturerview.h"
#include "providerslistview.h"
#include "addproviderview.h"
#include "productcategorieslistview.h"
#include "addproductcategoryview.h"
#include "productslistview.h"
#include "addproductview.h"
#include "customerslistview.h"
#include "addenterprisecustomerview.h"
#include "addphysicalcustomerview.h"
#include "stockunitslistview.h"
#include "addstockunitview.h"
#include "productoriginslistview.h"
#include "addproductoriginview.h"
#include "csticmsslistview.h"
#include "addcsticmsview.h"
#include "cstipislistview.h"
#include "addcstipiview.h"
#include "cstipislistview.h"
#include "addcstipiview.h"
#include "cstipislistview.h"
#include "addcstpisview.h"
#include "cstcofinsslistview.h"
#include "addcstcofinsview.h"
#include "taxrateslistview.h"
#include "addtaxrateview.h"
#include "cfopslistview.h"
#include "addcfopview.h"
#include "priceslistview.h"
#include "addpriceview.h"
#include "storeslistview.h"
#include "addstoreview.h"
#include "salesorderslistview.h"
#include "addsalesorderview.h"
#include "addsaleproductorderview.h"
#include "purchasesorderslistview.h"
#include "addpurchasesorderview.h"
#include "addpurchaseproductorderview.h"
#include "accountslistview.h"
#include "addaccountview.h"
#include "historieslistview.h"
#include "addhistoryview.h"
#include "entrieslistview.h"
#include "addentryview.h"

namespace Ui {
    class MainWindow;
}

//!  Main Window
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This is the entry point of the project.
*/
class MainWindow : public QMainWindow, public IMainWindow
{
    Q_OBJECT

public:
    //! Default constructor.
    /*!
    * Create a new instance of MainWindow.
    */
    explicit MainWindow(QWidget *parent = 0);

    //! Destructor.
    /*!
    * Release all resources here.
    */
    ~MainWindow();

public slots:

    //! Adds the form, that will handle the user management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "Manage User" context menu, inside "System" menu.
      There will be placed a child dialog into MDI to allow user mantain user's database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormAddUserToMDI(), addFormEditUserToMDI(), addFormAddUserToMDI() and removeFormAddUserMDI()
    */
    void addFormManageUsersToMDI();


    //! Adds the form, that will add an user, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add User" button, located at AddUserView form.
      There will be placed a child dialog into MDI to allow the current user to add more users into database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageUsersToMDI() and removeFormAddUserMDI()
    */
    void addFormAddUserToMDI();

    //! Removes the form, that adds an user, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more users into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageUsersToMDI() and addFormAddUserToMDI()
    */
    void removeFormAddUserMDI();

    //! Adds the form, that will edit an user, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit User" button, located at AddUserView form.
      There will be placed a child dialog into MDI to allow the current user to edit users from database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageUsersToMDI() and removeFormEditUserMDI()
    */
    void addFormEditUserToMDI(User *user);

    //! Removes the form, that edits an user, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit users into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageUsersToMDI() and addFormEditUserToMDI()
    */
    void removeFormEditUserMDI();


    //! Sets the user currently logged in
    /*!
      This is an abstract method that will get called, when an user logs in successfully.
    */
    void setUser(User *user);

    //! Adds the form, that will handle the manufacturers management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "manufacturers" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain manufacturer's database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddManufacturerToMDI(), removeFormAddManufacturerMDI(), addFormEditManufacturerToMDI() and removeFormEditManufacturerMDI()
    */
    void addFormManageManufacturersToMDI();

    //! Adds the form, that will add a manufacturer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Manufacturer" button, located at AddManufacturerView form.
      There will be placed a child dialog into MDI to allow the user to add more manufacturers into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageManufacturersToMDI() and removeFormAddManufacturerMDI()
    */
    void addFormAddManufacturerToMDI();

    //! Removes the form, that adds a manufacturer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more manufacturers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageManufacturersToMDI() and addFormAddManufacturerToMDI()
    */
    void removeFormAddManufacturerMDI();

    //! Adds the form, that will edit a manufacturer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit manufacturer" button, located at AddManufacturerView form.
      There will be placed a child dialog into MDI to allow the current user to edit manufacturers from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageManufacturersToMDI() and removeFormEditManufacturerMDI()
    */
    void addFormEditManufacturerToMDI(Manufacturer *manufacturer);

    //! Removes the form, that edits a manufacturer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit manufacturers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageManufacturersToMDI() and addFormEditManufacturerToMDI()
    */
    void removeFormEditManufacturerMDI();

    //! Adds the form, that will handle the providers management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "providers" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain provider's database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddProviderToMDI(), removeFormAddProviderMDI(), addFormEditProviderToMDI() and removeFormEditProviderMDI()
    */
    void addFormManageProvidersToMDI();

    //! Adds the form, that will add a provider, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Provider" button, located at AddProviderView form.
      There will be placed a child dialog into MDI to allow the user to add more providers into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProvidersToMDI() and removeFormAddProviderMDI()
    */
    void addFormAddProviderToMDI();

    //! Removes the form, that adds a provider, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more providers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProvidersToMDI() and addFormAddProviderToMDI()
    */
    void removeFormAddProviderMDI();

    //! Adds the form, that will edit a provider, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit provider" button, located at AddProviderView form.
      There will be placed a child dialog into MDI to allow the current user to edit providers from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProvidersToMDI() and removeFormEditProviderMDI()
    */
    void addFormEditProviderToMDI(Provider *provider);

    //! Removes the form, that edits a provider, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit providers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProvidersToMDI() and addFormEditProviderToMDI()
    */
    void removeFormEditProviderMDI();

    //! Adds the form, that will handle the product categories management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "product categories" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain product category database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddProductCategoryToMDI(), removeFormAddProductCategoryMDI(), addFormEditProductCategoryToMDI() and removeFormEditProductCategoryMDI()
    */
    void addFormManageProductCategoriesToMDI();

    //! Adds the form, that will add a product category, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add product category" button, located at AddProductCategoryView form.
      There will be placed a child dialog into MDI to allow the user to add more product categories into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductCategoriesToMDI() and removeFormAddProductCategoryMDI()
    */
    void addFormAddProductCategoryToMDI();

    //! Removes the form, that adds a product category, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more product categories into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductCategoriesToMDI() and addFormAddProductCategoryToMDI()
    */
    void removeFormAddProductCategoryMDI();

    //! Adds the form, that will edit a product category, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit product category" button, located at AddProductCategoryView form.
      There will be placed a child dialog into MDI to allow the current user to edit product categories from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductCategoriesToMDI() and removeFormEditProductCategoryMDI()
    */
    void addFormEditProductCategoryToMDI(ProductCategory *productCategory);

    //! Removes the form, that edits a product category, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit product categories into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductCategoriesToMDI() and addFormEditProductCategoryToMDI()
    */
    void removeFormEditProductCategoryMDI();

    //! Adds the form, that will handle the products management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "products" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain product database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddProductToMDI(), removeFormAddProductMDI(), addFormEditProductToMDI() and removeFormEditProductMDI()
    */
    void addFormManageProductsToMDI();

    //! Adds the form, that will add a product, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add product" button, located at AddProductView form.
      There will be placed a child dialog into MDI to allow the user to add more products into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductsToMDI() and removeFormAddProductMDI()
    */
    void addFormAddProductToMDI();

    //! Removes the form, that adds a product, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more products into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductsToMDI() and addFormAddProductToMDI()
    */
    void removeFormAddProductMDI();

    //! Adds the form, that will edit a product, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit product" button, located at AddProductView form.
      There will be placed a child dialog into MDI to allow the current user to edit products from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductsToMDI() and removeFormEditProductMDI()
    */
    void addFormEditProductToMDI(Product *product);

    //! Removes the form, that edits a product, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit products into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductsToMDI() and addFormEditProductToMDI()
    */
    void removeFormEditProductMDI();

    //! Adds the form, that will handle the customers management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "Canage Customers" context menu, inside "Customers" menu.
      There will be placed a child dialog into MDI to allow user mantain customer database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddEnterpriseCustomerToMDI(), removeFormAddEnterpriseCustomerMDI(), addFormEditEnterpriseCustomerToMDI(), removeFormEditEnterpriseCustomerMDI(), addFormAddPhysicalCustomerToMDI(), removeFormAddPhysicalCustomerMDI(), addFormEditPhysicalCustomerToMDI() and removeFormEditPhysicalCustomerMDI()
    */
    void addFormManageCustomersToMDI();

    //! Adds the form, that will add a enterprise customer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add enterprise customer" button, located at AddEnterpriseCustomerView form.
      There will be placed a child dialog into MDI to allow the user to add more enterprise customers into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and removeFormAddEnterpriseCustomerMDI()
    */
    void addFormAddEnterpriseCustomerToMDI();

    //! Removes the form, that adds a enterprise customer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more enterprise customers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and addFormAddEnterpriseCustomerToMDI()
    */
    void removeFormAddEnterpriseCustomerMDI();

    //! Adds the form, that will edit a enterprise customer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit enterprise customer" button, located at AddEnterpriseCustomerView form.
      There will be placed a child dialog into MDI to allow the current user to edit enterprise customers from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and removeFormEditEnterpriseCustomerMDI()
    */
    void addFormEditEnterpriseCustomerToMDI(EnterpriseCustomer *enterpriseCustomer);

    //! Removes the form, that edits a enterprise customer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit enterprise customers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and addFormEditEnterpriseCustomerToMDI()
    */
    void removeFormEditEnterpriseCustomerMDI();

    //! Adds the form, that will add a physical customer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add physical customer" button, located at AddPhysicalCustomerView form.
      There will be placed a child dialog into MDI to allow the user to add more physical customers into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and removeFormAddPhysicalCustomerMDI()
    */
    void addFormAddPhysicalCustomerToMDI();

    //! Removes the form, that adds a physical customer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more physical customers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and addFormAddPhysicalCustomerToMDI()
    */
    void removeFormAddPhysicalCustomerMDI();

    //! Adds the form, that will edit a physical customer, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit physical customer" button, located at AddPhysicalCustomerView form.
      There will be placed a child dialog into MDI to allow the current user to edit physical customers from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and removeFormEditPhysicalCustomerMDI()
    */
    void addFormEditPhysicalCustomerToMDI(PhysicalCustomer *physicalCustomer);

    //! Removes the form, that edits a physical customer, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit physical customers into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCustomersToMDI() and addFormEditPhysicalCustomerToMDI()
    */
    void removeFormEditPhysicalCustomerMDI();

    //! Adds the form, that will handle the stock units management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "stock units" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain stock unit database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddStockUnitToMDI(), removeFormAddStockUnitMDI(), addFormEditStockUnitToMDI() and removeFormEditStockUnitMDI()
    */
    void addFormManageStockUnitsToMDI();

    //! Adds the form, that will add a stock unit, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add stock unit" button, located at AddStockUnitView form.
      There will be placed a child dialog into MDI to allow the user to add more stock units into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageStockUnitsToMDI() and removeFormAddStockUnitMDI()
    */
    void addFormAddStockUnitToMDI();

    //! Removes the form, that adds a stock unit, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more stock units into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageStockUnitsToMDI() and addFormAddStockUnitToMDI()
    */
    void removeFormAddStockUnitMDI();

    //! Adds the form, that will edit a stock unit, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit stock unit" button, located at AddStockUnitView form.
      There will be placed a child dialog into MDI to allow the current user to edit stock units from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageStockUnitsToMDI() and removeFormEditStockUnitMDI()
    */
    void addFormEditStockUnitToMDI(StockUnit *stockUnit);

    //! Removes the form, that edits a stock unit, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit stock units into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageStockUnitsToMDI() and addFormEditStockUnitToMDI()
    */
    void removeFormEditStockUnitMDI();

    //! Adds the form, that will handle the product origins management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "product origins" context menu, inside "Stock" menu.
      There will be placed a child dialog into MDI to allow user mantain product origin database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddProductOriginToMDI(), removeFormAddProductOriginMDI(), addFormEditProductOriginToMDI() and removeFormEditProductOriginMDI()
    */
    void addFormManageProductOriginsToMDI();

    //! Adds the form, that will add a product origin, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add product origin" button, located at AddProductOriginView form.
      There will be placed a child dialog into MDI to allow the user to add more product origins into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductOriginsToMDI() and removeFormAddProductOriginMDI()
    */
    void addFormAddProductOriginToMDI();

    //! Removes the form, that adds a product origin, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more product origins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductOriginsToMDI() and addFormAddProductOriginToMDI()
    */
    void removeFormAddProductOriginMDI();

    //! Adds the form, that will edit a product origin, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit product origin" button, located at AddProductOriginView form.
      There will be placed a child dialog into MDI to allow the current user to edit product origins from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductOriginsToMDI() and removeFormEditProductOriginMDI()
    */
    void addFormEditProductOriginToMDI(ProductOrigin *productOrigin);

    //! Removes the form, that edits a product origin, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit product origins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageProductOriginsToMDI() and addFormEditProductOriginToMDI()
    */
    void removeFormEditProductOriginMDI();

    //! Adds the form, that will handle the icms management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "icms" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain icms database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddCstIcmsToMDI(), removeFormAddCstIcmsMDI(), addFormEditCstIcmsToMDI() and removeFormEditCstIcmsMDI()
    */
    void addFormManageCstIcmssToMDI();

    //! Adds the form, that will add a icms, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add icms" button, located at AddCstIcmsView form.
      There will be placed a child dialog into MDI to allow the user to add more icms into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIcmssToMDI() and removeFormAddCstIcmsMDI()
    */
    void addFormAddCstIcmsToMDI();

    //! Removes the form, that adds a icms, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more icms into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIcmssToMDI() and addFormAddCstIcmsToMDI()
    */
    void removeFormAddCstIcmsMDI();

    //! Adds the form, that will edit a icms, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit icms" button, located at AddCstIcmsView form.
      There will be placed a child dialog into MDI to allow the current user to edit icms from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIcmssToMDI() and removeFormEditCstIcmsMDI()
    */
    void addFormEditCstIcmsToMDI(CstIcms *cstIcms);

    //! Removes the form, that edits a icms, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit icms into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIcmssToMDI() and addFormEditCstIcmsToMDI()
    */
    void removeFormEditCstIcmsMDI();

    //! Adds the form, that will handle the ipi management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "ipi" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain ipi database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddCstIpiToMDI(), removeFormAddCstIpiMDI(), addFormEditCstIpiToMDI() and removeFormEditCstIpiMDI()
    */
    void addFormManageCstIpisToMDI();

    //! Adds the form, that will add a ipi, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add ipi" button, located at AddCstIpiView form.
      There will be placed a child dialog into MDI to allow the user to add more ipi into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIpisToMDI() and removeFormAddCstIpiMDI()
    */
    void addFormAddCstIpiToMDI();

    //! Removes the form, that adds a ipi, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more ipi into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIpisToMDI() and addFormAddCstIpiToMDI()
    */
    void removeFormAddCstIpiMDI();

    //! Adds the form, that will edit a ipi, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit ipi" button, located at AddCstIpiView form.
      There will be placed a child dialog into MDI to allow the current user to edit ipi from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIpisToMDI() and removeFormEditCstIpiMDI()
    */
    void addFormEditCstIpiToMDI(CstIpi *cstIpi);

    //! Removes the form, that edits a ipi, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit ipi into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstIpisToMDI() and addFormEditCstIpiToMDI()
    */
    void removeFormEditCstIpiMDI();

    //! Adds the form, that will handle the ipi management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "pis" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain pis database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddCstPisToMDI(), removeFormAddCstPisMDI(), addFormEditCstPisToMDI() and removeFormEditCstPisMDI()
    */
    void addFormManageCstPissToMDI();

    //! Adds the form, that will add a pis, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add pis" button, located at AddCstPisView form.
      There will be placed a child dialog into MDI to allow the user to add more pis into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstPissToMDI() and removeFormAddCstPisMDI()
    */
    void addFormAddCstPisToMDI();

    //! Removes the form, that adds a pis, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more pis into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstPissToMDI() and addFormAddCstPisToMDI()
    */
    void removeFormAddCstPisMDI();

    //! Adds the form, that will edit a pis, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit pis" button, located at AddCstPisView form.
      There will be placed a child dialog into MDI to allow the current user to edit pis from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstPissToMDI() and removeFormEditCstPisMDI()
    */
    void addFormEditCstPisToMDI(CstPis *cstPis);

    //! Removes the form, that edits a pis, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit pis into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstPissToMDI() and addFormEditCstPisToMDI()
    */
    void removeFormEditCstPisMDI();

    //! Adds the form, that will handle the cofins management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "cofins" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain cofins database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddCstCofinsToMDI(), removeFormAddCstCofinsMDI(), addFormEditCstCofinsToMDI() and removeFormEditCstCofinsMDI()
    */
    void addFormManageCstCofinssToMDI();

    //! Adds the form, that will add a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add cofins" button, located at AddCstCofinsView form.
      There will be placed a child dialog into MDI to allow the user to add more cofins into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstCofinssToMDI() and removeFormAddCstCofinsMDI()
    */
    void addFormAddCstCofinsToMDI();

    //! Removes the form, that adds a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstCofinssToMDI() and addFormAddCstCofinsToMDI()
    */
    void removeFormAddCstCofinsMDI();

    //! Adds the form, that will edit a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit cofins" button, located at AddCstCofinsView form.
      There will be placed a child dialog into MDI to allow the current user to edit cofins from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstCofinssToMDI() and removeFormEditCstCofinsMDI()
    */
    void addFormEditCstCofinsToMDI(CstCofins *cstCofins);

    //! Removes the form, that edits a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCstCofinssToMDI() and addFormEditCstCofinsToMDI()
    */
    void removeFormEditCstCofinsMDI();

    //! Adds the form, that will handle the cofins management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "cofins" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain cofins database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddTaxRateToMDI(), removeFormAddTaxRateMDI(), addFormEditTaxRateToMDI() and removeFormEditTaxRateMDI()
    */
    void addFormManageTaxRatesToMDI();

    //! Adds the form, that will add a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add cofins" button, located at AddTaxRateView form.
      There will be placed a child dialog into MDI to allow the user to add more cofins into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageTaxRatesToMDI() and removeFormAddTaxRateMDI()
    */
    void addFormAddTaxRateToMDI();

    //! Removes the form, that adds a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageTaxRatesToMDI() and addFormAddTaxRateToMDI()
    */
    void removeFormAddTaxRateMDI();

    //! Adds the form, that will edit a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit cofins" button, located at AddTaxRateView form.
      There will be placed a child dialog into MDI to allow the current user to edit cofins from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageTaxRatesToMDI() and removeFormEditTaxRateMDI()
    */
    void addFormEditTaxRateToMDI(TaxRate *taxRate);

    //! Removes the form, that edits a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageTaxRatesToMDI() and addFormEditTaxRateToMDI()
    */
    void removeFormEditTaxRateMDI();

    //! Adds the form, that will handle the cofins management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "cofins" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow user mantain cofins database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddCfopToMDI(), removeFormAddCfopMDI(), addFormEditCfopToMDI() and removeFormEditCfopMDI()
    */
    void addFormManageCfopsToMDI();

    //! Adds the form, that will add a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add cofins" button, located at AddCfopView form.
      There will be placed a child dialog into MDI to allow the user to add more cofins into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCfopsToMDI() and removeFormAddCfopMDI()
    */
    void addFormAddCfopToMDI();

    //! Removes the form, that adds a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCfopsToMDI() and addFormAddCfopToMDI()
    */
    void removeFormAddCfopMDI();

    //! Adds the form, that will edit a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit cofins" button, located at AddCfopView form.
      There will be placed a child dialog into MDI to allow the current user to edit cofins from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCfopsToMDI() and removeFormEditCfopMDI()
    */
    void addFormEditCfopToMDI(Cfop *cfop);

    //! Removes the form, that edits a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit cofins into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManageCfopsToMDI() and addFormEditCfopToMDI()
    */
    void removeFormEditCfopMDI();

    //! Adds the form, that will handle the cofins management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "prices" context menu.
      There will be placed a child dialog into MDI to allow user mantain prices database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormAddPriceToMDI(), removeFormAddPriceMDI(), addFormEditPriceToMDI() and removeFormEditPriceMDI()
    */
    void addFormManagePricesToMDI();

    //! Adds the form, that will add a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add price" button, located at PricesListView form.
      There will be placed a child dialog into MDI to allow the user to add more prices into database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManagePricesToMDI() and removeFormAddPriceMDI()
    */
    void addFormAddPriceToMDI();

    //! Removes the form, that adds a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more prices into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManagePricesToMDI() and addFormAddPriceToMDI()
    */
    void removeFormAddPriceMDI();

    //! Adds the form, that will edit a cofins, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit price" button, located at PricesListView form.
      There will be placed a child dialog into MDI to allow the current user to edit price from database.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManagePricesToMDI() and removeFormEditPriceMDI()
    */
    void addFormEditPriceToMDI(Price *price);

    //! Removes the form, that edits a cofins, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit price into database, will be removed from MDI.
      Only Managers, Supervisors and Stockers are allowed to get into this option.
      \sa addFormManagePricesToMDI() and addFormEditPriceToMDI()
    */
    void removeFormEditPriceMDI();

    //! Adds the form, that will handle the stores management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "stores" context menu, inside "System" menu.
      There will be placed a child dialog into MDI to allow user mantain store's database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormAddStoreToMDI(), removeFormAddStoreMDI(), addFormEditStoreToMDI() and removeFormEditStoreMDI()
    */
    void addFormManageStoresToMDI();

    //! Adds the form, that will add a store, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Store" button, located at StoresListView form.
      There will be placed a child dialog into MDI to allow the user to add more stores into database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageStoresToMDI() and removeFormAddStoreMDI()
    */
    void addFormAddStoreToMDI();

    //! Removes the form, that adds a store, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more stores into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageStoresToMDI() and addFormAddStoreToMDI()
    */
    void removeFormAddStoreMDI();

    //! Adds the form, that will edit a store, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit store" button, located at StoresListView form.
      There will be placed a child dialog into MDI to allow the current user to edit stores from database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageStoresToMDI() and removeFormEditStoreMDI()
    */
    void addFormEditStoreToMDI(Store *store);

    //! Removes the form, that edits a store, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit stores into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageStoresToMDI() and addFormEditStoreToMDI()
    */
    void removeFormEditStoreMDI();

    //! Adds the form, that will handle the sales orders management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "sales orders" context menu, inside "Sales" menu.
      There will be placed a child dialog into MDI to allow user mantain sales order's database.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormAddSalesOrderToMDI(), removeFormAddSalesOrderMDI(), addFormEditSalesOrderToMDI() and removeFormEditSalesOrderMDI()
    */
    void addFormManageSalesOrdersToMDI();

    //! Adds the form, that will add a sales order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Sales Order" button, located at SalesOrdersListView form.
      There will be placed a child dialog into MDI to allow the user to add more sales orders into database.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormManageSalesOrdersToMDI() and removeFormAddSalesOrderMDI()
    */
    void addFormAddSalesOrderToMDI();

    //! Removes the form, that adds a sales order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more sales orders into database, will be removed from MDI.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormManageSalesOrdersToMDI() and addFormAddSalesOrderToMDI()
    */
    void removeFormAddSalesOrderMDI();

    //! Adds the form, that will edit a sales order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit sales order" button, located at SalesOrdersListView form.
      There will be placed a child dialog into MDI to allow the current user to edit sales orders from database.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormManageSalesOrdersToMDI() and removeFormEditSalesOrderMDI()
    */
    void addFormEditSalesOrderToMDI(SalesOrder *salesOrder);

    //! Removes the form, that edits a sales order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit sales orders into database, will be removed from MDI.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormManageSalesOrdersToMDI() and addFormEditSalesOrderToMDI()
    */
    void removeFormEditSalesOrderMDI();

    //! Adds the form, that will add a sale product order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Sale Product Order" button, located at AddSalesOrderView form.
      There will be placed a child dialog into MDI to allow the user to add more sale product orders into database.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa removeFormAddSaleProductOrderToMDI()
    */
    void addFormAddSaleProductOrderToMDI(AddSalesOrderView *addSalesOrderView);

    //! Removes the form, that adds a sale product order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more sale product orders into database, will be removed from MDI.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormAddSaleProductOrderToMDI()
    */
    void removeFormAddSaleProductOrderMDI();

    //! Adds the form, that will edit a sale product order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit sale product order order" button, located at AddSalesOrderView form.
      There will be placed a child dialog into MDI to allow the current user to edit sale product orders from database.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa removeFormEditSaleProductOrderMDI()
    */
    void addFormEditSaleProductOrderToMDI(SaleProductOrder *saleProductOrder, AddSalesOrderView *addSalesOrderView);

    //! Removes the form, that edits a sales order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit sales orders into database, will be removed from MDI.
      Only Managers, Supervisors and Sellers are allowed to get into this option.
      \sa addFormEditSaleProductOrderToMDI()
    */
    void removeFormEditSaleProductOrderMDI();

    //! Adds the form, that will handle the purchases orders management, into MDI area
    /*!
      This is an abstract method that will get called, when an user select "purchases orders" context menu, inside "Sales" menu.
      There will be placed a child dialog into MDI to allow user mantain purchases order's database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormAddPurchasesOrderToMDI(), removeFormAddPurchasesOrderMDI(), addFormEditPurchasesOrderToMDI() and removeFormEditPurchasesOrderMDI()
    */
    void addFormManagePurchasesOrdersToMDI();

    //! Adds the form, that will add a purchases order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Purchases Order" button, located at PurchasesOrdersListView form.
      There will be placed a child dialog into MDI to allow the user to add more purchases orders into database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManagePurchasesOrdersToMDI() and removeFormAddPurchasesOrderMDI()
    */
    void addFormAddPurchasesOrderToMDI();

    //! Removes the form, that adds a purchases order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more purchases orders into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManagePurchasesOrdersToMDI() and addFormAddPurchasesOrderToMDI()
    */
    void removeFormAddPurchasesOrderMDI();

    //! Adds the form, that will edit a purchases order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit purchases order" button, located at PurchasesOrdersListView form.
      There will be placed a child dialog into MDI to allow the current user to edit purchases orders from database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManagePurchasesOrdersToMDI() and removeFormEditPurchasesOrderMDI()
    */
    void addFormEditPurchasesOrderToMDI(PurchasesOrder *purchasesOrder);

    //! Removes the form, that edits a purchases order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit purchases orders into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManagePurchasesOrdersToMDI() and addFormEditPurchasesOrderToMDI()
    */
    void removeFormEditPurchasesOrderMDI();

    //! Adds the form, that will add a purchase product order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Purchase Product Order" button, located at AddPurchasesOrderView form.
      There will be placed a child dialog into MDI to allow the user to add more purchase product orders into database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa removeFormAddPurchaseProductOrderToMDI()
    */
    void addFormAddPurchaseProductOrderToMDI(AddPurchasesOrderView *addPurchasesOrderView);

    //! Removes the form, that adds a purchase product order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more purchase product orders into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormAddPurchaseProductOrderToMDI()
    */
    void removeFormAddPurchaseProductOrderMDI();

    //! Adds the form, that will edit a purchase product order, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit purchase product order order" button, located at AddPurchasesOrderView form.
      There will be placed a child dialog into MDI to allow the current user to edit purchase product orders from database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa removeFormEditPurchaseProductOrderMDI()
    */
    void addFormEditPurchaseProductOrderToMDI(PurchaseProductOrder *purchaseProductOrder, AddPurchasesOrderView *addPurchasesOrderView);

    //! Removes the form, that edits a purchases order, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit purchases orders into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormEditPurchaseProductOrderToMDI()
    */
    void removeFormEditPurchaseProductOrderMDI();

    //! Adds the form, that will handle the account management, into MDI area
    /*!
      This is an abstract method that will get called, when an account select "Manage Account" context menu, inside "Tax" menu.
      There will be placed a child dialog into MDI to allow account mantain account's database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormAddAccountToMDI(), removeFormAddAccountMDI(), addFormEditAccountToMDI() and removeFormEditAccountMDI()
    */
    void addFormManageAccountsToMDI();

    //! Adds the form, that will add an account, into MDI area
    /*!
      This is an abstract method that will get called, when an account clicks on "Add Account" button, located at AddAccountView form.
      There will be placed a child dialog into MDI to allow the current account to add more accounts into database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageAccountsToMDI() and removeFormAddAccountMDI()
    */
    void addFormAddAccountToMDI();

    //! Removes the form, that adds an account, from MDI area
    /*!
      This is an abstract method that will get called, when an account dismisses the dialog.
      The child dialog that allows an account to add more accounts into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageAccountsToMDI() and addFormAddAccountToMDI()
    */
    void removeFormAddAccountMDI();

    //! Adds the form, that will edit an account, into MDI area
    /*!
      This is an abstract method that will get called, when an account clicks on "Edit Account" button, located at AddAccountView form.
      There will be placed a child dialog into MDI to allow the current account to edit accounts from database.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageAccountsToMDI() and removeFormEditAccountMDI()
    */
    void addFormEditAccountToMDI(Account *account);


    //! Removes the form, that edits an account, from MDI area
    /*!
      This is an abstract method that will get called, when an account dismisses the dialog.
      The child dialog that allows an account to edit accounts into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
      \sa addFormManageAccountsToMDI() and addFormEditAccountToMDI()
    */
    void removeFormEditAccountMDI();

	//! Adds the form, that will edit a History, into MDI area
    /*!
      This is an abstract method that will get called, when an account clicks on "Edit History" button, located at AddHistoryView form.
      There will be placed a child dialog into MDI to allow the current account to edit Histories from database.
      Only Managers and Supervisors are allowed to get into this option.
    */
	void addFormManageHistoriesToMDI();

	
    //! Adds the form, that will add a History, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add History" button, located at AddHistoryView form.
      There will be placed a child dialog into MDI to allow the user to add more Histories into database.
      Only Managers and Supervisors are allowed to get into this option.
    */
     void addFormAddHistoryToMDI();

    //! Removes the form, that adds a History, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more Histories into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
    */
     void removeFormAddHistoryMDI();

    //! Adds the form, that will edit a History, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit History" button, located at AddHistoryView form.
      There will be placed a child dialog into MDI to allow the current user to edit Histories from database.
      Only Managers and Supervisors are allowed to get into this option.
	*/
     void addFormEditHistoryToMDI(History *history);

    //! Removes the form, that edits a History, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit Histories into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
    */
     void removeFormEditHistoryMDI();

	//! Adds the form, that will edit an Entry, into MDI area
    /*!
      This is an abstract method that will get called, when an Entry clicks on "Edit Entry" button, located at AddEntryView form.
      There will be placed a child dialog into MDI to allow the current account to edit Entries from database.
      Only Managers and Supervisors are allowed to get into this option.
    */
	void addFormManageEntriesToMDI();

    //! Adds the form, that will add an Entry, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Add Entry" button, located at AddEntryView form.
      There will be placed a child dialog into MDI to allow the user to add more Entries into database.
      Only Managers and Supervisors are allowed to get into this option.
    */
    void addFormAddEntryToMDI();

    //! Removes the form, that adds an Entry, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to add more Entries into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
    */
    void removeFormAddEntryMDI();

    //! Adds the form, that will edit an Entry, into MDI area
    /*!
      This is an abstract method that will get called, when an user clicks on "Edit Entry" button, located at AddEntryView form.
      There will be placed a child dialog into MDI to allow the current user to edit Entries from database.
      Only Managers and Supervisors are allowed to get into this option.
    */
    void addFormEditEntryToMDI(Entry *entry);

    //! Removes the form, that edits an Entry, from MDI area
    /*!
      This is an abstract method that will get called, when an user dismisses the dialog.
      The child dialog that allows an user to edit Entries into database, will be removed from MDI.
      Only Managers and Supervisors are allowed to get into this option.
    */
    void removeFormEditEntryMDI();

private:
    Ui::MainWindow *ui;
    Login *loginDialog;
    User *user;

    //======= Users =========
    UsersListView *usersListView;
    QMdiSubWindow *subWindowUserListView;
    AddUserView *addUserView;
    QMdiSubWindow *subWindowAddUserView;
    AddUserView *editUserView;
    QMdiSubWindow *subWindowEditUserView;

    //======== Manufacturers =============
    ManufacturersListView *manufacturersListView;
    QMdiSubWindow *subWindowManufacturerListView;
    AddManufacturerView *addManufacturerView;
    QMdiSubWindow *subWindowAddManufacturerView;
    AddManufacturerView *editManufacturerView;
    QMdiSubWindow *subWindowEditManufacturerView;

    //======== Providers =============
    ProvidersListView *providersListView;
    QMdiSubWindow *subWindowProviderListView;
    AddProviderView *addProviderView;
    QMdiSubWindow *subWindowAddProviderView;
    AddProviderView *editProviderView;
    QMdiSubWindow *subWindowEditProviderView;

    //======== Product Categories ==========
    ProductCategoriesListView *productCategoriesListView;
    QMdiSubWindow *subWindowProductCategoryListView;
    AddProductCategoryView *addProductCategoryView;
    QMdiSubWindow *subWindowAddProductCategoryView;
    AddProductCategoryView *editProductCategoryView;
    QMdiSubWindow *subWindowEditProductCategoryView;

    //======== Product ==========
    ProductsListView *productsListView;
    QMdiSubWindow *subWindowProductListView;
    AddProductView *addProductView;
    QMdiSubWindow *subWindowAddProductView;
    AddProductView *editProductView;
    QMdiSubWindow *subWindowEditProductView;

    //======== Customers ==========
    CustomersListView *customersListView;
    QMdiSubWindow *subWindowCustomerListView;
    AddEnterpriseCustomerView *addEnterpriseCustomerView;
    QMdiSubWindow *subWindowAddEnterpriseCustomerView;
    AddEnterpriseCustomerView *editEnterpriseCustomerView;
    QMdiSubWindow *subWindowEditEnterpriseCustomerView;
    AddPhysicalCustomerView *addPhysicalCustomerView;
    QMdiSubWindow *subWindowAddPhysicalCustomerView;
    AddPhysicalCustomerView *editPhysicalCustomerView;
    QMdiSubWindow *subWindowEditPhysicalCustomerView;

    //======== Stock Units ==========
    StockUnitsListView *stockUnitsListView;
    QMdiSubWindow *subWindowStockUnitListView;
    AddStockUnitView *addStockUnitView;
    QMdiSubWindow *subWindowAddStockUnitView;
    AddStockUnitView *editStockUnitView;
    QMdiSubWindow *subWindowEditStockUnitView;

    //======== Product Origins ==========
    ProductOriginsListView *productOriginsListView;
    QMdiSubWindow *subWindowProductOriginListView;
    AddProductOriginView *addProductOriginView;
    QMdiSubWindow *subWindowAddProductOriginView;
    AddProductOriginView *editProductOriginView;
    QMdiSubWindow *subWindowEditProductOriginView;

    //======== CST ICMS ==========
    CstIcmssListView *cstIcmssListView;
    QMdiSubWindow *subWindowCstIcmsListView;
    AddCstIcmsView *addCstIcmsView;
    QMdiSubWindow *subWindowAddCstIcmsView;
    AddCstIcmsView *editCstIcmsView;
    QMdiSubWindow *subWindowEditCstIcmsView;

    //======== CST IPI ==========
    CstIpisListView *cstIpisListView;
    QMdiSubWindow *subWindowCstIpiListView;
    AddCstIpiView *addCstIpiView;
    QMdiSubWindow *subWindowAddCstIpiView;
    AddCstIpiView *editCstIpiView;
    QMdiSubWindow *subWindowEditCstIpiView;

    //======== CST PIS ==========
    CstPissListView *cstPissListView;
    QMdiSubWindow *subWindowCstPisListView;
    AddCstPisView *addCstPisView;
    QMdiSubWindow *subWindowAddCstPisView;
    AddCstPisView *editCstPisView;
    QMdiSubWindow *subWindowEditCstPisView;

    //======== CST COFINS ==========
    CstCofinssListView *cstCofinssListView;
    QMdiSubWindow *subWindowCstCofinsListView;
    AddCstCofinsView *addCstCofinsView;
    QMdiSubWindow *subWindowAddCstCofinsView;
    AddCstCofinsView *editCstCofinsView;
    QMdiSubWindow *subWindowEditCstCofinsView;

    //======== TAX RATE ==========
    TaxRatesListView *taxRatesListView;
    QMdiSubWindow *subWindowTaxRateListView;
    AddTaxRateView *addTaxRateView;
    QMdiSubWindow *subWindowAddTaxRateView;
    AddTaxRateView *editTaxRateView;
    QMdiSubWindow *subWindowEditTaxRateView;

    //======== CFOP ==========
    CfopsListView *cfopsListView;
    QMdiSubWindow *subWindowCfopListView;
    AddCfopView *addCfopView;
    QMdiSubWindow *subWindowAddCfopView;
    AddCfopView *editCfopView;
    QMdiSubWindow *subWindowEditCfopView;

    //======== PRICE ==========
    PricesListView *pricesListView;
    QMdiSubWindow *subWindowPriceListView;
    AddPriceView *addPriceView;
    QMdiSubWindow *subWindowAddPriceView;
    AddPriceView *editPriceView;
    QMdiSubWindow *subWindowEditPriceView;

    //======== STORES =============
    StoresListView *storesListView;
    QMdiSubWindow *subWindowStoreListView;
    AddStoreView *addStoreView;
    QMdiSubWindow *subWindowAddStoreView;
    AddStoreView *editStoreView;
    QMdiSubWindow *subWindowEditStoreView;

    //======== SALES ORDERS =============
    SalesOrdersListView *salesOrdersListView;
    QMdiSubWindow *subWindowSalesOrderListView;
    AddSalesOrderView *addSalesOrderView;
    QMdiSubWindow *subWindowAddSalesOrderView;
    AddSalesOrderView *editSalesOrderView;
    QMdiSubWindow *subWindowEditSalesOrderView;

    //======== SALES PRODUCT ORDERS =============
    AddSaleProductOrderView *addSaleProductOrderView;
    QMdiSubWindow *subWindowAddSaleProductOrderView;
    AddSaleProductOrderView *editSaleProductOrderView;
    QMdiSubWindow *subWindowEditSaleProductOrderView;

    //======== PURCHASES ORDERS =============
    PurchasesOrdersListView *purchasesOrdersListView;
    QMdiSubWindow *subWindowPurchasesOrderListView;
    AddPurchasesOrderView *addPurchasesOrderView;
    QMdiSubWindow *subWindowAddPurchasesOrderView;
    AddPurchasesOrderView *editPurchasesOrderView;
    QMdiSubWindow *subWindowEditPurchasesOrderView;

    //======== PURCHASES PRODUCT ORDERS =============
    AddPurchaseProductOrderView *addPurchaseProductOrderView;
    QMdiSubWindow *subWindowAddPurchaseProductOrderView;
    AddPurchaseProductOrderView *editPurchaseProductOrderView;
    QMdiSubWindow *subWindowEditPurchaseProductOrderView;

    //======= ACCOUNTS =========
    AccountsListView *accountsListView;
    QMdiSubWindow *subWindowAccountListView;
    AddAccountView *addAccountView;
    QMdiSubWindow *subWindowAddAccountView;
    AddAccountView *editAccountView;
    QMdiSubWindow *subWindowEditAccountView;

	//======= HISTORIES =========
    HistoriesListView *historiesListView;
    QMdiSubWindow *subWindowHistoryListView;
    AddHistoryView *addHistoryView;
    QMdiSubWindow *subWindowAddHistoryView;
    AddHistoryView *editHistoryView;
    QMdiSubWindow *subWindowEditHistoryView;

    //======= ENTRIES =========
    EntriesListView *entriesListView;
    QMdiSubWindow *subWindowEntryListView;
    AddEntryView *addEntryView;
    QMdiSubWindow *subWindowAddEntryView;
    AddEntryView *editEntryView;
    QMdiSubWindow *subWindowEditEntryView;


		
};

#endif // MAINWINDOW_H
