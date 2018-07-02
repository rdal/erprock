#include "purchasesorder.h"

PurchasesOrder::PurchasesOrder(int id, QList<PurchaseProductOrder*> *purchaseProductOrders, QString receipt, QDateTime date,
                               QString providerId, int paymentCondition, Utilities::PaymentForm paymentForm,
                               QString observation, double valuePaid, double cargo, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->purchaseProductOrders = purchaseProductOrders;
    this->receipt = receipt;
    this->date = date;
    this->providerId = providerId;
    this->paymentCondition = paymentCondition;
    this->paymentForm = paymentForm;
    this->observation = observation;
    this->valuePaid = valuePaid;
    this->cargo = cargo;
}

PurchasesOrder::PurchasesOrder(QList<PurchaseProductOrder*> *purchaseProductOrders, QString receipt, QDateTime date,
                               QString providerId, int paymentCondition, Utilities::PaymentForm paymentForm,
                               QString observation, double valuePaid, double cargo, QObject *parent) :
    QObject(parent)
{
    this->id = 0;
    this->purchaseProductOrders = purchaseProductOrders;
    this->receipt = receipt;
    this->date = date;
    this->providerId = providerId;
    this->paymentCondition = paymentCondition;
    this->paymentForm = paymentForm;
    this->observation = observation;
    this->valuePaid = valuePaid;
    this->cargo = cargo;
}

int PurchasesOrder::getId()
{
    return this->id;
}

QList<PurchaseProductOrder*> *PurchasesOrder::getPurchaseProductOrders()
{
    return this->purchaseProductOrders;
}

QString PurchasesOrder::getReceipt()
{
    return this->receipt;
}

QDateTime PurchasesOrder::getDate()
{
    return this->date;
}

QString PurchasesOrder::getProviderId()
{
    return this->providerId;
}

int PurchasesOrder::getPaymentCondition()
{
    return this->paymentCondition;
}

Utilities::PaymentForm PurchasesOrder::getPaymentForm()
{
    return this->paymentForm;
}

QString PurchasesOrder::getObservation()
{
    return this->observation;
}

double PurchasesOrder::getValuePaid()
{
    return this->valuePaid;
}

double PurchasesOrder::getCargo()
{
    return this->cargo;
}

double PurchasesOrder::getValueTotal()
{
    PurchaseProductOrder *purchaseProductOrder = NULL;

    double totalValue = 0;
    int count = this->purchaseProductOrders->count();
    for(int i=0; i<count; i++)
    {
        purchaseProductOrder = this->purchaseProductOrders->at(i);
        double val = purchaseProductOrder->getUnitPrice() * purchaseProductOrder->getQuantity();
        totalValue += val;
    }
    totalValue += this->cargo;

    if(purchaseProductOrder)
        delete purchaseProductOrder;

    return totalValue;
}

void PurchasesOrder::setPurchaseProductOrders(QList<PurchaseProductOrder*> *purchaseProductOrders)
{
    this->purchaseProductOrders = purchaseProductOrders;
}

void PurchasesOrder::appendPurchaseProductOrder(PurchaseProductOrder *purchaseProductOrder)
{
    this->purchaseProductOrders->append(purchaseProductOrder);
}

void PurchasesOrder::removePurchaseProductOrder(PurchaseProductOrder *purchaseProductOrder)
{
    this->purchaseProductOrders->removeOne(purchaseProductOrder);
}

void PurchasesOrder::setReceipt(QString receipt)
{
    this->receipt = receipt;
}

void PurchasesOrder::setDate(QDateTime date)
{
    this->date = date;
}

void PurchasesOrder::setProviderId(QString providerId)
{
    this->providerId = providerId;
}

void PurchasesOrder::setPaymentCondition(int paymentCondition)
{
    this->paymentCondition = paymentCondition;
}

void PurchasesOrder::setPaymentForm(Utilities::PaymentForm paymentForm)
{
    this->paymentForm = paymentForm;
}

void PurchasesOrder::setObservation(QString observation)
{
    this->observation = observation;
}

void PurchasesOrder::setValuePaid(double valuePaid)
{
    this->valuePaid = valuePaid;
}

void PurchasesOrder::setCargo(double cargo)
{
    this->cargo = cargo;
}
