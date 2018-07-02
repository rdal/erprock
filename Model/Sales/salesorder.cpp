#include "salesorder.h"

SalesOrder::SalesOrder(int id, QList<SaleProductOrder*> *saleProductOrders, QString receipt, QDateTime date,
                       int paymentCondition, Utilities::PaymentForm paymentForm, double discount, QString observation,
                       double valuePaid, QString customerId, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->saleProductOrders = saleProductOrders;
    this->receipt = receipt;
    this->date = date;
    this->paymentCondition = paymentCondition;
    this->paymentForm = paymentForm;
    this->discount = discount;
    this->observation = observation;
    this->valuePaid = valuePaid;
    this->customerId = customerId;
}

SalesOrder::SalesOrder(QList<SaleProductOrder*> *saleProductOrders, QString receipt, int paymentCondition,
                       Utilities::PaymentForm paymentForm, double discount, QString observation, double valuePaid,
                       QString customerId, QObject *parent) :
    QObject(parent)
{
    this->id = 0;
    this->saleProductOrders = saleProductOrders;
    this->receipt = receipt;
    this->paymentCondition = paymentCondition;
    this->paymentForm = paymentForm;
    this->discount = discount;
    this->observation = observation;
    this->valuePaid = valuePaid;
    this->customerId = customerId;
}

int SalesOrder::getId()
{
    return this->id;
}

QList<SaleProductOrder*> *SalesOrder::getSaleProductOrders()
{
    return this->saleProductOrders;
}

QString SalesOrder::getReceipt()
{
    return this->receipt;
}

QDateTime SalesOrder::getDate()
{
    return this->date;
}

int SalesOrder::getPaymentCondition()
{
    return this->paymentCondition;
}

Utilities::PaymentForm SalesOrder::getPaymentForm()
{
    return this->paymentForm;
}

//QString SalesOrder::getPaymentFormName(Utilities::PaymentForm paymentForm)
//{
//    QString ret = "";
//    switch(paymentForm)
//    {
//        case Utilities::MONEY:
//        {
//            ret = tr("Money");
//            break;
//        }
//        case Utilities::VISA:
//        {
//            ret = tr("Visa");
//            break;
//        }
//        case Utilities::MASTERCARD:
//        {
//            ret = tr("MasterCard");
//            break;
//        }
//        case Utilities::DINERS:
//        {
//            ret = tr("Diners");
//            break;
//        }
//        case Utilities::AMEX:
//        {
//            ret = tr("American Express");
//            break;
//        }
//        case Utilities::BANK_TICKET:
//        {
//            ret = tr("Boleto Bancário");
//            break;
//        }
//        default:
//        {
//            break;
//        }
//    }

//    return ret;
//}

double SalesOrder::getDiscount()
{
    return this->discount;
}

QString SalesOrder::getObservation()
{
    return this->observation;
}

double SalesOrder::getValuePaid()
{
    return this->valuePaid;
}

double SalesOrder::getValueTotal()
{
    SaleProductOrder *saleProductOrder = NULL;

    double totalValue = 0;
    int count = this->saleProductOrders->count();
    for(int i=0; i<count; i++)
    {
        saleProductOrder = this->saleProductOrders->at(i);
        double val = saleProductOrder->getValue() * saleProductOrder->getQuantity();
        totalValue += val;
    }

    if(saleProductOrder)
        delete saleProductOrder;

    return totalValue;
}

QString SalesOrder::getCustomerId()
{
    return this->customerId;
}

void SalesOrder::setSaleProductOrders(QList<SaleProductOrder*> *saleProductOrders)
{
    this->saleProductOrders = saleProductOrders;
}

void SalesOrder::appendSaleProductOrder(SaleProductOrder *saleProductOrder)
{
    this->saleProductOrders->append(saleProductOrder);
}

void SalesOrder::removeSaleProductOrder(SaleProductOrder *saleProductOrder)
{
    this->saleProductOrders->removeOne(saleProductOrder);
}

void SalesOrder::setReceipt(QString receipt)
{
    this->receipt = receipt;
}

void SalesOrder::setDate(QDateTime date)
{
    this->date = date;
}

void SalesOrder::setPaymentCondition(int paymentCondition)
{
    this->paymentCondition = paymentCondition;
}

void SalesOrder::setPaymentForm(Utilities::PaymentForm paymentForm)
{
    this->paymentForm = paymentForm;
}

void SalesOrder::setDiscount(double discount)
{
    this->discount = discount;
}

void SalesOrder::setObservation(QString observation)
{
    this->observation = observation;
}

void SalesOrder::setValuePaid(double valuePaid)
{
    this->valuePaid = valuePaid;
}

void SalesOrder::setCustomerId(QString customerId)
{
    this->customerId = customerId;
}
