#-------------------------------------------------
#
# Project created by QtCreator 2011-12-15T00:40:58
#
#-------------------------------------------------

QT       += core gui sql xml widgets

TARGET = ERPRock
TEMPLATE = app

DEFINES += DB_POSTGRESQL
CODECFORTR = UTF-8

INCLUDEPATH +=  . \
                Model \
                Model/Stock \
                Model/Customers \
                Model/Tax \
                Model/Sales \
                View \
                View/Stock \
                View/Sales \
                View/Customers \
                View/Tax \
                Controllers \
                Controllers/Stock \
                Controllers/Sales \
                Controllers/Customers \
                Controllers/Tax \
                Exceptions \
                Util \
                UT
unix:INCLUDEPATH += /usr/local/Trolltech/Qt-4.8.0/include/QtSql \
					/usr/local/pgsql/include 
win32:INCLUDEPATH += C:/qt-everywhere-opensource-src-5.2.0/qtbase/include/QtSql/5.2.0 \
					 C:/PostgreSQL/9.3/include \
					C:/qt-everywhere-opensource-src-5.2.0/qtbase/include/QtCore/5.2.0/QtCore

SOURCES += main.cpp\
        mainwindow.cpp \
        Controllers/databasecontroller.cpp \
        Util/utilities.cpp \
        Model/user.cpp \
        Exceptions/filenotfoundexception.cpp \
        Controllers/usercontroller.cpp \
        UT/testing.cpp \
        View/userslistview.cpp \
        View/adduserview.cpp \
        View/login.cpp \
        Model/Stock/manufacturer.cpp \
        Controllers/Stock/manufacturercontroller.cpp \
        View/Stock/addmanufacturerview.cpp \
        View/Stock/manufacturerslistview.cpp \
        Model/Stock/provider.cpp \
        Controllers/Stock/providercontroller.cpp \
        View/Stock/providerslistview.cpp \
        View/Stock/addproviderview.cpp \
        Model/Stock/productcategory.cpp \
        Controllers/Stock/productcategorycontroller.cpp \
        View/Stock/productcategorieslistview.cpp \
        View/Stock/addproductcategoryview.cpp \
        Model/Stock/product.cpp \
        Controllers/Stock/productcontroller.cpp \
        View/Stock/productslistview.cpp \
        View/Stock/addproductview.cpp \
        Model/Customers/customer.cpp \
        Controllers/Customers/customercontroller.cpp \
        Model/Customers/physicalcustomer.cpp \
        Model/Customers/enterprisecustomer.cpp \
        View/Customers/customerslistview.cpp \
        View/Customers/addenterprisecustomerview.cpp \
        View/Customers/addphysicalcustomerview.cpp \
        Model/Stock/stockunit.cpp \
        Controllers/Stock/stockunitcontroller.cpp \
        View/Stock/stockunitslistview.cpp \
        View/Stock/addstockunitview.cpp \
        Model/Stock/productorigin.cpp \
        Controllers/Stock/productorigincontroller.cpp \
        View/Stock/productoriginslistview.cpp \
        View/Stock/addproductoriginview.cpp \
        Model/Tax/csticms.cpp \
        Controllers/Tax/csticmscontroller.cpp \
        View/Tax/csticmsslistview.cpp \
        View/Tax/addcsticmsview.cpp \
        Model/Tax/cstipi.cpp \
        Controllers/Tax/cstipicontroller.cpp \
        View/Tax/cstipislistview.cpp \
        View/Tax/addcstipiview.cpp \
        Model/Tax/cstpis.cpp \
        Controllers/Tax/cstpiscontroller.cpp \
        View/Tax/cstpisslistview.cpp \
        View/Tax/addcstpisview.cpp \
        Model/Tax/cstcofins.cpp \
        Controllers/Tax/cstcofinscontroller.cpp \
        View/Tax/cstcofinsslistview.cpp \
        View/Tax/addcstcofinsview.cpp \
        Model/Tax/taxrate.cpp \
        Controllers/Tax/taxratecontroller.cpp \
        View/Tax/taxrateslistview.cpp \
        View/Tax/addtaxrateview.cpp \
        Model/Tax/cfop.cpp \
        Controllers/Tax/cfopcontroller.cpp \
        View/Tax/cfopslistview.cpp \
        View/Tax/addcfopview.cpp \
    Model/Sales/price.cpp \
    Controllers/Sales/pricecontroller.cpp \
    View/Sales/priceslistview.cpp \
    Model/store.cpp \
    Controllers/storecontroller.cpp \
    View/storeslistview.cpp \
    View/addstoreview.cpp \
    View/Sales/addpriceview.cpp \
    Model/Sales/saleproductorder.cpp \
    Model/Sales/salesorder.cpp \
    Controllers/Sales/salesordercontroller.cpp \
    View/Sales/salesorderslistview.cpp \
    View/Sales/addsalesorderview.cpp \
    View/Sales/addsaleproductorderview.cpp \
    Model/Sales/purchasesorder.cpp \
    Model/Sales/purchaseproductorder.cpp \
    Controllers/Sales/purchasesordercontroller.cpp \
    View/Sales/purchasesorderslistview.cpp \
    View/Sales/addpurchasesorderview.cpp \
    View/Sales/addpurchaseproductorderview.cpp \
    Model/Tax/account.cpp \
    Controllers/Tax/accountscontroller.cpp \
    View/Tax/accountslistview.cpp \
    View/Tax/addaccountview.cpp \
    Model/Tax/history.cpp \
    Controllers/Tax/historiescontroller.cpp \
    View/Tax/historieslistview.cpp \
    View/Tax/addhistoryview.cpp \
    Model/Tax/entry.cpp \
    Controllers/Tax/entriescontroller.cpp \
    View/Tax/entrieslistview.cpp \
    View/Tax/addentryview.cpp

HEADERS  += mainwindow.h \
        Controllers/databasecontroller.h \
        Util/utilities.h \
        Model/user.h \
        Exceptions/filenotfoundexception.h \
        Controllers/usercontroller.h \
        UT/testing.h \
        View/userslistview.h \
        View/adduserview.h \
        View/imainwindow.h \
        View/login.h \
        Model/Stock/manufacturer.h \
        Controllers/Stock/manufacturercontroller.h \
        View/Stock/addmanufacturerview.h \
        View/Stock/manufacturerslistview.h \
        Model/Stock/provider.h \
        Controllers/Stock/providercontroller.h \
        View/Stock/providerslistview.h \
        View/Stock/addproviderview.h \
        Model/Stock/productcategory.h \
        Controllers/Stock/productcategorycontroller.h \
        View/Stock/productcategorieslistview.h \
        View/Stock/addproductcategoryview.h \
        Model/Stock/product.h \
        Controllers/Stock/productcontroller.h \
        View/Stock/productslistview.h \
        View/Stock/addproductview.h \
        Model/Customers/customer.h \
        Controllers/Customers/customercontroller.h \
        Model/Customers/physicalcustomer.h \
        Model/Customers/enterprisecustomer.h \
        View/Customers/customerslistview.h \
        View/Customers/addenterprisecustomerview.h \
        View/Customers/addphysicalcustomerview.h \
        Model/Stock/stockunit.h \
        Controllers/Stock/stockunitcontroller.h \
        View/Stock/stockunitslistview.h \
        View/Stock/addstockunitview.h \
        Model/Stock/productorigin.h \
        Controllers/Stock/productorigincontroller.h \
        View/Stock/productoriginslistview.h \
        View/Stock/addproductoriginview.h \
        Model/Tax/csticms.h \
        Controllers/Tax/csticmscontroller.h \
        View/Tax/csticmsslistview.h \
        View/Tax/addcsticmsview.h \
        Model/Tax/cstipi.h \
        Controllers/Tax/cstipicontroller.h \
        View/Tax/cstipislistview.h \
        View/Tax/addcstipiview.h \
        Model/Tax/cstpis.h \
        Controllers/Tax/cstpiscontroller.h \
        View/Tax/cstpisslistview.h \
        View/Tax/addcstpisview.h \
        Model/Tax/cstcofins.h \
        Controllers/Tax/cstcofinscontroller.h \
        View/Tax/cstcofinsslistview.h \
        View/Tax/addcstcofinsview.h \
        Model/Tax/taxrate.h \
        Controllers/Tax/taxratecontroller.h \
        View/Tax/taxrateslistview.h \
        View/Tax/addtaxrateview.h \
        Model/Tax/cfop.h \
        Controllers/Tax/cfopcontroller.h \
        View/Tax/cfopslistview.h \
        View/Tax/addcfopview.h \
    Model/Sales/price.h \
    Controllers/Sales/pricecontroller.h \
    View/Sales/priceslistview.h \
    Model/store.h \
    Controllers/storecontroller.h \
    View/storeslistview.h \
    View/addstoreview.h \
    View/Sales/addpriceview.h \
    Model/Sales/saleproductorder.h \
    Model/Sales/salesorder.h \
    Controllers/Sales/salesordercontroller.h \
    View/Sales/salesorderslistview.h \
    View/Sales/addsalesorderview.h \
    View/Sales/addsaleproductorderview.h \
    Model/Sales/purchasesorder.h \
    Model/Sales/purchaseproductorder.h \
    Controllers/Sales/purchasesordercontroller.h \
    View/Sales/purchasesorderslistview.h \
    View/Sales/addpurchasesorderview.h \
    View/Sales/addpurchaseproductorderview.h \
    Model/Tax/account.h \
    Controllers/Tax/accountscontroller.h \
    View/Tax/accountslistview.h \
    View/Tax/addaccountview.h \
    Model/Tax/history.h \
    Controllers/Tax/historiescontroller.h \
    View/Tax/historieslistview.h \
    View/Tax/addhistoryview.h \
    Model/Tax/entry.h \
    Controllers/Tax/entriescontroller.h \
    View/Tax/entrieslistview.h \
    View/Tax/addentryview.h

FORMS    += mainwindow.ui \
        View/userslistview.ui \
        View/adduserview.ui \
        View/login.ui \
        View/Stock/addmanufacturerview.ui \
        View/Stock/manufacturerslistview.ui \
        View/Stock/providerslistview.ui \
        View/Stock/addproviderview.ui \
        View/Stock/productcategorieslistview.ui \
        View/Stock/addproductcategoryview.ui \
        View/Stock/productslistview.ui \
        View/Stock/addproductview.ui \
        View/Customers/customerslistview.ui \
        View/Customers/addenterprisecustomerview.ui \
        View/Customers/addphysicalcustomerview.ui \
        View/Stock/stockunitslistview.ui \
        View/Stock/addstockunitview.ui \
        View/Stock/productoriginslistview.ui \
        View/Stock/addproductoriginview.ui \
        View/Tax/csticmsslistview.ui \
        View/Tax/addcsticmsview.ui \
        View/Tax/cstipislistview.ui \
        View/Tax/addcstipiview.ui \
        View/Tax/cstpisslistview.ui \
        View/Tax/addcstpisview.ui \
        View/Tax/cstcofinsslistview.ui \
        View/Tax/addcstcofinsview.ui \
        View/Tax/taxrateslistview.ui \
        View/Tax/addtaxrateview.ui \
        View/Tax/cfopslistview.ui \
        View/Tax/addcfopview.ui \
    View/Sales/priceslistview.ui \
    View/storeslistview.ui \
    View/addstoreview.ui \
    View/Sales/addpriceview.ui \
    View/Sales/salesorderslistview.ui \
    View/Sales/addsalesorderview.ui \
    View/Sales/addsaleproductorderview.ui \
    View/Sales/purchasesorderslistview.ui \
    View/Sales/addpurchasesorderview.ui \
    View/Sales/addpurchaseproductorderview.ui \
    View/Tax/accountslistview.ui \
    View/Tax/addaccountview.ui \
    View/Tax/historieslistview.ui \
    View/Tax/addhistoryview.ui \
    View/Tax/entrieslistview.ui \
    View/Tax/addentryview.ui

TRANSLATIONS = ERPRock_pt.ts

unix:LIBS += -lpq
win32:LIBS += C:\PostgreSQL\9.3\lib\libpq.lib
#win32:LIBS += libpqdll.lib
#win32 {
#
#    ## Windows common build here
#
#    !contains(QMAKE_HOST.arch, x86_64) {
#        message("x86 build")
#
#        ## Windows x86 (32bit) specific build here
#
#    } else {
#        message("x86_64 build")
#
#        ## Windows x64 (64bit) specific build here
#		LIBS += libpqdll.lib
#
#    }
#}

RESOURCES += \
    images.qrc

OTHER_FILES += \
    other/cfop.input
