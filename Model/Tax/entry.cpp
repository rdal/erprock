#include "entry.h"


Entry::Entry(int id, QDateTime date, QString storeCnpj, QString debtorAccount, QString creditorAccount, double value, int historyId, QString complement, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->date = date;
    this->storeCnpj = storeCnpj;
    this->debtorAccount = debtorAccount;
    this->creditorAccount = creditorAccount;
    this->value = value;
    this->historyId = historyId;
    this->complement = complement;
}

Entry::Entry(QDateTime date, QString storeCnpj, QString debtorAccount, QString creditorAccount, double value, int historyId, QString complement, QObject *parent) :
    QObject(parent)
{
    this->id = 0;
    this->date = date;
    this->storeCnpj = storeCnpj;
    this->debtorAccount = debtorAccount;
    this->creditorAccount = creditorAccount;
    this->value = value;
    this->historyId = historyId;
    this->complement = complement;
}

Entry::Entry(int id, QDateTime date, QString storeCnpj, QString debtorAccount, QString creditorAccount, double value, int historyId, QString complement, int purchaseOrderId, int saleOrderId, QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->date = date;
    this->storeCnpj = storeCnpj;
    this->debtorAccount = debtorAccount;
    this->creditorAccount = creditorAccount;
    this->value = value;
    this->historyId = historyId;
    this->complement = complement;
    this->purchaseOrderId = purchaseOrderId;
    this->saleOrderId = saleOrderId;
}

Entry::Entry(QDateTime date, QString storeCnpj, QString debtorAccount, QString creditorAccount, double value, int historyId, QString complement, int purchaseOrderId, int saleOrderId, QObject *parent) :
    QObject(parent)
{
    this->id = 0;
    this->date = date;
    this->storeCnpj = storeCnpj;
    this->debtorAccount = debtorAccount;
    this->creditorAccount = creditorAccount;
    this->value = value;
    this->historyId = historyId;
    this->complement = complement;
    this->purchaseOrderId = purchaseOrderId;
    this->saleOrderId = saleOrderId;
}

int Entry::getId()
{
    return this->id;
}

QDateTime Entry::getDate()
{
    return this->date;
}

QString Entry::getStoreCnpj()
{
    return this->storeCnpj;
}

QString Entry::getDebtorAccount()
{
    return this->debtorAccount;
}

QString Entry::getCreditorAccount()
{
    return this->creditorAccount;
}

double Entry::getValue()
{
    return this->value;
}

int Entry::getHistory()
{
    return this->historyId;
}

QString Entry::getComplement()
{
    return this->complement;
}

int Entry::getPurchaseOrderId()
{
    return this->purchaseOrderId;
}

int Entry::getSaleOrderId()
{
    return this->saleOrderId;
}

void Entry::setDate(QDateTime date)
{
    this->date = date;
}

void Entry::setStoreCnpj(QString storeCnpj)
{
    this->storeCnpj = storeCnpj;
}

void Entry::setDebtorAccount(QString debtorAccount)
{
    this->debtorAccount = debtorAccount;
}

void Entry::setCreditorAccount(QString creditorAccount)
{
    this->creditorAccount = creditorAccount;
}

void Entry::setValue(double value)
{
    this->value = value;
}

void Entry::setHistory(int historyId)
{
    this->historyId = historyId;
}

void Entry::setComplement(QString complement)
{
    this->complement = complement;
}
