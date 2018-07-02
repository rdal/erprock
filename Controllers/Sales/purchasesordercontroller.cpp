#include "entriescontroller.h"
#include "purchasesordercontroller.h"
#include "productcontroller.h"

PurchasesOrderController::PurchasesOrderController(QObject *parent) :
    QObject(parent)
{
    dbController = DatabaseController::getInstance();
}

PurchasesOrderController::~PurchasesOrderController()
{
}

//PurchaseProductOrder *PurchasesOrderController::createNewPurchaseProductOrder(QString productCode, int quantity, QChar productOriginCode, double unitPrice)
//{
//    ProductController *productController = new ProductController();
//    Product *product = productController->getProductByCode(productCode);
//    Utilities *u = new Utilities();

//    PurchaseProductOrder *purchaseProductOrder = new PurchaseProductOrder(productCode,
//                                                                          quantity,
//                                                                          productOriginCode,
//                                                                          product->getCstIcms(),
//                                                                          product->getCstIpi(),
//                                                                          product->getCstPis(),
//                                                                          product->getCstCofins(),
//                                                                          product->getIcmsPercentName(),
//                                                                          product->getIpiPercentName(),
//                                                                          product->getPisPercentName(),
//                                                                          product->getCofinsPercentName(),
//                                                                          product->getCfopCode(),
//                                                                          unitPrice,
//                                                                          u->getDefaultCNPJ());

//    delete u;
//    delete product;
//    delete productController;

//    return purchaseProductOrder;
//}

Utilities::StatusControl PurchasesOrderController::storePurchasesOrder(PurchasesOrder *purchasesOrder, QString receipt)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        QString currentReceipt = purchasesOrder->getReceipt();
        bool exists = dbController->purchasesOrderAlreadyExists(currentReceipt, purchasesOrder->getProviderId());
        if(exists && (currentReceipt != receipt))
        {
            ret = Utilities::ALREADY_EXISTS;
        }
        else if(purchasesOrder->getPurchaseProductOrders()->count() == 0)
        {
            ret = Utilities::EMPTY;
        }
        else
        {
            bool result = dbController->storePurchasesOrder(purchasesOrder);
            if(!result)
            {
                ret = Utilities::UNKNOWN_ERROR;
            }
//            else{
//                Utilities *u = new Utilities();
//                EntriesController *entriesController = new EntriesController();

//                QList<PurchaseProductOrder*> *purchaseProductOrders = purchasesOrder->getPurchaseProductOrders();
//                int count = purchaseProductOrders->count();
//                QDateTime date = QDateTime::currentDateTime();
//                QString storeCnpj = u->getDefaultCNPJ();
//                for(int i=0; i<count; i++){
//                    double unitPrice = purchaseProductOrders->at(i)->getUnitPrice();
//                    int quantity = purchaseProductOrders->at(i)->getQuantity();
//                    double icms = purchaseProductOrders->at(i)->getIcmsValue();
//                    //double ipi = purchaseProductOrders->at(i)->getIpiValue();
//                    double pis = purchaseProductOrders->at(i)->getPisValue();
//                    double cofins = purchaseProductOrders->at(i)->getCofinsValue();

//                    double taxes = 0;

////                    QString creditorAccountBuyProduct = u->getDefaultProviderAccount();
////                    QString debtorAccountBuyProduct = u->getDefaultCashAccount();
////                    double valueBuyProduct = unitPrice * quantity;
////                    int historyIdBuyProduct = u->getBuyProductHistoryId();
////                    QString complementBuyProduct = "";
////                    Entry *entryBuyProduct = new Entry(date, storeCnpj, debtorAccountBuyProduct, creditorAccountBuyProduct, valueBuyProduct, historyIdBuyProduct, complementBuyProduct);

//                    QString creditorAccountIcmsCredit = u->getDefaultProviderAccount();
//                    QString debtorAccountIcmsCredit = u->getDefaultIcmsToRecoverAccount();
//                    double valueIcmsCredit = icms;
//                    int historyIdIcmsCredit = u->getTaxCreditHistoryId();
//                    QString complementIcmsCredit = "";
//                    Entry *entryIcmsCredit = new Entry(date, storeCnpj, debtorAccountIcmsCredit, creditorAccountIcmsCredit, valueIcmsCredit, historyIdIcmsCredit, complementIcmsCredit);
//                    taxes += icms;

//                    QString creditorAccountPisCredit = u->getDefaultProviderAccount();
//                    QString debtorAccountPisCredit = u->getDefaultPisToRecoverAccount();
//                    double valuePisCredit = pis;
//                    int historyIdPisCredit = u->getTaxCreditHistoryId();
//                    QString complementPisCredit = "";
//                    Entry *entryPisCredit = new Entry(date, storeCnpj, debtorAccountPisCredit, creditorAccountPisCredit, valuePisCredit, historyIdPisCredit, complementPisCredit);
//                    taxes += pis;

//                    QString creditorAccountCofinsCredit = u->getDefaultProviderAccount();
//                    QString debtorAccountCofinsCredit = u->getDefaultCofinsToRecoverAccount();
//                    double valueCofinsCredit = cofins;
//                    int historyIdCofinsCredit = u->getTaxCreditHistoryId();
//                    QString complementCofinsCredit = "";
//                    Entry *entryCofinsCredit = new Entry(date, storeCnpj, debtorAccountCofinsCredit, creditorAccountCofinsCredit, valueCofinsCredit, historyIdCofinsCredit, complementCofinsCredit);
//                    taxes += cofins;

//                    QString creditorAccountProductStock = u->getDefaultProviderAccount();
//                    QString debtorAccountProductStock = u->getDefaultProductStockAccount();
//                    double valueProductStock = (unitPrice * quantity) - taxes;
//                    int historyIdProductStock = u->getBuyProductHistoryId();
//                    QString complementProductStock = "";
//                    Entry *entryProductStock = new Entry(date, storeCnpj, debtorAccountProductStock, creditorAccountProductStock, valueProductStock, historyIdProductStock, complementProductStock);

//                    entriesController->addEntry(entryIcmsCredit);
//                    entriesController->addEntry(entryPisCredit);
//                    entriesController->addEntry(entryCofinsCredit);
//                    entriesController->addEntry(entryProductStock);
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

Utilities::StatusControl PurchasesOrderController::removePurchasesOrder(int id, bool removeRelatedEntries)
{
    Utilities::StatusControl ret = Utilities::NO_ERR;

    if(dbController->isConnectionOpen())
    {
        bool result = dbController->removePurchasesOrder(id, removeRelatedEntries);
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

PurchasesOrder *PurchasesOrderController::getPurchasesOrderById(int id)
{
    PurchasesOrder *purchasesOrder = NULL;
    if(dbController->isConnectionOpen())
    {
        purchasesOrder = dbController->getPurchasesOrderById(id);
    }
    return purchasesOrder;
}

PurchasesOrder *PurchasesOrderController::getPurchasesOrderByReceipt(QString receipt)
{
    PurchasesOrder *purchasesOrder = NULL;
    if(dbController->isConnectionOpen())
    {
        purchasesOrder = dbController->getPurchasesOrderByReceipt(receipt);
    }
    return purchasesOrder;
}

QList<PurchasesOrder*> *PurchasesOrderController::getPurchasesOrderByDateRange(QDateTime startDate, QDateTime endDate)
{
    QList<PurchasesOrder*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getPurchasesOrdersByDateRange(startDate, endDate);
    }

    return ret;
}

QList<PurchasesOrder*> *PurchasesOrderController::getPurchasesOrders()
{
    QList<PurchasesOrder*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getPurchasesOrders();
    }

    return ret;
}

QList<PurchaseProductOrder*> *PurchasesOrderController::getPurchaseProductOrdersByPurchasesOrderId(int id)
{
    QList<PurchaseProductOrder*> *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getPurchaseProductOrdersByPurchasesOrderId(id);
    }

    return ret;
}

PurchaseProductOrder *PurchasesOrderController::getPurchaseProductOrderById(int id)
{
    PurchaseProductOrder *ret = NULL;
    if(dbController->isConnectionOpen())
    {
        ret = dbController->getPurchaseProductOrderById(id);
    }

    return ret;
}
