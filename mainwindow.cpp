#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testing.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QTextCodec::setCodecForLocale ( QTextCodec::codecForName ( "UTF-8" ) );
    //QTextCodec::setCodecForCStrings ( QTextCodec::codecForName ( "UTF-8" ) );

    this->loginDialog = new Login();
    this->loginDialog->setParentMainWindow(this);
    QDialog::DialogCode ret = (QDialog::DialogCode)this->loginDialog->exec();
    if(ret == QDialog::Rejected)
    {
        exit(0);
    }

    //===========================================================================
    // If user is neither manager nor supervisor, then do not enable system menu
    // and stock menus
    //===========================================================================
    bool systemEnabled = false;
    bool stockEnabled = false;
    bool customersEnabled = false;
    bool taxEnabled = false;
    if(user)
    {
        User::UserRole role = user->getRole();
        if((role == User::MANAGER) || (role == User::SUPERVISOR))
        {
            systemEnabled = true;
            stockEnabled = true;
            customersEnabled = true;
            taxEnabled = true;
        }
        else if(role == User::STOCK)
        {
            stockEnabled = true;
        }
    }
    ui->menuSystem->setEnabled(systemEnabled);
    ui->menuStock->setEnabled(stockEnabled);
    ui->menuCustomers->setEnabled(customersEnabled);
    ui->menuTax->setEnabled(taxEnabled);
    //===========================================================================

    this->subWindowUserListView = NULL;
    this->subWindowAddUserView = NULL;
    this->subWindowEditUserView = NULL;

    this->subWindowManufacturerListView = NULL;
    this->subWindowAddManufacturerView = NULL;
    this->subWindowEditManufacturerView = NULL;

    this->subWindowProviderListView = NULL;
    this->subWindowAddProviderView = NULL;
    this->subWindowEditProviderView = NULL;

    this->subWindowProductCategoryListView = NULL;
    this->subWindowAddProductCategoryView = NULL;
    this->subWindowEditProductCategoryView = NULL;

    this->subWindowProductListView = NULL;
    this->subWindowAddProductView = NULL;
    this->subWindowEditProductView = NULL;

    this->subWindowCustomerListView = NULL;
    this->subWindowAddEnterpriseCustomerView = NULL;
    this->subWindowEditEnterpriseCustomerView = NULL;
    this->subWindowAddPhysicalCustomerView = NULL;
    this->subWindowEditPhysicalCustomerView = NULL;

    this->subWindowStockUnitListView = NULL;
    this->subWindowAddStockUnitView = NULL;
    this->subWindowEditStockUnitView = NULL;

    this->subWindowProductOriginListView = NULL;
    this->subWindowAddProductOriginView = NULL;
    this->subWindowEditProductOriginView = NULL;

    this->subWindowCstIcmsListView = NULL;
    this->subWindowAddCstIcmsView = NULL;
    this->subWindowEditCstIcmsView = NULL;

    this->subWindowCstIpiListView = NULL;
    this->subWindowAddCstIpiView = NULL;
    this->subWindowEditCstIpiView = NULL;

    this->subWindowCstPisListView = NULL;
    this->subWindowAddCstPisView = NULL;
    this->subWindowEditCstPisView = NULL;

    this->subWindowCstCofinsListView = NULL;
    this->subWindowAddCstCofinsView = NULL;
    this->subWindowEditCstCofinsView = NULL;

    this->subWindowTaxRateListView = NULL;
    this->subWindowAddTaxRateView = NULL;
    this->subWindowEditTaxRateView = NULL;

    this->subWindowCfopListView = NULL;
    this->subWindowAddCfopView = NULL;
    this->subWindowEditCfopView = NULL;

    this->subWindowPriceListView = NULL;
    this->subWindowAddPriceView = NULL;
    this->subWindowEditPriceView = NULL;

    this->subWindowStoreListView = NULL;
    this->subWindowAddStoreView = NULL;
    this->subWindowEditStoreView = NULL;

    this->subWindowSalesOrderListView = NULL;
    this->subWindowAddSalesOrderView = NULL;
    this->subWindowEditSalesOrderView = NULL;
    this->subWindowAddSaleProductOrderView = NULL;
    this->subWindowEditSaleProductOrderView = NULL;

    this->subWindowPurchasesOrderListView = NULL;
    this->subWindowAddPurchasesOrderView = NULL;
    this->subWindowEditPurchasesOrderView = NULL;
    this->subWindowAddPurchaseProductOrderView = NULL;
    this->subWindowEditPurchaseProductOrderView = NULL;

    this->subWindowAccountListView = NULL;
    this->subWindowAddAccountView = NULL;
    this->subWindowEditAccountView = NULL;

	//ByMav
	this->subWindowHistoryListView = NULL;
	this->subWindowAddHistoryView = NULL;
	this->subWindowEditHistoryView = NULL;

    this->subWindowEntryListView = NULL;
    this->subWindowAddEntryView = NULL;
    this->subWindowEditEntryView = NULL;
	

    connect(ui->actionManage_Users, SIGNAL(triggered()), this, SLOT(addFormManageUsersToMDI()));
    connect(ui->actionManufacturers, SIGNAL(triggered()), this, SLOT(addFormManageManufacturersToMDI()));
    connect(ui->actionProviders, SIGNAL(triggered()), this, SLOT(addFormManageProvidersToMDI()));
    connect(ui->actionProduct_Categories, SIGNAL(triggered()), this, SLOT(addFormManageProductCategoriesToMDI()));
    connect(ui->actionProducts, SIGNAL(triggered()), this, SLOT(addFormManageProductsToMDI()));
    connect(ui->actionManage_Customers, SIGNAL(triggered()), this, SLOT(addFormManageCustomersToMDI()));
    connect(ui->actionStock_Units, SIGNAL(triggered()), this, SLOT(addFormManageStockUnitsToMDI()));
    connect(ui->actionProductOrigin, SIGNAL(triggered()), this, SLOT(addFormManageProductOriginsToMDI()));
    connect(ui->actionCST_ICMS, SIGNAL(triggered()), this, SLOT(addFormManageCstIcmssToMDI()));
    connect(ui->actionCST_IPI, SIGNAL(triggered()), this, SLOT(addFormManageCstIpisToMDI()));
    connect(ui->actionCST_PIS, SIGNAL(triggered()), this, SLOT(addFormManageCstPissToMDI()));
    connect(ui->actionCST_COFINS, SIGNAL(triggered()), this, SLOT(addFormManageCstCofinssToMDI()));
    connect(ui->actionTax_Rates, SIGNAL(triggered()), this, SLOT(addFormManageTaxRatesToMDI()));
    connect(ui->actionCFOP, SIGNAL(triggered()), this, SLOT(addFormManageCfopsToMDI()));
    connect(ui->actionPrices, SIGNAL(triggered()), this, SLOT(addFormManagePricesToMDI()));
    connect(ui->actionStores, SIGNAL(triggered()), this, SLOT(addFormManageStoresToMDI()));
    connect(ui->actionSales_Orders, SIGNAL(triggered()), this, SLOT(addFormManageSalesOrdersToMDI()));
    connect(ui->actionPurchase_Orders, SIGNAL(triggered()), this, SLOT(addFormManagePurchasesOrdersToMDI()));
    connect(ui->actionAccounts, SIGNAL(triggered()), this, SLOT(addFormManageAccountsToMDI()));
	
	//ByMav
	connect(ui->actionHistories, SIGNAL(triggered()), this, SLOT(addFormManageHistoriesToMDI()));

	connect(ui->actionEntries, SIGNAL(triggered()), this, SLOT(addFormManageEntriesToMDI()));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete loginDialog;
    delete user;

    //======= Users =========
    if(subWindowUserListView)
        delete subWindowUserListView;
    if(subWindowAddUserView)
        delete subWindowAddUserView;
    if(subWindowEditUserView)
        delete subWindowEditUserView;

    //======== Manufacturers =============
    if(subWindowManufacturerListView)
        delete subWindowManufacturerListView;
    if(subWindowAddManufacturerView)
        delete subWindowAddManufacturerView;
    if(subWindowEditManufacturerView)
        delete subWindowEditManufacturerView;

    //======== Providers =============
    if(subWindowProviderListView)
        delete subWindowProviderListView;
    if(subWindowAddProviderView)
        delete subWindowAddProviderView;
    if(subWindowEditProviderView)
        delete subWindowEditProviderView;

    //======== Product Categories ==========
    if(subWindowProductCategoryListView)
        delete subWindowProductCategoryListView;
    if(subWindowAddProductCategoryView)
        delete subWindowAddProductCategoryView;
    if(subWindowEditProductCategoryView)
        delete subWindowEditProductCategoryView;

    //======== Product ==========
    if(subWindowProductListView)
        delete subWindowProductListView;
    if(subWindowAddProductView)
        delete subWindowAddProductView;
    if(subWindowEditProductView)
        delete subWindowEditProductView;

    //======== Customers ==========
    if(subWindowCustomerListView)
        delete subWindowCustomerListView;
    if(subWindowAddEnterpriseCustomerView)
        delete subWindowAddEnterpriseCustomerView;
    if(subWindowEditEnterpriseCustomerView)
        delete subWindowEditEnterpriseCustomerView;
    if(subWindowAddPhysicalCustomerView)
        delete subWindowAddPhysicalCustomerView;
    if(subWindowEditPhysicalCustomerView)
        delete subWindowEditPhysicalCustomerView;

    //======== Stock Units ==========
    if(subWindowStockUnitListView)
        delete subWindowStockUnitListView;
    if(subWindowAddStockUnitView)
        delete subWindowAddStockUnitView;
    if(subWindowEditStockUnitView)
        delete subWindowEditStockUnitView;

    //======== Produc Origins ==========
    if(subWindowProductOriginListView)
        delete subWindowProductOriginListView;
    if(subWindowAddProductOriginView)
        delete subWindowAddProductOriginView;
    if(subWindowEditProductOriginView)
        delete subWindowEditProductOriginView;

    //=========== CST ICMS =============
    if(subWindowCstIcmsListView)
        delete subWindowCstIcmsListView;
    if(subWindowAddCstIcmsView)
        delete subWindowAddCstIcmsView;
    if(subWindowEditCstIcmsView)
        delete subWindowEditCstIcmsView;

    //=========== CST IPI =============
    if(subWindowCstIpiListView)
        delete subWindowCstIpiListView;
    if(subWindowAddCstIpiView)
        delete subWindowAddCstIpiView;
    if(subWindowEditCstIpiView)
        delete subWindowEditCstIpiView;

    //=========== CST PIS =============
    if(subWindowCstPisListView)
        delete subWindowCstPisListView;
    if(subWindowAddCstPisView)
        delete subWindowAddCstPisView;
    if(subWindowEditCstPisView)
        delete subWindowEditCstPisView;

    //=========== CST COFINS =============
    if(subWindowCstCofinsListView)
        delete subWindowCstCofinsListView;
    if(subWindowAddCstCofinsView)
        delete subWindowAddCstCofinsView;
    if(subWindowEditCstCofinsView)
        delete subWindowEditCstCofinsView;

    //=========== TAX RATES =============
    if(subWindowTaxRateListView)
        delete subWindowTaxRateListView;
    if(subWindowAddTaxRateView)
        delete subWindowAddTaxRateView;
    if(subWindowEditTaxRateView)
        delete subWindowEditTaxRateView;

    //=========== CFOP =============
    if(subWindowCfopListView)
        delete subWindowCfopListView;
    if(subWindowAddCfopView)
        delete subWindowAddCfopView;
    if(subWindowEditCfopView)
        delete subWindowEditCfopView;

    //=========== PRICE =============
    if(subWindowPriceListView)
        delete subWindowPriceListView;
    if(subWindowAddPriceView)
        delete subWindowAddPriceView;
    if(subWindowEditPriceView)
        delete subWindowEditPriceView;

    //=========== STORE =============
    if(subWindowStoreListView)
        delete subWindowStoreListView;
    if(subWindowAddStoreView)
        delete subWindowAddStoreView;
    if(subWindowEditStoreView)
        delete subWindowEditStoreView;

    //=========== SALES ORDERS =============
    if(subWindowSalesOrderListView)
        delete subWindowSalesOrderListView;
    if(subWindowAddSalesOrderView)
        delete subWindowAddSalesOrderView;
    if(subWindowEditSalesOrderView)
        delete subWindowEditSalesOrderView;

    //========== SALE PRODUCT ORDERS ==========
    if(subWindowAddSaleProductOrderView)
        delete subWindowAddSaleProductOrderView;
    if(subWindowEditSaleProductOrderView)
        delete subWindowEditSaleProductOrderView;

    //=========== PURCHASES ORDERS =============
    if(subWindowPurchasesOrderListView)
        delete subWindowPurchasesOrderListView;
    if(subWindowAddPurchasesOrderView)
        delete subWindowAddPurchasesOrderView;
    if(subWindowEditPurchasesOrderView)
        delete subWindowEditPurchasesOrderView;

    //========== PURCHASE PRODUCT ORDERS ==========
    if(subWindowAddPurchaseProductOrderView)
        delete subWindowAddPurchaseProductOrderView;
    if(subWindowEditPurchaseProductOrderView)
        delete subWindowEditPurchaseProductOrderView;

    //======= Accounts =========
    if(subWindowAccountListView)
        delete subWindowAccountListView;
    if(subWindowAddAccountView)
        delete subWindowAddAccountView;
    if(subWindowEditAccountView)
        delete subWindowEditAccountView;

	//ByMav
	//=========== HISTORIES =============
    if(subWindowHistoryListView)
        delete subWindowHistoryListView;
    if(subWindowAddHistoryView)
        delete subWindowAddHistoryView;
    if(subWindowEditHistoryView)
        delete subWindowEditHistoryView;

    //=========== ENTRIES =============
    if(subWindowEntryListView)
        delete subWindowEntryListView;
    if(subWindowAddEntryView)
        delete subWindowAddEntryView;
    if(subWindowEditEntryView)
        delete subWindowEditEntryView;

}

void MainWindow::setUser(User *user)
{
    this->user = user;
}

//================ SLOTS =================
//================ USERS =================
void MainWindow::addFormManageUsersToMDI()
{
    this->subWindowUserListView = new QMdiSubWindow();
    this->usersListView = new UsersListView();
    this->usersListView->setParentMainWindow(this);
    this->subWindowUserListView->setWidget(this->usersListView);
    ui->mdiArea->addSubWindow(this->subWindowUserListView);

    this->usersListView->show();
}

void MainWindow::addFormAddUserToMDI()
{
    this->subWindowAddUserView = new QMdiSubWindow();
    this->addUserView = new AddUserView(this->usersListView);
    this->addUserView->setParentMainWindow(this);
    this->subWindowAddUserView->setWidget(this->addUserView);
    ui->mdiArea->addSubWindow(this->subWindowAddUserView);

    connect(this->addUserView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddUserMDI()));

    this->addUserView->show();
}

void MainWindow::removeFormAddUserMDI()
{
    this->subWindowAddUserView->close();
}

void MainWindow::addFormEditUserToMDI(User *user)
{
    this->subWindowEditUserView = new QMdiSubWindow();
    this->editUserView = new AddUserView(user, this->usersListView);
    this->editUserView->setParentMainWindow(this);
    this->subWindowEditUserView->setWidget(this->editUserView);
    ui->mdiArea->addSubWindow(this->subWindowEditUserView);

    connect(this->editUserView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditUserMDI()));

    this->editUserView->show();
}

void MainWindow::removeFormEditUserMDI()
{
    this->subWindowEditUserView->close();
}
//================= MANUFACTURERS ===================
void MainWindow::addFormManageManufacturersToMDI()
{
    this->subWindowManufacturerListView = new QMdiSubWindow();
    this->manufacturersListView = new ManufacturersListView();
    this->manufacturersListView->setParentMainWindow(this);
    this->subWindowManufacturerListView->setWidget(this->manufacturersListView);
    ui->mdiArea->addSubWindow(this->subWindowManufacturerListView);

    this->manufacturersListView->show();
}

void MainWindow::addFormAddManufacturerToMDI()
{
    this->subWindowAddManufacturerView = new QMdiSubWindow();
    this->addManufacturerView = new AddManufacturerView(this->manufacturersListView);
    this->addManufacturerView->setParentMainWindow(this);
    this->subWindowAddManufacturerView->setWidget(this->addManufacturerView);
    ui->mdiArea->addSubWindow(this->subWindowAddManufacturerView);

    connect(this->addManufacturerView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddManufacturerMDI()));

    this->addManufacturerView->show();
}

void MainWindow::removeFormAddManufacturerMDI()
{
    this->subWindowAddManufacturerView->close();
}

void MainWindow::addFormEditManufacturerToMDI(Manufacturer *manufacturer)
{
    this->subWindowEditManufacturerView = new QMdiSubWindow();
    this->editManufacturerView = new AddManufacturerView(manufacturer, this->manufacturersListView);
    this->editManufacturerView->setParentMainWindow(this);
    this->subWindowEditManufacturerView->setWidget(this->editManufacturerView);
    ui->mdiArea->addSubWindow(this->subWindowEditManufacturerView);

    connect(this->editManufacturerView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditManufacturerMDI()));

    this->editManufacturerView->show();
}

void MainWindow::removeFormEditManufacturerMDI()
{
    this->subWindowEditManufacturerView->close();
}

//================= PROVIDERS =====================
void MainWindow::addFormManageProvidersToMDI()
{
    this->subWindowProviderListView = new QMdiSubWindow();
    this->providersListView = new ProvidersListView();
    this->providersListView->setParentMainWindow(this);
    this->subWindowProviderListView->setWidget(this->providersListView);
    ui->mdiArea->addSubWindow(this->subWindowProviderListView);

    this->providersListView->show();
}

void MainWindow::addFormAddProviderToMDI()
{
    this->subWindowAddProviderView = new QMdiSubWindow();
    this->addProviderView = new AddProviderView(this->providersListView);
    this->addProviderView->setParentMainWindow(this);
    this->subWindowAddProviderView->setWidget(this->addProviderView);
    ui->mdiArea->addSubWindow(this->subWindowAddProviderView);

    connect(this->addProviderView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddProviderMDI()));

    this->addProviderView->show();
}

void MainWindow::removeFormAddProviderMDI()
{
    this->subWindowAddProviderView->close();
}

void MainWindow::addFormEditProviderToMDI(Provider *provider)
{
    this->subWindowEditProviderView = new QMdiSubWindow();
    this->editProviderView = new AddProviderView(provider, this->providersListView);
    this->editProviderView->setParentMainWindow(this);
    this->subWindowEditProviderView->setWidget(this->editProviderView);
    ui->mdiArea->addSubWindow(this->subWindowEditProviderView);

    connect(this->editProviderView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditProviderMDI()));

    this->editProviderView->show();
}

void MainWindow::removeFormEditProviderMDI()
{
    this->subWindowEditProviderView->close();
}

//============== PRODUCT CATEGORIES ===============
void MainWindow::addFormManageProductCategoriesToMDI()
{
    this->subWindowProductCategoryListView = new QMdiSubWindow();
    this->productCategoriesListView = new ProductCategoriesListView();
    this->productCategoriesListView->setParentMainWindow(this);
    this->subWindowProductCategoryListView->setWidget(this->productCategoriesListView);
    ui->mdiArea->addSubWindow(this->subWindowProductCategoryListView);

    this->productCategoriesListView->show();
}

void MainWindow::addFormAddProductCategoryToMDI()
{
    this->subWindowAddProductCategoryView = new QMdiSubWindow();
    this->addProductCategoryView = new AddProductCategoryView(this->productCategoriesListView);
    this->addProductCategoryView->setParentMainWindow(this);
    this->subWindowAddProductCategoryView->setWidget(this->addProductCategoryView);
    ui->mdiArea->addSubWindow(this->subWindowAddProductCategoryView);

    connect(this->addProductCategoryView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddProductCategoryMDI()));

    this->addProductCategoryView->show();
}

void MainWindow::removeFormAddProductCategoryMDI()
{
    this->subWindowAddProductCategoryView->close();
}

void MainWindow::addFormEditProductCategoryToMDI(ProductCategory *productCategory)
{
    this->subWindowEditProductCategoryView = new QMdiSubWindow();
    this->editProductCategoryView = new AddProductCategoryView(productCategory, this->productCategoriesListView);
    this->editProductCategoryView->setParentMainWindow(this);
    this->subWindowEditProductCategoryView->setWidget(this->editProductCategoryView);
    ui->mdiArea->addSubWindow(this->subWindowEditProductCategoryView);

    connect(this->editProductCategoryView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditProductCategoryMDI()));

    this->editProductCategoryView->show();
}

void MainWindow::removeFormEditProductCategoryMDI()
{
    this->subWindowEditProductCategoryView->close();
}

//===================== PRODUCTS =====================
void MainWindow::addFormManageProductsToMDI()
{
    this->subWindowProductListView = new QMdiSubWindow();
    this->productsListView = new ProductsListView();
    this->productsListView->setParentMainWindow(this);
    this->subWindowProductListView->setWidget(this->productsListView);
    ui->mdiArea->addSubWindow(this->subWindowProductListView);

    this->productsListView->show();
}

void MainWindow::addFormAddProductToMDI()
{
    this->subWindowAddProductView = new QMdiSubWindow();
    this->addProductView = new AddProductView(this->productsListView);
    this->addProductView->setParentMainWindow(this);
    this->subWindowAddProductView->setWidget(this->addProductView);
    ui->mdiArea->addSubWindow(this->subWindowAddProductView);

    connect(this->addProductView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddProductMDI()));

    this->addProductView->show();
}

void MainWindow::removeFormAddProductMDI()
{
    this->subWindowAddProductView->close();
}

void MainWindow::addFormEditProductToMDI(Product *product)
{
    this->subWindowEditProductView = new QMdiSubWindow();
    this->editProductView = new AddProductView(product, this->productsListView);
    this->editProductView->setParentMainWindow(this);
    this->subWindowEditProductView->setWidget(this->editProductView);
    ui->mdiArea->addSubWindow(this->subWindowEditProductView);

    connect(this->editProductView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditProductMDI()));

    this->editProductView->show();
}

void MainWindow::removeFormEditProductMDI()
{
    this->subWindowEditProductView->close();
}

//===================== CUSTOMERS =====================
void MainWindow::addFormManageCustomersToMDI()
{
    this->subWindowCustomerListView = new QMdiSubWindow();
    this->customersListView = new CustomersListView();
    this->customersListView->setParentMainWindow(this);
    this->subWindowCustomerListView->setWidget(this->customersListView);
    ui->mdiArea->addSubWindow(this->subWindowCustomerListView);

    this->customersListView->show();
}

void MainWindow::addFormAddEnterpriseCustomerToMDI()
{
    this->subWindowAddEnterpriseCustomerView = new QMdiSubWindow();
    this->addEnterpriseCustomerView = new AddEnterpriseCustomerView(this->customersListView);
    this->addEnterpriseCustomerView->setParentMainWindow(this);
    this->subWindowAddEnterpriseCustomerView->setWidget(this->addEnterpriseCustomerView);
    ui->mdiArea->addSubWindow(this->subWindowAddEnterpriseCustomerView);

    connect(this->addEnterpriseCustomerView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddEnterpriseCustomerMDI()));

    this->addEnterpriseCustomerView->show();
}

void MainWindow::removeFormAddEnterpriseCustomerMDI()
{
    this->subWindowAddEnterpriseCustomerView->close();
}

void MainWindow::addFormEditEnterpriseCustomerToMDI(EnterpriseCustomer *enterpriseCustomer)
{
    this->subWindowEditEnterpriseCustomerView = new QMdiSubWindow();
    this->editEnterpriseCustomerView = new AddEnterpriseCustomerView(enterpriseCustomer, this->customersListView);
    this->editEnterpriseCustomerView->setParentMainWindow(this);
    this->subWindowEditEnterpriseCustomerView->setWidget(this->editEnterpriseCustomerView);
    ui->mdiArea->addSubWindow(this->subWindowEditEnterpriseCustomerView);

    connect(this->editEnterpriseCustomerView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditEnterpriseCustomerMDI()));

    this->editEnterpriseCustomerView->show();
}

void MainWindow::removeFormEditEnterpriseCustomerMDI()
{
    this->subWindowEditEnterpriseCustomerView->close();
}

void MainWindow::addFormAddPhysicalCustomerToMDI()
{
    this->subWindowAddPhysicalCustomerView = new QMdiSubWindow();
    this->addPhysicalCustomerView = new AddPhysicalCustomerView(this->customersListView);
    this->addPhysicalCustomerView->setParentMainWindow(this);
    this->subWindowAddPhysicalCustomerView->setWidget(this->addPhysicalCustomerView);
    ui->mdiArea->addSubWindow(this->subWindowAddPhysicalCustomerView);

    connect(this->addPhysicalCustomerView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddPhysicalCustomerMDI()));

    this->addPhysicalCustomerView->show();
}

void MainWindow::removeFormAddPhysicalCustomerMDI()
{
    this->subWindowAddPhysicalCustomerView->close();
}

void MainWindow::addFormEditPhysicalCustomerToMDI(PhysicalCustomer *physicalCustomer)
{
    this->subWindowEditPhysicalCustomerView = new QMdiSubWindow();
    this->editPhysicalCustomerView = new AddPhysicalCustomerView(physicalCustomer, this->customersListView);
    this->editPhysicalCustomerView->setParentMainWindow(this);
    this->subWindowEditPhysicalCustomerView->setWidget(this->editPhysicalCustomerView);
    ui->mdiArea->addSubWindow(this->subWindowEditPhysicalCustomerView);

    connect(this->editPhysicalCustomerView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditPhysicalCustomerMDI()));

    this->editPhysicalCustomerView->show();
}

void MainWindow::removeFormEditPhysicalCustomerMDI()
{
    this->subWindowEditPhysicalCustomerView->close();
}

//============== STOCK UNITS ===============
void MainWindow::addFormManageStockUnitsToMDI()
{
    this->subWindowStockUnitListView = new QMdiSubWindow();
    this->stockUnitsListView = new StockUnitsListView();
    this->stockUnitsListView->setParentMainWindow(this);
    this->subWindowStockUnitListView->setWidget(this->stockUnitsListView);
    ui->mdiArea->addSubWindow(this->subWindowStockUnitListView);

    this->stockUnitsListView->show();
}

void MainWindow::addFormAddStockUnitToMDI()
{
    this->subWindowAddStockUnitView = new QMdiSubWindow();
    this->addStockUnitView = new AddStockUnitView(this->stockUnitsListView);
    this->addStockUnitView->setParentMainWindow(this);
    this->subWindowAddStockUnitView->setWidget(this->addStockUnitView);
    ui->mdiArea->addSubWindow(this->subWindowAddStockUnitView);

    connect(this->addStockUnitView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddStockUnitMDI()));

    this->addStockUnitView->show();
}

void MainWindow::removeFormAddStockUnitMDI()
{
    this->subWindowAddStockUnitView->close();
}

void MainWindow::addFormEditStockUnitToMDI(StockUnit *stockUnit)
{
    this->subWindowEditStockUnitView = new QMdiSubWindow();
    this->editStockUnitView = new AddStockUnitView(stockUnit, this->stockUnitsListView);
    this->editStockUnitView->setParentMainWindow(this);
    this->subWindowEditStockUnitView->setWidget(this->editStockUnitView);
    ui->mdiArea->addSubWindow(this->subWindowEditStockUnitView);

    connect(this->editStockUnitView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditStockUnitMDI()));

    this->editStockUnitView->show();
}

void MainWindow::removeFormEditStockUnitMDI()
{
    this->subWindowEditStockUnitView->close();
}

//============== PRODUCT ORIGINS ===============
void MainWindow::addFormManageProductOriginsToMDI()
{
    this->subWindowProductOriginListView = new QMdiSubWindow();
    this->productOriginsListView = new ProductOriginsListView();
    this->productOriginsListView->setParentMainWindow(this);
    this->subWindowProductOriginListView->setWidget(this->productOriginsListView);
    ui->mdiArea->addSubWindow(this->subWindowProductOriginListView);

    this->productOriginsListView->show();
}

void MainWindow::addFormAddProductOriginToMDI()
{
    this->subWindowAddProductOriginView = new QMdiSubWindow();
    this->addProductOriginView = new AddProductOriginView(this->productOriginsListView);
    this->addProductOriginView->setParentMainWindow(this);
    this->subWindowAddProductOriginView->setWidget(this->addProductOriginView);
    ui->mdiArea->addSubWindow(this->subWindowAddProductOriginView);

    connect(this->addProductOriginView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddProductOriginMDI()));

    this->addProductOriginView->show();
}

void MainWindow::removeFormAddProductOriginMDI()
{
    this->subWindowAddProductOriginView->close();
}

void MainWindow::addFormEditProductOriginToMDI(ProductOrigin *productOrigin)
{
    this->subWindowEditProductOriginView = new QMdiSubWindow();
    this->editProductOriginView = new AddProductOriginView(productOrigin, this->productOriginsListView);
    this->editProductOriginView->setParentMainWindow(this);
    this->subWindowEditProductOriginView->setWidget(this->editProductOriginView);
    ui->mdiArea->addSubWindow(this->subWindowEditProductOriginView);

    connect(this->editProductOriginView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditProductOriginMDI()));

    this->editProductOriginView->show();
}

void MainWindow::removeFormEditProductOriginMDI()
{
    this->subWindowEditProductOriginView->close();
}

//============== CST ICMS ===============
void MainWindow::addFormManageCstIcmssToMDI()
{
    this->subWindowCstIcmsListView = new QMdiSubWindow();
    this->cstIcmssListView = new CstIcmssListView();
    this->cstIcmssListView->setParentMainWindow(this);
    this->subWindowCstIcmsListView->setWidget(this->cstIcmssListView);
    ui->mdiArea->addSubWindow(this->subWindowCstIcmsListView);

    this->cstIcmssListView->show();
}

void MainWindow::addFormAddCstIcmsToMDI()
{
    this->subWindowAddCstIcmsView = new QMdiSubWindow();
    this->addCstIcmsView = new AddCstIcmsView(this->cstIcmssListView);
    this->addCstIcmsView->setParentMainWindow(this);
    this->subWindowAddCstIcmsView->setWidget(this->addCstIcmsView);
    ui->mdiArea->addSubWindow(this->subWindowAddCstIcmsView);

    connect(this->addCstIcmsView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddCstIcmsMDI()));

    this->addCstIcmsView->show();
}

void MainWindow::removeFormAddCstIcmsMDI()
{
    this->subWindowAddCstIcmsView->close();
}

void MainWindow::addFormEditCstIcmsToMDI(CstIcms *cstIcms)
{
    this->subWindowEditCstIcmsView = new QMdiSubWindow();
    this->editCstIcmsView = new AddCstIcmsView(cstIcms, this->cstIcmssListView);
    this->editCstIcmsView->setParentMainWindow(this);
    this->subWindowEditCstIcmsView->setWidget(this->editCstIcmsView);
    ui->mdiArea->addSubWindow(this->subWindowEditCstIcmsView);

    connect(this->editCstIcmsView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditCstIcmsMDI()));

    this->editCstIcmsView->show();
}

void MainWindow::removeFormEditCstIcmsMDI()
{
    this->subWindowEditCstIcmsView->close();
}

//============== CST IPI ===============
void MainWindow::addFormManageCstIpisToMDI()
{
    this->subWindowCstIpiListView = new QMdiSubWindow();
    this->cstIpisListView = new CstIpisListView();
    this->cstIpisListView->setParentMainWindow(this);
    this->subWindowCstIpiListView->setWidget(this->cstIpisListView);
    ui->mdiArea->addSubWindow(this->subWindowCstIpiListView);

    this->cstIpisListView->show();
}

void MainWindow::addFormAddCstIpiToMDI()
{
    this->subWindowAddCstIpiView = new QMdiSubWindow();
    this->addCstIpiView = new AddCstIpiView(this->cstIpisListView);
    this->addCstIpiView->setParentMainWindow(this);
    this->subWindowAddCstIpiView->setWidget(this->addCstIpiView);
    ui->mdiArea->addSubWindow(this->subWindowAddCstIpiView);

    connect(this->addCstIpiView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddCstIpiMDI()));

    this->addCstIpiView->show();
}

void MainWindow::removeFormAddCstIpiMDI()
{
    this->subWindowAddCstIpiView->close();
}

void MainWindow::addFormEditCstIpiToMDI(CstIpi *cstIpi)
{
    this->subWindowEditCstIpiView = new QMdiSubWindow();
    this->editCstIpiView = new AddCstIpiView(cstIpi, this->cstIpisListView);
    this->editCstIpiView->setParentMainWindow(this);
    this->subWindowEditCstIpiView->setWidget(this->editCstIpiView);
    ui->mdiArea->addSubWindow(this->subWindowEditCstIpiView);

    connect(this->editCstIpiView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditCstIpiMDI()));

    this->editCstIpiView->show();
}

void MainWindow::removeFormEditCstIpiMDI()
{
    this->subWindowEditCstIpiView->close();
}

//============== CST PIS ===============
void MainWindow::addFormManageCstPissToMDI()
{
    this->subWindowCstPisListView = new QMdiSubWindow();
    this->cstPissListView = new CstPissListView();
    this->cstPissListView->setParentMainWindow(this);
    this->subWindowCstPisListView->setWidget(this->cstPissListView);
    ui->mdiArea->addSubWindow(this->subWindowCstPisListView);

    this->cstPissListView->show();
}

void MainWindow::addFormAddCstPisToMDI()
{
    this->subWindowAddCstPisView = new QMdiSubWindow();
    this->addCstPisView = new AddCstPisView(this->cstPissListView);
    this->addCstPisView->setParentMainWindow(this);
    this->subWindowAddCstPisView->setWidget(this->addCstPisView);
    ui->mdiArea->addSubWindow(this->subWindowAddCstPisView);

    connect(this->addCstPisView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddCstPisMDI()));

    this->addCstPisView->show();
}

void MainWindow::removeFormAddCstPisMDI()
{
    this->subWindowAddCstPisView->close();
}

void MainWindow::addFormEditCstPisToMDI(CstPis *cstPis)
{
    this->subWindowEditCstPisView = new QMdiSubWindow();
    this->editCstPisView = new AddCstPisView(cstPis, this->cstPissListView);
    this->editCstPisView->setParentMainWindow(this);
    this->subWindowEditCstPisView->setWidget(this->editCstPisView);
    ui->mdiArea->addSubWindow(this->subWindowEditCstPisView);

    connect(this->editCstPisView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditCstPisMDI()));

    this->editCstPisView->show();
}

void MainWindow::removeFormEditCstPisMDI()
{
    this->subWindowEditCstPisView->close();
}

//============== CST COFINS ===============
void MainWindow::addFormManageCstCofinssToMDI()
{
    this->subWindowCstCofinsListView = new QMdiSubWindow();
    this->cstCofinssListView = new CstCofinssListView();
    this->cstCofinssListView->setParentMainWindow(this);
    this->subWindowCstCofinsListView->setWidget(this->cstCofinssListView);
    ui->mdiArea->addSubWindow(this->subWindowCstCofinsListView);

    this->cstCofinssListView->show();
}

void MainWindow::addFormAddCstCofinsToMDI()
{
    this->subWindowAddCstCofinsView = new QMdiSubWindow();
    this->addCstCofinsView = new AddCstCofinsView(this->cstCofinssListView);
    this->addCstCofinsView->setParentMainWindow(this);
    this->subWindowAddCstCofinsView->setWidget(this->addCstCofinsView);
    ui->mdiArea->addSubWindow(this->subWindowAddCstCofinsView);

    connect(this->addCstCofinsView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddCstCofinsMDI()));

    this->addCstCofinsView->show();
}

void MainWindow::removeFormAddCstCofinsMDI()
{
    this->subWindowAddCstCofinsView->close();
}

void MainWindow::addFormEditCstCofinsToMDI(CstCofins *cstCofins)
{
    this->subWindowEditCstCofinsView = new QMdiSubWindow();
    this->editCstCofinsView = new AddCstCofinsView(cstCofins, this->cstCofinssListView);
    this->editCstCofinsView->setParentMainWindow(this);
    this->subWindowEditCstCofinsView->setWidget(this->editCstCofinsView);
    ui->mdiArea->addSubWindow(this->subWindowEditCstCofinsView);

    connect(this->editCstCofinsView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditCstCofinsMDI()));

    this->editCstCofinsView->show();
}

void MainWindow::removeFormEditCstCofinsMDI()
{
    this->subWindowEditCstCofinsView->close();
}

//============== TAX RATE ===============
void MainWindow::addFormManageTaxRatesToMDI()
{
    this->subWindowTaxRateListView = new QMdiSubWindow();
    this->taxRatesListView = new TaxRatesListView();
    this->taxRatesListView->setParentMainWindow(this);
    this->subWindowTaxRateListView->setWidget(this->taxRatesListView);
    ui->mdiArea->addSubWindow(this->subWindowTaxRateListView);

    this->taxRatesListView->show();
}

void MainWindow::addFormAddTaxRateToMDI()
{
    this->subWindowAddTaxRateView = new QMdiSubWindow();
    this->addTaxRateView = new AddTaxRateView(this->taxRatesListView);
    this->addTaxRateView->setParentMainWindow(this);
    this->subWindowAddTaxRateView->setWidget(this->addTaxRateView);
    ui->mdiArea->addSubWindow(this->subWindowAddTaxRateView);

    connect(this->addTaxRateView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddTaxRateMDI()));

    this->addTaxRateView->show();
}

void MainWindow::removeFormAddTaxRateMDI()
{
    this->subWindowAddTaxRateView->close();
}

void MainWindow::addFormEditTaxRateToMDI(TaxRate *taxRate)
{
    this->subWindowEditTaxRateView = new QMdiSubWindow();
    this->editTaxRateView = new AddTaxRateView(taxRate, this->taxRatesListView);
    this->editTaxRateView->setParentMainWindow(this);
    this->subWindowEditTaxRateView->setWidget(this->editTaxRateView);
    ui->mdiArea->addSubWindow(this->subWindowEditTaxRateView);

    connect(this->editTaxRateView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditTaxRateMDI()));

    this->editTaxRateView->show();
}

void MainWindow::removeFormEditTaxRateMDI()
{
    this->subWindowEditTaxRateView->close();
}

//============== CFOP ===============
void MainWindow::addFormManageCfopsToMDI()
{
    this->subWindowCfopListView = new QMdiSubWindow();
    this->cfopsListView = new CfopsListView();
    this->cfopsListView->setParentMainWindow(this);
    this->subWindowCfopListView->setWidget(this->cfopsListView);
    ui->mdiArea->addSubWindow(this->subWindowCfopListView);

    this->cfopsListView->show();
}

void MainWindow::addFormAddCfopToMDI()
{
    this->subWindowAddCfopView = new QMdiSubWindow();
    this->addCfopView = new AddCfopView(this->cfopsListView);
    this->addCfopView->setParentMainWindow(this);
    this->subWindowAddCfopView->setWidget(this->addCfopView);
    ui->mdiArea->addSubWindow(this->subWindowAddCfopView);

    connect(this->addCfopView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddCfopMDI()));

    this->addCfopView->show();
}

void MainWindow::removeFormAddCfopMDI()
{
    this->subWindowAddCfopView->close();
}

void MainWindow::addFormEditCfopToMDI(Cfop *cfop)
{
    this->subWindowEditCfopView = new QMdiSubWindow();
    this->editCfopView = new AddCfopView(cfop, this->cfopsListView);
    this->editCfopView->setParentMainWindow(this);
    this->subWindowEditCfopView->setWidget(this->editCfopView);
    ui->mdiArea->addSubWindow(this->subWindowEditCfopView);

    connect(this->editCfopView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditCfopMDI()));

    this->editCfopView->show();
}

void MainWindow::removeFormEditCfopMDI()
{
    this->subWindowEditCfopView->close();
}

//============== PRICE ===============
void MainWindow::addFormManagePricesToMDI()
{
    this->subWindowPriceListView = new QMdiSubWindow();
    this->pricesListView = new PricesListView();
    this->pricesListView->setParentMainWindow(this);
    this->subWindowPriceListView->setWidget(this->pricesListView);
    ui->mdiArea->addSubWindow(this->subWindowPriceListView);

    this->pricesListView->show();
}

void MainWindow::addFormAddPriceToMDI()
{
    this->subWindowAddPriceView = new QMdiSubWindow();
    this->addPriceView = new AddPriceView(this->pricesListView);
    this->addPriceView->setParentMainWindow(this);
    this->subWindowAddPriceView->setWidget(this->addPriceView);
    ui->mdiArea->addSubWindow(this->subWindowAddPriceView);

    connect(this->addPriceView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddPriceMDI()));

    this->addPriceView->show();
}

void MainWindow::removeFormAddPriceMDI()
{
    this->subWindowAddPriceView->close();
}

void MainWindow::addFormEditPriceToMDI(Price *price)
{
    this->subWindowEditPriceView = new QMdiSubWindow();
    this->editPriceView = new AddPriceView(price, this->pricesListView);
    this->editPriceView->setParentMainWindow(this);
    this->subWindowEditPriceView->setWidget(this->editPriceView);
    ui->mdiArea->addSubWindow(this->subWindowEditPriceView);

    connect(this->editPriceView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditPriceMDI()));

    this->editPriceView->show();
}

void MainWindow::removeFormEditPriceMDI()
{
    this->subWindowEditPriceView->close();
}

//================= STORES =====================
void MainWindow::addFormManageStoresToMDI()
{
    this->subWindowStoreListView = new QMdiSubWindow();
    this->storesListView = new StoresListView();
    this->storesListView->setParentMainWindow(this);
    this->subWindowStoreListView->setWidget(this->storesListView);
    ui->mdiArea->addSubWindow(this->subWindowStoreListView);

    this->storesListView->show();
}

void MainWindow::addFormAddStoreToMDI()
{
    this->subWindowAddStoreView = new QMdiSubWindow();
    this->addStoreView = new AddStoreView(this->storesListView);
    this->addStoreView->setParentMainWindow(this);
    this->subWindowAddStoreView->setWidget(this->addStoreView);
    ui->mdiArea->addSubWindow(this->subWindowAddStoreView);

    connect(this->addStoreView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddStoreMDI()));

    this->addStoreView->show();
}

void MainWindow::removeFormAddStoreMDI()
{
    this->subWindowAddStoreView->close();
}

void MainWindow::addFormEditStoreToMDI(Store *store)
{
    this->subWindowEditStoreView = new QMdiSubWindow();
    this->editStoreView = new AddStoreView(store, this->storesListView);
    this->editStoreView->setParentMainWindow(this);
    this->subWindowEditStoreView->setWidget(this->editStoreView);
    ui->mdiArea->addSubWindow(this->subWindowEditStoreView);

    connect(this->editStoreView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditStoreMDI()));

    this->editStoreView->show();
}

void MainWindow::removeFormEditStoreMDI()
{
    this->subWindowEditStoreView->close();
}

//========== SALES =========

void MainWindow::addFormManageSalesOrdersToMDI()
{
    this->subWindowSalesOrderListView = new QMdiSubWindow();
    this->salesOrdersListView = new SalesOrdersListView();
    this->salesOrdersListView->setParentMainWindow(this);
    this->subWindowSalesOrderListView->setWidget(this->salesOrdersListView);
    ui->mdiArea->addSubWindow(this->subWindowSalesOrderListView);

    this->salesOrdersListView->show();
}

void MainWindow::addFormAddSalesOrderToMDI()
{
    this->subWindowAddSalesOrderView = new QMdiSubWindow();
    this->addSalesOrderView = new AddSalesOrderView(this->salesOrdersListView);
    this->addSalesOrderView->setParentMainWindow(this);
    this->subWindowAddSalesOrderView->setWidget(this->addSalesOrderView);
    ui->mdiArea->addSubWindow(this->subWindowAddSalesOrderView);

    connect(this->addSalesOrderView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddSalesOrderMDI()));

    this->addSalesOrderView->show();
}

void MainWindow::removeFormAddSalesOrderMDI()
{
    this->subWindowAddSalesOrderView->close();
}

void MainWindow::addFormEditSalesOrderToMDI(SalesOrder *salesOrder)
{
    this->subWindowEditSalesOrderView = new QMdiSubWindow();
    this->editSalesOrderView = new AddSalesOrderView(salesOrder, this->salesOrdersListView);
    this->editSalesOrderView->setParentMainWindow(this);
    this->subWindowEditSalesOrderView->setWidget(this->editSalesOrderView);
    ui->mdiArea->addSubWindow(this->subWindowEditSalesOrderView);

    connect(this->editSalesOrderView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditSalesOrderMDI()));

    this->editSalesOrderView->show();
}

void MainWindow::removeFormEditSalesOrderMDI()
{
    this->subWindowEditSalesOrderView->close();
}

void MainWindow::addFormAddSaleProductOrderToMDI(AddSalesOrderView *addSalesOrderView)
{
    this->subWindowAddSaleProductOrderView = new QMdiSubWindow();
    this->addSaleProductOrderView = new AddSaleProductOrderView(addSalesOrderView);
    this->addSaleProductOrderView->setParentMainWindow(this);
    this->subWindowAddSaleProductOrderView->setWidget(this->addSaleProductOrderView);
    ui->mdiArea->addSubWindow(this->subWindowAddSaleProductOrderView);

    connect(this->addSaleProductOrderView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddSaleProductOrderMDI()));

    this->addSaleProductOrderView->show();
}

void MainWindow::removeFormAddSaleProductOrderMDI()
{
    this->subWindowAddSaleProductOrderView->close();
}

void MainWindow::addFormEditSaleProductOrderToMDI(SaleProductOrder *saleProductOrder, AddSalesOrderView *addSalesOrderView)
{
    this->subWindowEditSaleProductOrderView = new QMdiSubWindow();
    this->editSaleProductOrderView = new AddSaleProductOrderView(saleProductOrder, addSalesOrderView);
    this->editSaleProductOrderView->setParentMainWindow(this);
    this->subWindowEditSaleProductOrderView->setWidget(this->editSaleProductOrderView);
    ui->mdiArea->addSubWindow(this->subWindowEditSaleProductOrderView);

    connect(this->editSaleProductOrderView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditSaleProductOrderMDI()));

    this->editSaleProductOrderView->show();
}

void MainWindow::removeFormEditSaleProductOrderMDI()
{
    this->subWindowEditSaleProductOrderView->close();
}

//============= PURCHASES ==============

void MainWindow::addFormManagePurchasesOrdersToMDI()
{
    this->subWindowPurchasesOrderListView = new QMdiSubWindow();
    this->purchasesOrdersListView = new PurchasesOrdersListView();
    this->purchasesOrdersListView->setParentMainWindow(this);
    this->subWindowPurchasesOrderListView->setWidget(this->purchasesOrdersListView);
    ui->mdiArea->addSubWindow(this->subWindowPurchasesOrderListView);

    this->purchasesOrdersListView->show();
}

void MainWindow::addFormAddPurchasesOrderToMDI()
{
    this->subWindowAddPurchasesOrderView = new QMdiSubWindow();
    this->addPurchasesOrderView = new AddPurchasesOrderView(this->purchasesOrdersListView);
    this->addPurchasesOrderView->setParentMainWindow(this);
    this->subWindowAddPurchasesOrderView->setWidget(this->addPurchasesOrderView);
    ui->mdiArea->addSubWindow(this->subWindowAddPurchasesOrderView);

    connect(this->addPurchasesOrderView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddPurchasesOrderMDI()));

    this->addPurchasesOrderView->show();
}

void MainWindow::removeFormAddPurchasesOrderMDI()
{
    this->subWindowAddPurchasesOrderView->close();
}

void MainWindow::addFormEditPurchasesOrderToMDI(PurchasesOrder *purchasesOrder)
{
    this->subWindowEditPurchasesOrderView = new QMdiSubWindow();
    this->editPurchasesOrderView = new AddPurchasesOrderView(purchasesOrder, this->purchasesOrdersListView);
    this->editPurchasesOrderView->setParentMainWindow(this);
    this->subWindowEditPurchasesOrderView->setWidget(this->editPurchasesOrderView);
    ui->mdiArea->addSubWindow(this->subWindowEditPurchasesOrderView);

    connect(this->editPurchasesOrderView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditPurchasesOrderMDI()));

    this->editPurchasesOrderView->show();
}

void MainWindow::removeFormEditPurchasesOrderMDI()
{
    this->subWindowEditPurchasesOrderView->close();
}

void MainWindow::addFormAddPurchaseProductOrderToMDI(AddPurchasesOrderView *addPurchasesOrderView)
{
    this->subWindowAddPurchaseProductOrderView = new QMdiSubWindow();
    this->addPurchaseProductOrderView = new AddPurchaseProductOrderView(addPurchasesOrderView);
    this->addPurchaseProductOrderView->setParentMainWindow(this);
    this->subWindowAddPurchaseProductOrderView->setWidget(this->addPurchaseProductOrderView);
    ui->mdiArea->addSubWindow(this->subWindowAddPurchaseProductOrderView);

    connect(this->addPurchaseProductOrderView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddPurchaseProductOrderMDI()));

    this->addPurchaseProductOrderView->show();
}

void MainWindow::removeFormAddPurchaseProductOrderMDI()
{
    this->subWindowAddPurchaseProductOrderView->close();
}

void MainWindow::addFormEditPurchaseProductOrderToMDI(PurchaseProductOrder *purchaseProductOrder, AddPurchasesOrderView *addPurchasesOrderView)
{
    this->subWindowEditPurchaseProductOrderView = new QMdiSubWindow();
    this->editPurchaseProductOrderView = new AddPurchaseProductOrderView(purchaseProductOrder, addPurchasesOrderView);
    this->editPurchaseProductOrderView->setParentMainWindow(this);
    this->subWindowEditPurchaseProductOrderView->setWidget(this->editPurchaseProductOrderView);
    ui->mdiArea->addSubWindow(this->subWindowEditPurchaseProductOrderView);

    connect(this->editPurchaseProductOrderView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditPurchaseProductOrderMDI()));

    this->editPurchaseProductOrderView->show();
}

void MainWindow::removeFormEditPurchaseProductOrderMDI()
{
    this->subWindowEditPurchaseProductOrderView->close();
}

//============= ACCOUNTS ==============
void MainWindow::addFormManageAccountsToMDI()
{
    this->subWindowAccountListView = new QMdiSubWindow();
    this->accountsListView = new AccountsListView();
    this->accountsListView->setParentMainWindow(this);
    this->subWindowAccountListView->setWidget(this->accountsListView);
    ui->mdiArea->addSubWindow(this->subWindowAccountListView);

    this->accountsListView->show();
}

void MainWindow::addFormAddAccountToMDI()
{
    this->subWindowAddAccountView = new QMdiSubWindow();
    this->addAccountView = new AddAccountView(this->accountsListView);
    this->addAccountView->setParentMainWindow(this);
    this->subWindowAddAccountView->setWidget(this->addAccountView);
    ui->mdiArea->addSubWindow(this->subWindowAddAccountView);

    connect(this->addAccountView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddAccountMDI()));

    this->addAccountView->show();
}

void MainWindow::removeFormAddAccountMDI()
{
    this->subWindowAddAccountView->close();
}

void MainWindow::addFormEditAccountToMDI(Account *account)
{
    this->subWindowEditAccountView = new QMdiSubWindow();
    this->editAccountView = new AddAccountView(account, this->accountsListView);
    this->editAccountView->setParentMainWindow(this);
    this->subWindowEditAccountView->setWidget(this->editAccountView);
    ui->mdiArea->addSubWindow(this->subWindowEditAccountView);

    connect(this->editAccountView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditAccountMDI()));

    this->editAccountView->show();
}

void MainWindow::removeFormEditAccountMDI()
{
    this->subWindowEditAccountView->close();
}

//ByMav
//============== HISTORIES ===============

void MainWindow::addFormManageHistoriesToMDI()
{
	this->subWindowHistoryListView = new QMdiSubWindow();
    this->historiesListView = new HistoriesListView();
    this->historiesListView->setParentMainWindow(this);
    this->subWindowHistoryListView->setWidget(this->historiesListView);
    ui->mdiArea->addSubWindow(this->subWindowHistoryListView);
	this->historiesListView->show();
}


void MainWindow::addFormAddHistoryToMDI()
{
    this->subWindowAddHistoryView = new QMdiSubWindow();
    this->addHistoryView = new AddHistoryView(this->historiesListView);
    this->addHistoryView->setParentMainWindow(this);
    this->subWindowAddHistoryView->setWidget(this->addHistoryView);
    ui->mdiArea->addSubWindow(this->subWindowAddHistoryView);

    connect(this->addHistoryView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddHistoryMDI()));

    this->addHistoryView->show();
}


void MainWindow::removeFormAddHistoryMDI()
{
    this->subWindowAddHistoryView->close();
}



void MainWindow::addFormEditHistoryToMDI(History *history)
{
	this->subWindowEditHistoryView = new QMdiSubWindow();
	this->editHistoryView = new AddHistoryView(history, this->historiesListView);
    this->editHistoryView->setParentMainWindow(this);
    this->subWindowEditHistoryView->setWidget(this->editHistoryView);
    ui->mdiArea->addSubWindow(this->subWindowEditHistoryView);

    connect(this->editHistoryView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditHistoryMDI()));

    this->editHistoryView->show();
}

void MainWindow::removeFormEditHistoryMDI()
{
    this->subWindowEditHistoryView->close();
}

//============== ENTRIES ===============

void MainWindow::addFormManageEntriesToMDI()
{
    this->subWindowEntryListView = new QMdiSubWindow();
    this->entriesListView = new EntriesListView();
    this->entriesListView->setParentMainWindow(this);
    this->subWindowEntryListView->setWidget(this->entriesListView);
    ui->mdiArea->addSubWindow(this->subWindowEntryListView);
    this->entriesListView->show();
}

void MainWindow::addFormAddEntryToMDI()
{
    this->subWindowAddEntryView = new QMdiSubWindow();
    this->addEntryView = new AddEntryView(this->entriesListView);
    this->addEntryView->setParentMainWindow(this);
    this->subWindowAddEntryView->setWidget(this->addEntryView);
    ui->mdiArea->addSubWindow(this->subWindowAddEntryView);

    connect(this->addEntryView, SIGNAL(aboutToClose()), this, SLOT(removeFormAddEntryMDI()));

    this->addEntryView->show();
}

void MainWindow::removeFormAddEntryMDI()
{
    this->subWindowAddEntryView->close();
}

void MainWindow::addFormEditEntryToMDI(Entry *entry)
{
    this->subWindowEditEntryView = new QMdiSubWindow();
    this->editEntryView = new AddEntryView(entry, this->entriesListView);
    this->editEntryView->setParentMainWindow(this);
    this->subWindowEditEntryView->setWidget(this->editEntryView);
    ui->mdiArea->addSubWindow(this->subWindowEditEntryView);

    connect(this->editEntryView, SIGNAL(aboutToClose()), this, SLOT(removeFormEditEntryMDI()));

    this->editEntryView->show();
}

void MainWindow::removeFormEditEntryMDI()
{
    this->subWindowEditEntryView->close();
}

