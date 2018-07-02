#include "salesordercontroller.h"
#include "productcontroller.h"
#include "pricecontroller.h"
#include "entriescontroller.h"

SalesOrderController::SalesOrderController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

SalesOrderController::~SalesOrderController()
{
}



SaleProductOrder *SalesOrderController::createNewSaleProductOrder(QString productCode, int quantity)
{
    ProductController *productController = new ProductController();
    Product *product = productController->getProductByCode(productCode);

    PriceController *priceController = new PriceController();
    Price *price = priceController->getPriceByProductCode(productCode);

    Utilities *u = new Utilities();

    SaleProductOrder *saleProductOrder = new SaleProductOrder(productCode,
                                                              quantity,
                                                              product->getCstIcms(),
                                                              product->getCstIpi(),
                                                              product->getCstPis(),
                                                              product->getCstCofins(),
                                                              product->getIcmsPercentName(),
                                                              product->getIpiPercentName(),
                                                              product->getPisPercentName(),
                                                              product->getCofinsPercentName(),
                                                              product->getCfopCode(),
                                                              u->getDefaultCNPJ(),
                                                              price->getValue());

    delete u;

    delete price;
    delete priceController;

    delete product;
    delete productController;

    return saleProductOrder;
}

Utilities::StatusControl SalesOrderController::storeSalesOrder(SalesOrder *salesOrder, QString receipt)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        QString currentReceipt = salesOrder->getReceipt();
        bool exists = dbController->salesOrderAlreadyExists(currentReceipt);
        if(exists && (currentReceipt != receipt))
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else if(salesOrder->getSaleProductOrders()->count() == 0)
        {
            ret = Utilities::EMPTY;
        }
        else
        {
            bool result = dbController->storeSalesOrder(salesOrder);
            if(!result)
            {
                ret = Utilities::UNKNOWN_ERROR;
            }
//            else{
//                Utilities *u = new Utilities();
//                EntriesController *entriesController = new EntriesController();

//                QList<SaleProductOrder*> *saleProductOrders = salesOrder->getSaleProductOrders();
//                int count = saleProductOrders->count();
//                QDateTime date = QDateTime::currentDateTime();
//                QString storeCnpj = u->getDefaultCNPJ();
//                for(int i=0; i<count; i++){

//                    int quantity = saleProductOrders->at(i)->getQuantity();
//                    double totalValue = (saleProductOrders->at(i)->getValue()) * quantity;

//                    //-- Tax Rates - ICMS
//                    QString icmsNameInSales = saleProductOrders->at(i)->getIcmsPercentName();
//                    TaxRate *icmsTaxRate = dbController->getTaxRateByName(icmsNameInSales);
//                    double icmsTaxRateValue = icmsTaxRate->getValue();
//                    //-- Tax Rates - PIS
//                    QString pisNameInSales = saleProductOrders->at(i)->getPisPercentName();
//                    TaxRate *pisTaxRate = dbController->getTaxRateByName(pisNameInSales);
//                    double pisTaxRateValue = pisTaxRate->getValue();
//                    //-- Tax Rates - COFINS
//                    QString cofinsNameInSales = saleProductOrders->at(i)->getPisPercentName();
//                    TaxRate *cofinsTaxRate = dbController->getTaxRateByName(cofinsNameInSales);
//                    double cofinsTaxRateValue = cofinsTaxRate->getValue();
//                    //--

//                    //double taxes = 0;

//                    QString debtorAccountSale = u->getDefaultDebtorSaleAccount();// 1.1.3.001
//                    QString creditorAccountSale = u->getDefaultCreditorSaleAccount(); // 4.1.1.001
//                    double valueSale = totalValue;
//                    int historyIdSale = u->getSaleHistoryId();
//                    QString complementSale = "";
//                    Entry *entrySale = new Entry(date, storeCnpj, debtorAccountSale, creditorAccountSale, valueSale, historyIdSale, complementSale);
//                    //taxes += icms;

//                    QString debtorAccountIcmsInSales = u->getDefaultIcmsInSalesDebtorAccount(); //4.1.2.999
//                    QString creditorAccountIcmsInSales = u->getDefaultIcmsInSalesCreditorAccount(); // 2.1.1.004
//                    double icmsValueInSales = totalValue * (icmsTaxRateValue/100);
//                    int historyIdIcmsInSales = u->getIcmsInSalesHistoryId();
//                    QString complementIcmsInSales = "";
//                    Entry *entryIcmsInSales = new Entry(date, storeCnpj, debtorAccountIcmsInSales, creditorAccountIcmsInSales, icmsValueInSales, historyIdIcmsInSales, complementIcmsInSales);
//                    //taxes += pis;

//                    QString debtorAccountPisInSales = u->getDefaultPisInSalesDebtorAccount(); //4.1.2.998
//                    QString creditorAccountPisInSales = u->getDefaultPisInSalesCreditorAccount(); // 2.1.1.005
//                    double pisValueInSales = totalValue * (pisTaxRateValue/100);
//                    int historyIdPisInSales = u->getPisInSalesHistoryId();
//                    QString complementPisInSales = "";
//                    Entry *entryPisInSales = new Entry(date, storeCnpj, debtorAccountPisInSales, creditorAccountPisInSales, pisValueInSales, historyIdPisInSales, complementPisInSales);
//                    //taxes += cofins;

//                    QString debtorAccountCofinsInSales = u->getDefaultCofinsInSalesDebtorAccount(); //4.1.2.997
//                    QString creditorAccountCofinsInSales = u->getDefaultCofinsInSalesCreditorAccount(); // 2.1.1.006
//                    double cofinsValueInSales = totalValue * (cofinsTaxRateValue/100);
//                    int historyIdCofinsInSales = u->getCofinsInSalesHistoryId();
//                    QString complementCofinsInSales = "";
//                    Entry *entryCofinsInSales = new Entry(date, storeCnpj, debtorAccountCofinsInSales, creditorAccountCofinsInSales, cofinsValueInSales, historyIdCofinsInSales, complementCofinsInSales);

//                    QString debtorAccountGoodsShipping = u->getDefaultGoodsShippingDebtorAccount(); //3.2.1.001
//                    QString creditorAccountGoodsShipping = u->getDefaultGoodsShippingCreditorAccount(); // 1.1.4.001
//                    double goodsShippingValue = 0;
//                    int historyIdGoodsShipping = u->getGoodsShippingHistoryId();
//                    QString complementGoodsShipping = "";
//                    Entry *entryGoodsShipping = new Entry(date, storeCnpj, debtorAccountGoodsShipping, creditorAccountGoodsShipping, goodsShippingValue, historyIdGoodsShipping, complementGoodsShipping);

//                    entriesController->addEntry(entrySale);
//                    entriesController->addEntry(entryIcmsInSales);
//                    entriesController->addEntry(entryPisInSales);
//                    entriesController->addEntry(entryCofinsInSales);
//                    entriesController->addEntry(entryGoodsShipping);
//                }

//                delete u;
//                delete entriesController;
//            }
        }
    }
    else
    {
        ret = Utilities::DB_NOT_CONNECTED;
    }

    return ret;
}

//Utilities::StatusControl SalesOrderController::updateSalesOrder(SalesOrder *salesOrder)
//{
//    Utilities::StatusControl ret = Utilities::NO_ERR;

//    if(dbController->isConnectionOpen())
//    {
//        bool exists = dbController->salesOrderAlreadyExists(salesOrder->getReceipt());
//        if(!exists)
//        {
//            ret = Utilities::DOESNT_EXIST;
//        }
//        else if(salesOrder->getSaleProductOrders()->count() == 0)
//        {
//            ret = Utilities::EMPTY;
//        }
//        else
//        {
//            bool result = dbController->updateSalesOrder(salesOrder);
//            if(!result)
//            {
//                ret = Utilities::UNKNOWN_ERROR;
//            }
//        }
//    }
//    else
//    {
//        ret = Utilities::DB_NOT_CONNECTED;
//    }
//    return ret;
//}

Utilities::StatusControl SalesOrderController::removeSalesOrder(int id, bool removeRelatedEntries)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removeSalesOrder(id, removeRelatedEntries);
        if(!result)
        {
            ret = Utilities::UNKNOWN_ERROR;
        }
    }
    else
    {
        ret = Utilities::DB_NOT_CONNECTED;
    }
    return ret;
}

SalesOrder *SalesOrderController::getSalesOrderById(int id)
{
    SalesOrder *salesOrder = NULL;
    if(dbController->isConnectionOpen())
    {
        salesOrder = dbController->getSalesOrderById(id);
    }
    return salesOrder;
}

SalesOrder *SalesOrderController::getSalesOrderByReceipt(QString receipt)
{
    SalesOrder *salesOrder = NULL;
    if(dbController->isConnectionOpen())
    {
        salesOrder = dbController->getSalesOrderByReceipt(receipt);
    }
    return salesOrder;
}

QList<SalesOrder*> *SalesOrderController::getSalesOrderByDateRange(QDateTime startDate, QDateTime endDate)
{
    QList<SalesOrder*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getSalesOrdersByDateRange(startDate, endDate);
    }

    return ret;
}

QList<SalesOrder*> *SalesOrderController::getSalesOrders()
{
    QList<SalesOrder*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getSalesOrders();
    }

    return ret;
}

QList<SaleProductOrder*> *SalesOrderController::getSaleProductOrdersBySalesOrderId(int id)
{
    QList<SaleProductOrder*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getSaleProductOrdersBySalesOrderId(id);
    }

    return ret;
}

SaleProductOrder *SalesOrderController::getSaleProductOrderById(int id)
{
    SaleProductOrder *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getSaleProductOrderById(id);
    }

    return ret;
}
